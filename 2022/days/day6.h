#ifndef __DAY6_H__
#define __DAY6_H__

#include <day.h>
#include <util.h>

class Day6 : AOC::Day {
public:
    static const int dayNum = 6;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    void partA() {
        std::vector<char> curMarker;
        unit curChar = 0;

        for(char c : this->input.text[0]) {
            if(curMarker.size() > 3) {
                bool success = true;

                for(size_t i = 0; i < curMarker.size() - 1; i++) {
                    if(success == false) break;

                    for(size_t j = i + 1; j < curMarker.size(); j++) {
                        if(curMarker[i] == curMarker[j]) {
                            success = false;
                            break;
                        }
                    }   
                }

                if(success) {
                    printf("%c%c%c%c\n", curMarker[0], curMarker[1], curMarker[2], curMarker[3]);
                    partASolution = curChar;
                    return;
                }
            }

            if(curMarker.size() < 4) {
                curMarker.push_back(c);
            }
            else {
                curMarker.erase(curMarker.begin());
                curMarker.push_back(c);
            }
            curChar++;
        }
    }

    void partB() {
        std::vector<char> curMarker;
        unit curChar = 0;

        for(char c : this->input.text[0]) {
            if(curMarker.size() > 13) {
                bool success = true;

                for(size_t i = 0; i < curMarker.size() - 1; i++) {
                    if(success == false) break;

                    for(size_t j = i + 1; j < curMarker.size(); j++) {
                        if(curMarker[i] == curMarker[j]) {
                            success = false;
                            break;
                        }
                    }   
                }

                if(success) {
                    partBSolution = curChar;
                    return;
                }
            }

            if(curMarker.size() < 14) {
                curMarker.push_back(c);
            }
            else {
                curMarker.erase(curMarker.begin());
                curMarker.push_back(c);
            }

            curChar++;
        }
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