#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

/*!
 * This is an internally used by Robot. We won't be testing this class.
 */
class RobotState : public State {
    public:
        RobotState(std::string name) : State(name){
            /*
            mp.insert(std::make_pair("Recharge",State("Recharge"));
            mp.insert(std::make_pair("Wander",State("Wander"));
            
            State("Wander") {}
            State("Make Noise") {}
            State("Evade") {}
            State("Find Recharge Station") {}
            State("Nothing") {}
            */
        }

        void entry(const Event& e) {}
        void during() {}
        void exit(const Event& e) {}


    /*
     * Question 2: define a 'RobotState' that inherits from 'State'
     * Hint 1: you'll need to implement the 'virtual' methods and inherit both of
     * the 'State' constructors.
     */
};

class Robot : public StateMachine {
public:
    Robot(std::string name) : StateMachine(name){
        set_initial(closed_off);
        add_transition("battery full", Recharge, Wander);
        add_transition("found recharge station", Find_Recharge_Station, Recharge);
        add_transition("battery low", Evade, Find_Recharge_Station);

        add_transition("battery low", Wander, Find_Recharge_Station);
        add_transition("reset", Make_Noise, Wander);

        add_transition("intruder detected", Wander, Make_Noise);
        add_transition("reset", Evade, Make_Noise);
        add_transition("proximity warning", Make_Noise, Evade);
        add_transition("start", closed_off, Wander);
    }
   /*
   
    */
    /*
     * Implement contructors. Constructors should instantiate states
     * and transitions AND should set initial_state so that Event('start')
     * sets the Robot to state 'Wander'
     *
     * Look at code for StateMachine.h and in examples and elma/example if you need help.
     *
     * States should have the EXACT names:
     * "Recharge"
     * "Wander"
     * "Find Recharge Station"
     * "Evade"
     * Make Noise"
     *
     * Robot should respond to events with the EXACT names:
     * "found recharge station"
     * "battery full"
     * "battery low"
     * "start"
     * "reset"
     * "intruder detected"
     * "proximity warning"
     */

private:
    /*
     * Hint: You may want to keep RobotState here since locally declared variables are destroyed
     */
    RobotState closed_off = RobotState("closed_off");
    RobotState Recharge = RobotState("Recharge");
    RobotState Wander = RobotState("Wander");
    RobotState Find_Recharge_Station = RobotState("Find Recharge Station");
    RobotState Evade = RobotState("Evade");
    RobotState Make_Noise = RobotState("Make Noise");

};