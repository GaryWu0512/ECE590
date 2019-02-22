#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <ratio>


using namespace std::chrono;

//typedef std::chrono::duration<double,std::milli> milliseconds_type;
//typedef std::chrono::duration<double,std::ratio<1000*60,1>> minutes_type;
//typedef std::chrono::duration<double,std::ratio<1000,1>> seconds_type;
//typedef std::chrono::duration<double,std::ratio<1,1000000>> nanoseconds_type;

class Stopwatch {
    public:
    Stopwatch() {}
    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted
    double get_seconds();      // number of seconds counted
    double get_milliseconds(); // number of milliseconds counted
    double get_nanoseconds();  // number of nanoseconds counted

    private:

    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;
    high_resolution_clock::duration elapsed;
    high_resolution_clock::duration temp;
    bool start_point;
};

#endif