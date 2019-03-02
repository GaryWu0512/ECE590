#include "gtest/gtest.h"
#include "robot.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace elma;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */
TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));
//start
//sleep;10sec
//result --> 10sec
//sleep;10sec
//stop
//sleep;10sec
//result --> 10sec
//start
//sleep;10sec
//result --> 10sec
//stop
//result --> 20sec
}


/*!!
 * Here we use your Robot class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */
TEST(Question2, RobotEnvironment1) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";

    /*
     * Send signals to robot and test
     */
    
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    std::cout<<robot.to_json();
}

/*!!
 * Here we will create various StateMachines and validate the JSON from the to_json method.
 */
TEST(Question3, to_json) {
    /*
     * coming soon... but this is straight-forward to test. At this point, you shouldn't
     * need help writing tests for this one.
     */
}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */

class TestProcess : public Process {
    public:
        TestProcess(std::string name) : Process(name) {}
        void init() {
            watch("hello", [this](const Event& e) { 
                str = "priority 0";
                std::cout << str << "\n";
            }, 0);
            watch("hello", [this](const Event& e) { 
                str = "priority 1";
                std::cout << str << "\n";
            }, 1);
            watch("hello", [this](const Event& e) { 
                str = "priority 2";
                std::cout << str << "\n";
            }, 2);
            watch("hello", [this](const Event& e) { 
                str = "priority 3";
                std::cout << str << "\n";
            }, 3);
            watch("hello", [this](const Event& e) { 
                str = "priority 11";
                std::cout << str << "\n";
            }, 1);
            

            watch("value", [this](const Event& e) { 
                x = 3;
            },3); 
            watch("value", [this](const Event& e) { 
                x = 1;
            },1);
            watch("value", [this](const Event& e) { 
                x = 9;
            },9); 


            watch("calculate", [this](const Event& e) { 
                result = 10;
            },0); 
            watch("calculate", [this](const Event& e) { 
                result+=13;
            },3); 
            watch("calculate", [this](const Event& e) { 
                result/=2;
            },2);
            watch("calculate", [this](const Event& e) { 
                result*=10;
            },1);          
        }
        void start() {}
        void update() { 
            emit(Event("hello"));
            std::cout << str << "\n";
            ASSERT_EQ("priority 3", str);

            emit(Event("value"));
            std::cout << x << "\n";
            ASSERT_EQ(9, x);

            emit(Event("calculate"));
            std::cout << result << "\n";
            ASSERT_EQ(63, result);
        }
        void stop() {}
    private:
        string str;
        double x;
        int result;
};

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */
TEST(Question4, WatchPriority) {
    /*
     * coming soon...
     */
    std::vector<int> _priority  {4,0,0,2,1};
    std::vector<int> handler  {2,3,5,6,3};
    int temp, temp2;
    //std::cout << sizeof(_priority)/sizeof(int) << "\n\n";
    /*for (int i = 0; i < _priority.size(); i++) {
        for (int j = 0; j < _priority.size()-1-i; j++) {
            std::cout<<_priority[j]<< handler[j]<<"\n";
            std::cout<<"j ="<<j<<"\n";
            if (_priority[j] > _priority[j + 1]) {
                temp = _priority[j + 1];
                _priority[j + 1] = _priority[j];
                _priority[j] = temp;
                temp2= handler[j+1];
                handler[j+1]=handler[j];
                handler[j]=temp2;
                std::cout<<_priority[j]<< handler[j];
            }
        }
    }
    for (int i= 0; i<_priority.size();i++){
        std::cout<< handler[i];
    }*/

     TestProcess p("WatchPriority");        
        Manager m;
        m.schedule(p,10_ms)
          .init();
        p.update();
}