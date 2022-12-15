#ifndef __DAY14_H__
#define __DAY14_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

class Day14 : AOC::Day {
public:
    static const int dayNum = 14;
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
        SOLID = 1,
        SAND = 2
    };

    robin_hood::unordered_flat_map<struct position, int, struct position> blocks = {};
    
    unit minX = __INT_MAX__;
    unit maxX = 0;
    
    unit minY = 0;
    unit maxY = 0;

    struct position sandDropPos = {500, 0};

    bool dropSand(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks, struct position sandPos, unit minX, unit maxX, unit minY, unit maxY) {
        while(blocks[sandPos] == AIR) {
            sandPos.y++;

            if(blocks[sandPos] != AIR) {
                if(blocks[{sandPos.x - 1, sandPos.y}] == AIR) {
                    sandPos.x--;
                }
                else if(blocks[{sandPos.x + 1, sandPos.y}] == AIR) {
                    sandPos.x++;
                }
                else {
                    sandPos.y--;
                    break;
                }
            }

            if(sandPos.y > maxY) return false;
            if(sandPos.y < minY) return false;

            if(sandPos.x > maxX) return false;
            if(sandPos.x < minX) return false;
        }

        if(sandPos.y <= minY) return false;

        blocks[sandPos] = SAND; 

        return true;
    }

    void printBlocks(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks, unit minX, unit maxX, unit minY, unit maxY) {
        for(unit y = minY; y <= maxY; y++) {
            for(unit x = minX; x <= maxX; x++) {
                switch(blocks[{x, y}]) {
                case AIR:
                    printf(".");
                    break;
                case SAND:
                    printf("O");
                    break;
                case SOLID:
                    printf("#");
                    break;
                default:
                    break;
                }
            }    

            printf("\n");
        }
    }

    void readInput(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks, unit& minX, unit& maxX, unit& minY, unit& maxY, bool partA = true) {
        blocks = {};
        
        for(std::string& str : this->input.text) {
            std::vector<std::string> positions = split(str, " -> ");
            unit prevX = __INT_MAX__;
            unit prevY = __INT_MAX__;
            
            for(std::string& pos : positions) {
                std::vector<std::string> vals = split(pos, ',');

                unit x = strtounit(vals[0].c_str());
                unit y = strtounit(vals[1].c_str());

                maxX = std::max(x, maxX);
                maxY = std::max(y, maxY);

                minX = std::min(x, minX);

                if(prevX == __INT_MAX__) {
                    prevX = x;
                    prevY = y;

                    continue;
                }

                for(unit i = std::min(prevX, x); i <= std::max(prevX, x); i++) {
                    for(unit j = std::min(prevY, y); j <= std::max(prevY, y); j++) {
                        struct position position = {i, j};

                        blocks[position] = SOLID;
                    }   
                }

                prevX = x;
                prevY = y;
            }
        }

        if(!partA) {
            maxY += 2;

            minX -= minX / 2;
            maxX += maxX / 2;

            for(unit x = minX; x <= maxX; x++) {
                blocks[{x, maxY}] = SOLID;
            }
        }
    }

    void partA() {
        readInput(this->blocks, minX, maxX, minY, maxY);
        size_t droppedSand = 0;

        while(dropSand(blocks, sandDropPos, minX, maxX, minY, maxY)) {

            droppedSand++;
        }

        partASolution = droppedSand;
    }

    void partB() {
        readInput(this->blocks, minX, maxX, minY, maxY, false);
        size_t droppedSand = 1;

        while(dropSand(blocks, sandDropPos, minX, maxX, minY, maxY)) {
            droppedSand++;
        }

        partBSolution = droppedSand;
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%llu\n", partASolution);
        printf("---- Part B ----\n");
        printf("%llu\n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif