#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>


#include "elma.h"

using std::vector;
using std::string;

namespace random_filter {

    //class Process;
    //class Channel;

    class Random : public elma::Process {
        public:
            Random(string name) : Process(name), random_number(0.0) {}
            void init() {}
            void start() {}
            void update() { 
            random_number = (double)rand() / (RAND_MAX + 1.);
            channel("link").send(random_number);
            }
            void stop() {}

        private:
            double random_number;
    };

    class Filter : public elma::Process {
        public:
            Filter(string name, vector<double> vect) : Process(name), _filter(vect.begin(),vect.end()), _sum(0.0) {}
            void init() {
                if (_filter.size() > channel("link").capacity()){
                    channel("link").change_capacity(_filter.size());
                }
            }
            void start() {}
            void update() { 
                if(channel("link").nonempty()){
                    _sum = 0;
                    int s = _filter.size();
                    vector<double> q = channel("link").latest(s);
                    if (s>channel("link").size()){
                        for (int i = 0; i< channel("link").size(); i++){
                            _sum+=_filter[i]*q[i];
                        }
                    }else{
                        for (int i = 0; i<s ; i++){
                            _sum+=_filter[i]*q[i];
                        }      
                    }
                }  
            }
            inline double value() {return _sum;}
            void stop() {}

        private:
            double _sum;
            vector<double> _filter;
    };
}

#endif

