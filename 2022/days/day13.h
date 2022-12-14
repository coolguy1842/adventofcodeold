#ifndef __DAY13_H__
#define __DAY13_H__

#include <day.h>
#include <util.h>

#include <variant>

class Day13 : AOC::Day {
public:
    static const int dayNum = 13;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    enum valueTypes {
        LIST = 0,
        VALUES
    };

    struct packetValue {
        size_t type;
        void* value;
    };

    struct packet {
        std::vector<struct packetValue> values;
    };
    
    struct packetPair {
        struct packet left;
        struct packet right;
    };

    std::vector<packetPair> packetPairs;

    struct packet readPacketStr(std::string packetStr) {
        size_t nestLevel = 0;

        struct packet packet;
        
        for(size_t i = 1; i < packetStr.size() - 1; i++) {
            if(packetStr[i] == '[') {
                nestLevel++;
            }
            else if(packetStr[i] == ']') {
                nestLevel--;
            }
        }

        return packet;
    }

    void partA() {
        
    }

    void partB() {

    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("\n");
        //printf("---- Part B ----\n");
        //printf("\n");
        printf("----------------\n\n");
        
    }
};

#endif