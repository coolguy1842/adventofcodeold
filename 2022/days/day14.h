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
    robin_hood::unordered_flat_map<struct position, int, struct position> blocksB = {};
    
    unit minX = __INT_MAX__;
    unit maxX = 0;
    
    unit minY = 0;
    unit maxY = 0;

    struct position sandDropPos = {500, 0};

    bool dropSand(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks, struct position sandPos, unit& minX, unit& maxX, unit& minY, unit& maxY) {
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

            if(sandPos.x < minX || sandPos.x > maxX) return false;
        }

        if(sandPos.y == minY) return false;

        blocks[sandPos] = SAND; 

        return true;
    }

    bool dropSandB(robin_hood::unordered_flat_map<struct position, int, struct position>& blocks, struct position sandPos, unit& minX, unit& maxX, unit& minY, unit& maxY) {
        while(blocks[sandPos] == AIR) {
            if(sandPos.y == maxY) break;
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
                    
                    if(sandPos.y == minY) return false;
                    break;
                }
            }
        }

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

    void readInput() {
        std::vector<std::string> vals;
        for(std::string& str : this->input.text) {
            unit prevX = __INT_MAX__;
            unit prevY = __INT_MAX__;
            
            for(std::string& pos : split(str, " -> ")) {
                vals = split(pos, ',');

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
                        blocksB[position] = SOLID;
                    }   
                }

                prevX = x;
                prevY = y;
            }
        }
    }

    void partA() {
        readInput();
        
        while(dropSand(blocks, sandDropPos, minX, maxX, minY, maxY)) partASolution++;
    }

    void partB() {
        maxY++;
        
        minX -= (minX / 2);
        maxX += (maxX / 2);

        do {
            partBSolution++;
        } while(dropSandB(blocksB, sandDropPos, minX, maxX, minY, maxY));
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