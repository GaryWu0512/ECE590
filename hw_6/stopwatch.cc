#include "elma.h"
#include "stopwatch.h"
#include <chrono>
#include <ratio>
#include <iostream>


void Stopwatch::start(){
    start_time = high_resolution_clock::now();
    start_point = true;
}

void Stopwatch::stop(){
    end_time = high_resolution_clock::now();
    temp = end_time -start_time;
    elapsed += temp;
    //std::cout<< "time = "<<elapsed.count();
}

void Stopwatch::reset(){
    start_time = high_resolution_clock::now();
    end_time = high_resolution_clock::now();
    elapsed = high_resolution_clock::duration::zero();
    temp = high_resolution_clock::duration::zero();
    start_point = false;
}

double Stopwatch::get_minutes(){
    if (start_point == false){
        throw std::domain_error("Not start yet");
    }
    //auto m = minutes_type(milliseconds_type(elapsed));
    //std::cout<< "time min = "<<m.count();
    std::chrono::duration<double, std::ratio<60>> m = elapsed;
    return m.count();
}

double Stopwatch::get_seconds(){
    if (start_point == false){
        throw std::domain_error("Not start yet");
    }
    //auto sec = seconds_type(milliseconds_type(elapsed));
    std::chrono::duration<double> sec = elapsed;
    return sec.count();
}

double Stopwatch::get_milliseconds(){
    if (start_point == false){
        throw std::domain_error("Not start yet");
    }
    //auto mi = milliseconds_type(elapsed);
    //std::cout<< "time = mill"<<mi.count();
    std::chrono::duration<double, std::milli> mill = elapsed;
    return mill.count();
}

double Stopwatch::get_nanoseconds(){
    if (start_point == false){
        throw std::domain_error("Not start yet");
    }
    //auto na = nanoseconds_type(milliseconds_type(elapsed));
    std::chrono::duration<double,std::nano> na = elapsed;
    //std::cout<< "time = nan"<<na.count();
    return na.count();
}
