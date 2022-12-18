#ifndef __DAY15_H__
#define __DAY15_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

class Day15 : AOC::Day {
public:
    static const int dayNum = 15;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    struct position {
        unit x, y;

        bool operator==(const position& p) const { 
            return (this->x == p.x && this->y == p.y);
        }
        
        std::size_t operator()(const position& p) const {
            return ((size_t)p.x << 32) | (size_t)p.y;
        }
    };

    enum blockTypes {
        AIR = 0,
        SENSOR = 1,
        BEACON = 2
    };

    struct sensor {
        struct position closestBeacon;
    };

    robin_hood::unordered_flat_map<struct position, int, struct position> blocks = {};
    robin_hood::unordered_flat_map<struct position, struct sensor, struct position> sensors = {};

    int distanceFromPos(struct position& src, struct position& dest) {
        return std::abs(src.x - dest.x) + std::abs(src.y - dest.y);
    }

    void readInput(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks) {
        blocks = {};

        for(std::string& str : this->input.text) {
            std::string newStr = replace(replace(str, ",", ""), ":", "");
            std::vector<std::string> splitStr = split(newStr, ' ');

            unit sensorX = strtounit(split(splitStr[2], '=')[1].c_str());
            unit sensorY = strtounit(split(splitStr[3], '=')[1].c_str());

            unit beaconX = strtounit(split(splitStr[8], '=')[1].c_str());
            unit beaconY = strtounit(split(splitStr[9], '=')[1].c_str());

            blocks[{sensorX, sensorY}] = SENSOR;
            blocks[{beaconX, beaconY}] = BEACON;
        }
    }

    void partA() {
        readInput(blocks);
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