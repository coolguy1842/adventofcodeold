#ifndef __DAY6_H__
#define __DAY6_H__

#include <day.h>
#include <util.h>

#include <stdio.h>

class Day6 : AOC::Day {
public:
    static const int dayNum = 6;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    void findUniqueSequence(size_t len, unit* positionOut) {
        char* curMarker = (char*)calloc(sizeof(char), len--);
        size_t curMarkerLen = 0;

        for(char& c : this->input.text[0]) {
            if(curMarkerLen > len) {
                bool success = true;

                for(size_t i = 0; i < curMarkerLen - 1; i++) {
                    if(success == false) break;

                    for(size_t j = i + 1; j < curMarkerLen; j++) {
                        if(curMarker[i] == curMarker[j]) {
                            success = false;
                            break;
                        }
                    }   
                }

                if(success) return;

                memmove(curMarker, curMarker + 1, sizeof(char) * len);
                curMarker[curMarkerLen - 1] = c;
            }
            else curMarker[curMarkerLen++] = c;
            
            (*positionOut)++;
        }

        free(curMarker);
    }

    void partA() {
        findUniqueSequence(4, &partASolution);
    }

    void partB() {
        findUniqueSequence(14, &partBSolution);  
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%lld\n", partASolution);
        printf("---- Part B ----\n");
        printf("%lld\n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif