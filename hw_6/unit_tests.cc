#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <ratio>
#include <thread>
#include <vector>
#include <chrono>

#include "stopwatch.h"
#include "elma.h"
#include "random_filter.h"


#define SLEEP(__ms__) std::this_thread::sleep_for(std::chrono::milliseconds(__ms__))
#define MS(__ms__) high_resolution_clock::duration(milliseconds(__ms__))

using std::vector;
using std::string;
using namespace random_filter;

namespace {

    TEST(STOPWATCH, BASIC1){
        Stopwatch w;
        w.start();
        SLEEP(100);
        w.stop();      
        SLEEP(100);
        w.start();
        SLEEP(50);
        w.stop();   
        EXPECT_NEAR(w.get_seconds(), 0.15, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 150, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 150000000, 50000000);  
    }  

    class Sender : public elma::Process {
      public: 
        Sender(string name, vector<double> vect) : Process(name), _data(vect.begin(), vect.end()), _idx(0) {}
        void init() {}
        void start() {}
        void update() {
            channel("Data").send(_data[_idx++]);
            if(_idx==_data.size()) _idx=0;
        }
        void stop() {}
      private:
        int _idx;
        vector<double> _data;
    };

    class Receiver : public elma::Process {
      public: 
        Receiver(std::string name, int n) : Process(name), _sum(0.0), _n(n) {}
        void init() {}
        void start() {}
        void update() {
            if(channel("Data").nonempty()){
                _sum = 0;
                vector<double> data = channel("Data").latest(_n);
                for(auto x: data)
                    _sum += x;
            }
        }
        inline double sum() {return _sum;}
        void stop() {}
      private:
        int _n;
        double _sum;
    };
    
    TEST(LATEST, BASIC){
        vector<double> ans{1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        Receiver receiver("receiver", 10);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_DOUBLE_EQ(receiver.sum(), ans[i]);
        }
    }

    TEST(CAPACITY, BASIC){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 1);
        m.channel("Data").change_capacity(5);
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 6);
        EXPECT_EQ(m.channel("Data").capacity(), 5);
    }

    TEST(RANDOM_FILTER, BASIC){
        srand (0);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{1, 1, 1});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
        m.run(MS(40)).stop();
        EXPECT_NEAR(f.value(),  2.01767, 0.01);
        m.run(MS(40)).stop();
        EXPECT_NEAR(f.value(),  1.90764, 0.01);
    }

    class  Tester: public elma::Process {
      public: 
        Tester(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };

    typedef std::map<string, std::tuple<string, double, double, int>> info_type;
    void ps_test( info_type& info,  info_type& ans){
        //std::cout.precision(3);
        //std::cout<<"======================================="<<std::endl;
        for(auto x: ans){
            string key = x.first;
            EXPECT_EQ(std::get<0>(info[key]), std::get<0>(x.second));
            EXPECT_NEAR(std::get<1>(info[key]), std::get<1>(x.second), 10.0);
            EXPECT_NEAR(std::get<2>(info[key]), std::get<2>(x.second), 10.0);
            EXPECT_NEAR(std::get<3>(info[key]), std::get<3>(x.second), 1);
            
            //std::cout<<key<<" || "
            //         <<std::get<0>(info[key])<<" || "
            //         <<std::get<1>(info[key])<<" || "
            //         <<std::get<2>(info[key])<<" || "
            //         <<std::get<3>(info[key])<<std::endl;
        }
        //std::cout<<"======================================="<<std::endl;
    }

    TEST(PS, BASIC){
        elma::Manager m;
        Tester james("james");
        Tester lily("lily");

        m.schedule(james, MS(17))
        .schedule(lily, MS(31));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"james", std::make_tuple("STOPPED", 85.0, 17.0, 5)},
            {"lily", std::make_tuple("STOPPED", 93.0, 31.0, 3)},
        });
        
        m.init().run(MS(100));
        auto info = m.ps();
        ps_test(info, ans);
    }

}



/* 
#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <ratio>
#include <thread>
#include <vector>

#include "elma.h"

namespace {

    using std::string;
    using namespace std::chrono;
    using std::vector;

    #define MS(__ms__) high_resolution_clock::duration(milliseconds(__ms__))

    TEST(RATIO,RATIO) {
      typedef std::ratio<2,3> two_thirds;
      std::cout << two_thirds::num << "/" <<two_thirds::den << "\n";
      typedef std::chrono::duration<int,std::milli> milliseconds_type;

      auto x = milliseconds_type(10);   
      std::cout << "ten ms = " << x.count() << "ms\n";

      typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
      auto y = seconds_type(x);
      std::cout << "ten ms = " << y.count() << "s\n";

      auto w = x+y;
      auto z = y+y;
      std::cout << "x+y = " << w.count() << "ms\n";
      std::cout << "y+x = " << z.count() << "s\n";

      auto zero = seconds_type::zero();
      ASSERT_EQ(0, zero.count());

    }

    TEST(CLOCK,CLOCK) {
      high_resolution_clock::time_point t = high_resolution_clock::now();
      std::cout << t.time_since_epoch().count() << " ns since 1970\n";
      typedef std::chrono::duration<double,std::ratio<3600*24*365,1>> years;
      auto y = years(t.time_since_epoch());
      std::cout << y.count() << " hours since 1970\n";
    }

    TEST(CLOCK,DIFF) {
      high_resolution_clock::time_point t1, t2;
      t1 = high_resolution_clock::now();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      t2 = high_resolution_clock::now();
      std::cout << (t2 - t1).count() << " ns\n";      
    }

    class MyProcess : public elma::Process {
      public:
        MyProcess(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() { 
          std::cout << name() << ": " 
                    << milli_time()
                    << "ms\n";
        }
        void stop() {}
    };

    TEST(Manager,Schedule) {
      elma::Manager m;
      MyProcess p("A"), q("B");
      m.schedule(p, MS(1))
       .schedule(q, MS(5))
       .init()
       .run(MS(11));
       ASSERT_EQ(p.num_updates(), 10);
       ASSERT_EQ(q.num_updates(), 2);
    }

    class OpenLoopCar : public elma::Process {
      public:
        OpenLoopCar(std::string name) : Process(name) {}
        void init() {}
        void start() {
          velocity = 0;
        }
        void update() {
          double u = 1;
          velocity += delta() * ( - k * velocity + u ) / m;
          std::cout << "t: " << milli_time() << " ms\tv: " << velocity << " m/s\n";
        }
        void stop() {}
      private:
        double velocity;
        const double k = 0.02;
        const double m = 100;
    };

    TEST(Car,OpenLoop) {
      elma::Manager m;
      OpenLoopCar car("Toyota");
      m.schedule(car, MS(10))
       .init()
       .run(MS(100));
    }    

    class ControllableCar : public elma::Process {
      public:
        ControllableCar(std::string name) : Process(name) {}
        void init() {}
        void start() {
          velocity = 0;
        }
        void update() {
          if ( channel("Throttle").nonempty() ) {
            force = channel("Throttle").latest();
          }
          velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
          channel("Velocity").send(velocity);
          std::cout << "t: "  << milli_time() << " ms\t" 
                    << " u: " << force        << " N\t"
                    << " v: " << velocity     << " m/s\n";
        }
        void stop() {}
      private:
        double velocity;
        double force;
        const double k = 0.02;
        const double m = 1000;
    };  

    class CruiseControl : public elma::Process {
      public:
        CruiseControl(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {
          if ( channel("Velocity").nonempty() ) {
            speed = channel("Velocity").latest();
          }
          channel("Throttle").send(-KP*(speed - desired_speed));
        }
        void stop() {}
      private:
        double speed = 0;
        const double desired_speed = 50.0,
                     KP = 314.15;
                     vector<double> _v;
    };   

    TEST(Car,ClosedLoop) {

      elma::Manager m;

      ControllableCar car("Car");
      CruiseControl cc("Control");
      elma::Channel throttle("Throttle");
      elma::Channel velocity("Velocity");

      m.schedule(car, MS(10))
       .schedule(cc, MS(10))
       .add_channel(throttle)
       .add_channel(velocity)
       .init()
       .run(MS(10000));

    }

}*/
