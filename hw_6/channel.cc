#include <iostream>
#include <stdexcept>
#include "elma.h"

namespace elma {
    
    Channel& Channel::send(double value) {
        _queue.push_front(value);
        while ( _queue.size() >= capacity() ) {
            _queue.pop_back();
        }
        return *this;
    }

    Channel& Channel::flush(double) {
        _queue.clear();
        return *this;
    }

    vector<double> Channel::latest( int n ) {
        //deque<double> _copy_queue;
        vector<double> result;
        double nm;
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the latest value in an empty channel.");
        }
        if (_queue.size() < n){
            for(int i = 0 ; i<_queue.size(); i++){
                result.push_back(_queue[i]);
            }
        }else{
            for (int j = 0; j<n ;j++){
                result.push_back(_queue[j]);
            }
        }
        return result;
        
    }

    double Channel::earliest() {
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the earliest value in an empty channel.");
        }
        return _queue.back();        
    }

    void Channel::change_capacity(int c) {
        _capacity = c ;
        if (_queue.size() > c){
            for (int i = 0 ; i < c-_queue.size(); i ++){
                _queue.pop_back();
            }
        }
    }    
}