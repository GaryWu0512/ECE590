#include <stdexcept>
#include <iostream>
#include <tuple>
#include "stopwatch.h"
#include "process.h"
#include "channel.h"
#include "elma.h"

namespace elma {

    Manager& Manager::schedule(
        Process& process, 
        high_resolution_clock::duration period) {

        process._period = period;
        _processes.push_back(&process); 
        process._manager_ptr = this;            

        return *this;

    }

    Manager& Manager::drop(Process&) {

    }

    Manager& Manager::add_channel(Channel& channel) {
        _channels[channel.name()] = &channel;
        return *this;
    }

    Channel& Manager::channel(string name) {
        if ( _channels.find(name) != _channels.end() ) {
          return *(_channels[name]);
        } else {
            throw std::domain_error("Tried to access an unregistered or non-existant channel.");
        }
    }

    Manager& Manager::all(std::function< void(Process&) > f) {
        for(auto process_ptr : _processes) {
            f(*process_ptr);
        }
        return *this;
    }

    Manager& Manager::init() {
        return all([](Process& p) { p._init();});
    }

    Manager& Manager::start() {
        return all([this](Process& p) { p._start(_elapsed) ;});
    }    

    Manager& Manager::stop() {
        return all([](Process& p) { p._stop(); });
    }    

    Manager& Manager::update() { 
        return all([this](Process& p) {
            if ( _elapsed > p.last_update() + p.period() ) {
                p._update(_elapsed);
            }
        });
    }

    Manager& Manager::run(high_resolution_clock::duration runtime) {

        _start_time = high_resolution_clock::now();
        _elapsed = high_resolution_clock::duration::zero();
        start();        

        while ( _elapsed < runtime ) {
            update();
            _elapsed = high_resolution_clock::now() - _start_time;
        }

        stop();

        return *this;

    }

    map<string, std::tuple<string, double, double, int>> Manager::ps(){
        map<string, std::tuple<string, double, double, int>> result;
        std::tuple<string, double, double, int> t;

        string _name;
        string _status;
        elma::Process::status_type s_type;
        double _last_update;
        double _delta;
        int _num_updates;
        for (int i = 0 ; i < _processes.size(); i++){
            elma::Process *process = _processes[i];
            _name = process->name();
            s_type = process->status();

            if (s_type == 0){
                _status = "UNINITIALIZED";
            }else if (s_type == 1){
                _status = "STOPPED";
            }else if(s_type == 2){
                _status = "RUNNING";
            }
            
            std::chrono::duration<double, std::milli> _last = process->last_update();
            _last_update = _last.count();
            _delta = process->delta();
            _num_updates = process->num_updates();
            t = std::make_tuple( _status, _last_update, _delta, _num_updates );
            result[_name] = t;
        }
        return result;
    }
}