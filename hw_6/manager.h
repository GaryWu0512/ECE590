#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <map>
#include <chrono>
#include <functional>
#include <tuple> 

#include "elma.h"

namespace elma {

    using std::string;
    using std::vector;
    using std::map;
    using std::tuple;
    using namespace std::chrono;

    class Channel;
    class Process;

    class Manager {

        public: 

        Manager() {}

        Manager& add_channel(Channel&);
        Manager& schedule(Process& process, high_resolution_clock::duration period);

        Channel& channel(string);

        Manager& drop(Process&);
        Manager& all(std::function<void(Process&)> f);

        Manager& init();
        Manager& start();
        Manager& stop();
        Manager& run(high_resolution_clock::duration);

        map<string, tuple<string, double, double, int>> ps();

        // should this be private?
        Manager& update();

        inline high_resolution_clock::time_point start_time() { return _start_time; }
        inline high_resolution_clock::duration elapsed() { return _elapsed; }

        private:

        vector<Process *> _processes;
        map<string, Channel *> _channels;
        high_resolution_clock::time_point _start_time;
        high_resolution_clock::duration _elapsed;

    };

}

#endif