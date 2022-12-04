#ifndef __DAY4_H__
#define __DAY4_H__

#include <day.h>
#include <util.h>

class Day4 : AOC::Day {
public:
    static const int dayNum = 4;
    static const bool hasSecondInput = false;

    using AOC::Day::Day;

    unit partASolution = 0;
    unit partBSolution = 0;

    void partA() {
        unit overlaps = 0;

        for(std::string& str : this->input.text) {
            std::vector<std::string> splitStr = split(str, ',');
            std::vector<std::string> splitSection1 = split(splitStr[0], '-');
            std::vector<std::string> splitSection2 = split(splitStr[1], '-');

            int splitSection1Min = std::stoi(splitSection1[0]);
            int splitSection1Max = std::stoi(splitSection1[1]);

            int splitSection2Min = std::stoi(splitSection2[0]);
            int splitSection2Max = std::stoi(splitSection2[1]);

            if(splitSection1Min >= splitSection2Min && splitSection1Max <= splitSection2Max) {
                // first section is fully captured by the second section
                overlaps++;
            }
            else if(splitSection2Min >= splitSection1Min && splitSection2Max <= splitSection1Max) {
                // second section is fully captured by the first section
                overlaps++;
            }
        }

        partASolution = overlaps;
    }

    void partB() {
        unit overlaps = 0;

        for(std::string& str : this->input.text) {
            std::vector<std::string> splitStr = split(str, ',');
            std::vector<std::string> splitSection1 = split(splitStr[0], '-');
            std::vector<std::string> splitSection2 = split(splitStr[1], '-');

            int splitSection1Min = std::stoi(splitSection1[0]);
            int splitSection1Max = std::stoi(splitSection1[1]);

            int splitSection2Min = std::stoi(splitSection2[0]);
            int splitSection2Max = std::stoi(splitSection2[1]);

            if(splitSection1Min >= splitSection2Min && splitSection1Min <= splitSection2Max) {
                // first section is fully captured by the second section
                overlaps++;
            }
            else if(splitSection2Min >= splitSection1Min && splitSection2Min <= splitSection1Max) {
                // first section is fully captured by the second section
                overlaps++;
            }
            else if(splitSection1Max >= splitSection2Min && splitSection1Max <= splitSection2Max) {
                // first section is fully captured by the second section
                overlaps++;
            }
            else if(splitSection2Max >= splitSection1Min && splitSection2Max <= splitSection1Max) {
                // first section is fully captured by the second section
                overlaps++;
            }
        }

        partBSolution = overlaps;
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