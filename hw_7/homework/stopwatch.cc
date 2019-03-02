#include <chrono>
#include <ratio>
#include <iostream>
#include "elma.h"
#include "stopwatch.h"
/*
void init(){
    watch("start", [this](Event& e) {
        s_time = high_resolution_clock::now();
        sp = true;
    });
    watch("stop", [this](Event &e) {
        e_time = high_resolution_clock::now();
        tp = e_time - s_time;
        ed += tp;
    });
    watch("reset", [this](Event& e) {
        s_time = high_resolution_clock::duration::zero();
        tp = high_resolution_clock::duration::zero();
        sp = false;
    });
}


double seconds(){
    if (sp == false){
        throw std::domain_error("Not start yet");
    }
    std::chrono::duration<double> sec = ed;
    return sec.count();
}*/