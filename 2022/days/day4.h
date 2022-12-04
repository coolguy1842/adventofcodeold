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

    bool overlaps(int position, int min, int max) {
        return position >= min && position <= max;
    }

    bool anyOverlap(int min, int max, int overlapMin, int overlapMax) {
        return (min >= overlapMin && min <= overlapMax) || (max >= overlapMin && max <= overlapMax);
    }

    bool fullyOverlaps(int min, int max, int overlapMin, int overlapMax) {
        return (min >= overlapMin && min <= overlapMax) && (max >= overlapMin && max <= overlapMax);
    }

    struct pair {    
        struct range {
            int min;
            int max;
        };
        
        struct range first;
        struct range second;
    };

    std::vector<struct pair> sections;

    void partA() {
        for(std::string& str : this->input.text) {
            // biggest thing i want to change but not sure what to do instead
            std::vector<std::string> splitStr = split(str, ',');
            std::vector<std::string> splitSection1 = split(splitStr[0], '-');
            std::vector<std::string> splitSection2 = split(splitStr[1], '-');

            int section1Min = strtoint(splitSection1[0].c_str());
            int section1Max = strtoint(splitSection1[1].c_str());

            int section2Min = strtoint(splitSection2[0].c_str());
            int section2Max = strtoint(splitSection2[1].c_str());

            // put into vector so it doesn't have to be calculated again
            sections.push_back({{section1Min, section1Max}, {section2Min, section2Max}});

            if(fullyOverlaps(section1Min, section1Max, section2Min, section2Max)) partASolution++;
            else if(fullyOverlaps(section2Min, section2Max, section1Min, section1Max)) partASolution++;
        }
    }

    void partB() {
        for(struct pair& pair : sections) {
            if(anyOverlap(pair.first.min, pair.first.max, pair.second.min, pair.second.max)) partBSolution++;
            else if(anyOverlap(pair.second.min, pair.second.max, pair.first.min, pair.first.max)) partBSolution++;
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