#include <iostream>
#include "elma.h"
#include <json/json.h>
using nlohmann::json;

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

    json StateMachine::to_json(){
        json j;
        std::string sm_name;
        vector<string> sm_state;
        vector<map<string, string>> sm_trans;
        sm_name = this->name();
        for(int i = 0 ; i < _transitions.size(); i++){
            map<string, string> mp_trans;
            elma::Transition transition = _transitions[i];
            elma::State& state_a = transition.from();
            elma::State& state_b = transition.to();
            mp_trans["from"] = state_a.name();
            mp_trans["to"] = state_b.name();
            mp_trans["when"] = transition.event_name();
            sm_trans.push_back(mp_trans);
            if (std::find(sm_state.begin(), sm_state.end(),state_a.name()) == sm_state.end()){
                sm_state.push_back(state_a.name());
            }
            if (std::find(sm_state.begin(), sm_state.end(),state_b.name()) == sm_state.end()){
                sm_state.push_back(state_b.name());
            }
        }
        j["name"] = sm_name;
        j["states"] = sm_state;
        j["transitions"] = sm_trans;

        return j;
    }

};