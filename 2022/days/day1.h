#ifndef __DAY1_H__
#define __DAY1_H__

#include <day.h>
#include <util.h>

#include <algorithm>

class Day1 : AOC::Day {
public:
    static const int dayNum = 1;
    static const bool hasSecondInput = false;

    using AOC::Day::Day;
 
    std::vector<unit> elves;

    void partA() {
        unit num = 0;

        for(std::string& str : this->input.text) {
            switch(str.size()) {
            case 0:
                this->elves.push_back(num);
                num = 0;
                
                break;
            default:
                num += atoll(str.c_str());
                
                break;
            }
        }

        this->elves.push_back(num);
        std::sort(this->elves.rbegin(), this->elves.rend());
    }
    
    void partB() {}

    void printResults() {
        printf("---- Part A ----\n");
        printf("%lld\n", elves[0]);
        printf("---- Part B ----\n");
        printf("%lld + %lld + %lld = %lld\n", elves[0], elves[1], elves[2], elves[0] + elves[1] + elves[2]);
        printf("----------------\n\n");
        
    }
};

#endif