#ifndef _MEASURELAMBDA_H
#define _MEASURELAMBDA_H

#include "elma/elma.h"
#include <iostream>
#include <chrono>


    using namespace elma;
    using namespace std::chrono;

class MeasureLambda : public Process {
    public:

    //! Wrap the base process class
    MeasureLambda(std::string op, double x, double y) : Process("measuelambda"){
        j = {
            {"x",x},
            {"y",y},
            {"op",op}
        };
    }

    //! Nothing to do for init
    void init() {}

    //! Nothing to do upon starting
    void start() {}

    //! Emit a switch event each time called
    void update() {
        httplib::SSLClient cli("4r14yiquva.execute-api.us-east-2.amazonaws.com", 443);
        _start_time = high_resolution_clock::now();
        //https://nyqkace875.execute-api.us-west-2.amazonaws.com/default/Calculator
        //https://nyqkace875.execute-api.us-west-2.amazonaws.com/default/TEST
        //https://nyqkace875.execute-api.us-west-2.amazonaws.com/default/test
        https://4r14yiquva.execute-api.us-east-2.amazonaws.com/default/TEST
        auto response = cli.Post("/default/TEST", j.dump(), "json");
        _elapsed += high_resolution_clock::now() - _start_time;
        //std::cout << json::parse(response->body) << "\n";
        duration_all.push_back(_elapsed.count());
        /*
        try {
            if (response && response->status == 200) {
                count+=1;
                duration_all.push_back(_elapsed.count());
                json_response = json::parse(response->body);
            } else if ( response ) {
                std::cout << "Warning:: Elma client connected to a server that returned Error: "
                        << response->status
                        << std::endl;
            } else {
                std::cout << "Warning:: Elma client returned no result"
                        << std::endl;
            }

        } catch (const httplib::Exception& e) {
            std::cout << "Warning: Elma client failed: "
                    << e.what()
                    << "\n";
        } catch(const json::exception& e ) {
            std::cout << "Warning: Elma client could not parse response: "
                    << e.what()
                    << "\n";
        } catch (...) {
            std::cout << "Warning: Elma client failed with no message\n";
        }*/  
        
    }

    //! Nothing to do to stop
    void stop() {}

    double min(){
        minum = *min_element(duration_all.begin(),duration_all.end());
        return minum;
    }
    double max(){
        maxium = *max_element(duration_all.begin(), duration_all.end());
        return maxium;
    }
    double mean(){
        return accumulate( duration_all.begin(), duration_all.end(), 0.0)/duration_all.size(); 
    }

    private:
    json j;
    json json_response;
    int count;
    double answer;
    double minum;
    double maxium;
    high_resolution_clock::time_point _start_time;
    high_resolution_clock::duration _elapsed;
    vector<double> duration_all;
};


#endif