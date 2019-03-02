#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <chrono>
#include <ratio>
#include "elma.h"

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process{
    public:
        Stopwatch() : Process("StopWatch"){}
        void init(){
            ed = high_resolution_clock::duration::zero();
            tp = high_resolution_clock::duration::zero();
            watch("start", [this](Event& e) {
                s_time = high_resolution_clock::now();
                sp = true;
            });
            watch("stop", [this](Event &e) {
                e_time = high_resolution_clock::now();
                tp = e_time - s_time;
                ed = tp;
            });
            watch("reset", [this](Event& e) {
                s_time = high_resolution_clock::now();
                e_time = high_resolution_clock::now();
                tp = high_resolution_clock::duration::zero();
                sp = false;
            });
        }
        void start(){}
        void update() {}
        void stop() {}

        double seconds(){
            if (ed == high_resolution_clock::duration::zero()){
                tp = high_resolution_clock::now() - s_time;
                std::chrono::duration<double> sec = tp;
                //std::cout<<"tp="<<tp.count();
                return sec.count();
            }
            std::chrono::duration<double> sec = ed;
            //std::cout<<"ed="<<ed.count();
            return sec.count();
        }
    
    private:
        high_resolution_clock::time_point s_time;
        high_resolution_clock::time_point e_time;
        high_resolution_clock::duration ed;
        high_resolution_clock::duration tp;
        bool sp;
};

/*class Stopwatch : public Process {
    public:
        Stopwatch() : Process("StopWatch") {}
        void init();
        void start() {}
        void update() {}
        void stop() {}
        
        double seconds();

    private:
        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
        high_resolution_clock::duration elapsed;
        high_resolution_clock::duration temp;
        bool start_point;

};*/

class StopWatchUser : public Process {
    public:
        StopWatchUser(): Process("StopWatchUser") {}
        void init();
        void start() {
            m.schedule(watch, 10_ms)
            .init()
            .start();

            m.emit(Event("start"));
            m.emit(Event("stop"));
            m.emit(Event("reset"));
        }
        void update() {}
        void stop() {}
    private:
        Manager m;
        Stopwatch watch;

};
#endif