#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <ratio>
#include <thread>
#include <vector>
#include <chrono>

#include "stopwatch.h"
#include "random_filter.h"
#include "elma.h"

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

    TEST(STOPWATCH, BASIC2){
        Stopwatch w;
        w.start();
        SLEEP(120);
        w.stop();      
        SLEEP(100);
        w.start();
        SLEEP(120);
        w.stop();   
        EXPECT_NEAR(w.get_minutes(), 0.004, 0.0005);
        EXPECT_NEAR(w.get_seconds(), 0.24, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 240, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 240000000, 50000000);  
    }

    TEST(STOPWATCH, RESET2){
        Stopwatch w;
        w.start();
        SLEEP(200);
        w.stop();      
        w.reset();
        w.start();
        SLEEP(120);
        w.stop();   
        EXPECT_NEAR(w.get_minutes(), 0.002, 0.05);
        EXPECT_NEAR(w.get_seconds(), 0.12, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 120, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 120000000, 50000000);  
    }

    TEST(STOPWATCH, STOP){
        Stopwatch w;
        w.start();
        SLEEP(100);
        w.stop();      
        w.stop();          
        w.start();
        SLEEP(100);
        w.stop();   
        EXPECT_NEAR(w.get_seconds(), 0.2, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 200, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 200000000, 50000000);  
    }
    TEST(STOPWATCH, START){
        Stopwatch w;
        w.start();
        SLEEP(200);
        w.stop();      
        w.start();          
        w.start();
        w.start();
        SLEEP(100);
        w.stop();   
        std::cout << w.get_seconds() << "\n";  // about 0.3
        EXPECT_NEAR(w.get_seconds(), 0.3, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 300, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 300000000, 50000000);  
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
            EXPECT_NEAR(receiver.sum(), ans[i], 0.1);
        }
    }

    TEST(LATEST, BASIC2){
        vector<double> ans{1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        Receiver receiver("receiver", 2);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_NEAR(receiver.sum(), ans[i], 0.1);
        }
    }

    TEST(LATEST, BASIC3){
        vector<double> ans{1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55});
        Receiver receiver("receiver", 2);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_NEAR(receiver.sum(), ans[i], 0.1);
        }
    }

    TEST(LATEST, BASIC4){
        vector<double> ans{6, 29, 103, 105, 156};
        elma::Manager m;
        Sender sender("sender", vector<double>{6, 23, 74, 2, 51});
        Receiver receiver("receiver", 5);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_NEAR(receiver.sum(), ans[i], 0.1);
        }
    }

    TEST(LATEST, BASIC5){
        vector<double> ans{-3, -5, -6, -6, -5, -3, 0, 4, 9};
        elma::Manager m;
        Sender sender("sender", vector<double>{-3, -2, -1, 0, 1, 2, 3, 4, 5});
        Receiver receiver("receiver", 9);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_NEAR(receiver.sum(), ans[i], 0.1);
        }
    }

    TEST(CHANNEL, CAPACITY1){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        m.channel("Data").change_capacity(5); // channel = {6, 7, 8, 9, 10}
        EXPECT_NEAR(m.channel("Data").earliest(), 6, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 5);
    }

    TEST(CHANNEL, CAPACITY2){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        m.channel("Data").change_capacity(1000);  // channel = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 1000);
    }

    TEST(CHANNEL, CAPACITY3){
        elma::Manager m;
        Sender sender("sender", {1, 1, 2, 3, 5, 8, 13, 21, 34, 55});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        m.channel("Data").change_capacity(8);  // channel = {2, 3, 5, 8, 13, 21, 34, 55}
        EXPECT_NEAR(m.channel("Data").earliest(), 2, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 8);
        m.channel("Data").change_capacity(10); // channel = {2, 3, 5, 8, 13, 21, 34, 55, null, null}
        EXPECT_NEAR(m.channel("Data").earliest(), 2, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 10);        
    }

    
    TEST(CHANNEL, CAPACITY4){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        m.channel("Data").change_capacity(8);  // channel = {3, 4, 5, 6, 7, 8, 9, 10}
        EXPECT_NEAR(m.channel("Data").earliest(), 3, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 8);
        m.channel("Data").change_capacity(6);  // channel = {5, 6, 7, 8, 9, 10}
        EXPECT_NEAR(m.channel("Data").earliest(), 5, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 6);
        m.channel("Data").change_capacity(4);  // channel = {7, 8, 9, 10}
        EXPECT_NEAR(m.channel("Data").earliest(), 7, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 4);
        m.channel("Data").change_capacity(1);  // channel = {10}
        EXPECT_NEAR(m.channel("Data").earliest(), 10, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 1);
    }
    
    TEST(CHANNEL, CAPACITY5){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(60))
        .stop();
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        m.channel("Data").change_capacity(10);  // channel = {1,2,3,4,5}
        EXPECT_NEAR(m.channel("Data").earliest(), 1, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 10);
        m.channel("Data").change_capacity(3);   // channel = {3,4,5}
        EXPECT_NEAR(m.channel("Data").earliest(), 3, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 3);
        m.channel("Data").change_capacity(15);  // channel = {3,4,5}
        EXPECT_NEAR(m.channel("Data").earliest(), 3, 0.1);
        EXPECT_EQ(m.channel("Data").capacity(), 15);
    }

    TEST(RANDOM_FILTER, BASIC1){
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

    TEST(RANDOM_FILTER, BASIC2){
        srand (23);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{0.8, 0.6, 0.4, 0.2});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
        m.run(MS(50)).stop();
        EXPECT_NEAR(f.value(),  1.18068, 0.01);
        m.run(MS(50)).stop();
        EXPECT_NEAR(f.value(),  0.694626, 0.01);
    }

    TEST(RANDOM_FILTER, BASIC3){
        srand (77);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{2, 1, 0, -1, -2});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
        m.run(MS(60)).stop();
        EXPECT_NEAR(f.value(),  1.98004, 0.01);
        m.run(MS(20)).stop();
        EXPECT_NEAR(f.value(),  0.498157, 0.01);
    }

    TEST(RANDOM_FILTER, EXTEND1){
        srand (0);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{0.25, 0.25, 0.25, 0.25});
        elma::Channel data("link", 2);  // original size is only 2

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data);
        EXPECT_EQ(m.channel("link").capacity(), 2);
        m.init();
        EXPECT_GE(m.channel("link").capacity(), 2);
        m.run(MS(50)).stop();
        EXPECT_NEAR(f.value(),  0.704027, 0.01);
        m.run(MS(20)).stop();
        EXPECT_NEAR(f.value(),  0.721892, 0.01);
        m.run(MS(20)).stop();
        EXPECT_NEAR(f.value(),  0.672684, 0.01);
    }

    TEST(RANDOM_FILTER, EXTEND2){
        srand (0);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{0.5, 0.3, 0.2});
        elma::Channel data("link", 2); // original size is only 2

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data);
        EXPECT_EQ(m.channel("link").capacity(), 2);
        m.init();
        EXPECT_GE(m.channel("link").capacity(), 2);
        m.run(MS(100)).stop();
        EXPECT_NEAR(f.value(),  0.436401, 0.01);
        m.run(MS(20)).stop();
        EXPECT_NEAR(f.value(),  0.513963, 0.01);
        m.run(MS(20)).stop();
        EXPECT_NEAR(f.value(),  0.460444, 0.01);
    }

    typedef std::map<string, std::tuple<string, double, double, int>> info_type;
    void ps_test( info_type& info,  info_type& ans){
        //std::cout.precision(3);
        //std::cout<<"======================================="<<std::endl;
        for(auto x: ans){
            string key = x.first;
            EXPECT_EQ(std::get<0>(info[key]), std::get<0>(x.second));            // status
            EXPECT_NEAR(std::get<1>(info[key]), std::get<1>(x.second), 10.0);    // latest_update
            EXPECT_NEAR(std::get<2>(info[key]), std::get<2>(x.second), 10.0);    // delta
            EXPECT_NEAR(std::get<3>(info[key]), std::get<3>(x.second), 1);       // num_updates
            /*
            std::cout<<key<<" || "
                     <<std::get<0>(info[key])<<" || "       
                     <<std::get<1>(info[key])<<" || "
                     <<std::get<2>(info[key])<<" || "
                     <<std::get<3>(info[key])<<std::endl;
            */
        }
        //std::cout<<"======================================="<<std::endl;
    }

    class  Tester: public elma::Process {
      public: 
        Tester(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };

    TEST(PS, BASIC1){
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

    TEST(PS, BASIC2){
        elma::Manager m;
        Tester andy("andy");
        Tester bob("bob");
        Tester cathy("cathy");

        m.schedule(andy, MS(10))
        .schedule(bob, MS(100))
        .schedule(cathy, MS(1000));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"andy", std::make_tuple("STOPPED", 1000.0, 10.0, 100)},
            {"bob", std::make_tuple("STOPPED", 1000.0, 100.0, 10)},
            {"cathy", std::make_tuple("STOPPED", 1000.0, 1000.0, 1)}
        });
        
        m.init().run(MS(1010));
        auto info = m.ps();
        ps_test(info, ans);
    }

    TEST(PS, BASIC3){
        elma::Manager m;
        Tester a("a");
        Tester b("b");
        Tester c("c");
        Tester d("d");
        Tester e("e");

        m.schedule(a, MS(10))
        .schedule(b, MS(20))
        .schedule(c, MS(40))
        .schedule(d, MS(60))
        .schedule(e, MS(120));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"a", std::make_tuple("STOPPED", 120.0, 10.0, 12)},
            {"b", std::make_tuple("STOPPED", 120.0, 20.0, 6)},
            {"c", std::make_tuple("STOPPED", 120.0, 40.0, 3)},
            {"d", std::make_tuple("STOPPED", 120.0, 60.0, 2)},
            {"e", std::make_tuple("STOPPED", 120.0, 120.0, 1)},
        });
        
        m.init().run(MS(130));
        auto info = m.ps();
        ps_test(info, ans);
    }

    TEST(PS, BASIC4){
        elma::Manager m;
        Tester a("a");
        Tester b("b");
        Tester c("c");

        m.schedule(a, MS(30))
        .schedule(b, MS(50))
        .schedule(c, MS(70));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"a", std::make_tuple("STOPPED", 990.0, 30.0, 33)},
            {"b", std::make_tuple("STOPPED", 1000.0, 50.0, 20)},
            {"c", std::make_tuple("STOPPED", 980.0, 70.0, 14)}
        });
        
        m.init().run(MS(1010));
        auto info = m.ps();
        ps_test(info, ans);
    }
    
    TEST(PS, BASIC5){
        elma::Manager m;
        Tester a("a");
        Tester b("b");
        Tester c("c");
        Tester d("d");

        m.schedule(a, MS(256))
        .schedule(b, MS(80))
        .schedule(c, MS(100))
        .schedule(d, MS(64));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"a", std::make_tuple("STOPPED", 512.0, 256.0, 2)},
            {"b", std::make_tuple("STOPPED", 480.0, 80.0, 6)},
            {"c", std::make_tuple("STOPPED", 500.0, 100.0, 5)},
            {"d", std::make_tuple("STOPPED", 512.0, 64.0, 8)}
        });
        
        m.init().run(MS(530));
        auto info = m.ps();
        ps_test(info, ans);
    }
}
