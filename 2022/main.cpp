#include <stdio.h>

#include <days.h>
#include <util.h>
#include <timer.h>

#include <iostream>

#define currentDay Day3

#define showResults true
#define showTimers false

int main() {    
    AOC::Timer partBTimer("Part B");
    AOC::Timer partATimer("Part A");
    
    char inputStr[22];
    char inputStrB[23];

    sprintf(inputStr, ".\\dayinputs\\%d\\input", currentDay::dayNum);
    if(currentDay::hasSecondInput) sprintf(inputStr, ".\\dayinputs\\%d\\inputB", currentDay::dayNum);
    
    currentDay* day;

    if(currentDay::hasSecondInput) day = new currentDay(inputStr, inputStrB);
    else day = new currentDay(inputStr);

    partATimer.start();
    day->partA();
    partATimer.stop();

    partBTimer.start();
    day->partB();
    partBTimer.stop();
    
#if(showResults == true)
    day->printResults();
#endif

#if(showTimers == true)
        partATimer.print();
        partBTimer.print();
#endif

    delete day;
    return 0;
}