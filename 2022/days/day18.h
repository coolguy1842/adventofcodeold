#ifndef __DAY18_H__
#define __DAY18_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

class Day18 : AOC::Day {
public:
    static const int dayNum = 18;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    struct position {
        unit x;
        unit y;
        unit z;

        
        bool operator==(const position& p) const { 
            return (this->x == p.x && this->y == p.y && this->z == p.z);
        }
        
        std::size_t operator()(const position& p) const {
            return (((size_t)p.x << 32) ^ (size_t)p.y) | (size_t)p.z;
        }
    };

    robin_hood::unordered_flat_map<struct position, bool, struct position> blocks = {};
    robin_hood::unordered_flat_map<struct position, bool, struct position> airSpaces = {};

    void readInput() {
        for(std::string& line : this->input.text) {
            std::vector<std::string> splitStr = split(line, ',');

            unit x = strtounit(splitStr[0].c_str());
            unit y = strtounit(splitStr[1].c_str());
            unit z = strtounit(splitStr[2].c_str());

            blocks[{x, y, z}] = true;
        }
    }

    size_t checkBlockSides(struct position position) {
        size_t total = 0;

        if(blocks.find({position.x - 1, position.y, position.z}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x - 1, position.y, position.z}] = true;
        }

        if(blocks.find({position.x + 1, position.y, position.z}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x + 1, position.y, position.z}] = true;
        }


        if(blocks.find({position.x, position.y - 1, position.z}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x, position.y - 1, position.z}] = true;
        }
        
        if(blocks.find({position.x, position.y + 1, position.z}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x, position.y + 1, position.z}] = true;
        }
        

        if(blocks.find({position.x, position.y, position.z - 1}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x, position.y, position.z - 1}] = true;
        }
        
        if(blocks.find({position.x, position.y, position.z + 1}) == blocks.end()) {
            total++;
            
            airSpaces[{position.x, position.y, position.z + 1}] = true;
        }
        

        return total;
    }

    size_t checkAirSpaces(struct position position) {
        size_t total = 0;
        
        if(blocks.find({position.x - 1, position.y, position.z}) == blocks.end()) return 0;
        if(blocks.find({position.x + 1, position.y, position.z}) == blocks.end()) return 0;

        if(blocks.find({position.x, position.y - 1, position.z}) == blocks.end()) return 0;
        if(blocks.find({position.x, position.y + 1, position.z}) == blocks.end()) return 0;

        if(blocks.find({position.x, position.y, position.z - 1}) == blocks.end()) return 0;
        if(blocks.find({position.x, position.y, position.z + 1}) == blocks.end()) return 0;


        return total;
    }

    void partA() {
        readInput();

        size_t total = 0;
        for(auto& pair : blocks) {
            total += checkBlockSides(pair.first);
        }

        partASolution = total;
    }

    void partB() {
        size_t total = 0;
        for(auto& pair : airSpaces) {
            total += checkAirSpaces(pair.first);
        }

        partBSolution = total;
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%llu\n", partASolution);
        //printf("---- Part B ----\n");
        //printf("\n");
        printf("----------------\n\n");
        
    }
};

#endif