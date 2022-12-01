#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <string>
#include <time.h>

namespace AOC {
    
class Timer {
private:
    std::string name;

    struct timespec startTime, stopTime;
    bool hasStart, hasStop;

public:
    Timer(std::string name = "timer") : name(name) {}
    ~Timer() {}

    void start() {
        clock_gettime(CLOCK_REALTIME, &startTime);

        this->hasStart = true;
        this->hasStop = false;
    }
    
    void stop() {
        if(!this->hasStart) return;
        
        clock_gettime(CLOCK_REALTIME, &stopTime);
        this->hasStop = true;
    }

    void print() {
        if(!this->hasStop) this->stop();

        long nanoseconds = stopTime.tv_nsec - startTime.tv_nsec;
        nanoseconds += (stopTime.tv_sec - startTime.tv_sec) * 1e+9;

        printf("--- %s ---\n", this->name.c_str());
        printf("seconds: %f\n", (double)nanoseconds / 1e+9);
        printf("milliseconds: %f\n", (double)nanoseconds / 1e+6);
        printf("microseconds: %f\n", (double)nanoseconds / 1000);
        printf("nanoseconds: %ld\n", nanoseconds);

        std::string temp = "";
        for(size_t i = 0; i < this->name.size(); i++) temp += "-";
        printf("----%s----\n", temp.c_str());
    }
};

};

#endif