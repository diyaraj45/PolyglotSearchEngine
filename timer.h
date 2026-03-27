#pragma once
#include <chrono>
#include <iostream>
using namespace std;

class Timer{
private:
    // Chrono start time setup
    chrono::high_resolution_clock::time_point start_time;
public:
    // Start function: starts the timer
    void start(){
        start_time = chrono::high_resolution_clock::now();
    }
    // Stop function: resulting time from start to end
    // long long used due to use of int start and int end whose product could result in a value of bits greater than those subtracted
    long long stop(){
        //End: timers end time
        auto end_time = chrono::high_resolution_clock::now();

        // Duration from start to finish by subrtracting estart time from end time
        return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    }
};