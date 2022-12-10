#ifndef __DAY9_H__
#define __DAY9_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

struct position {
    unit x = 0;
    unit y = 0;
    
    bool operator==(const position &other) const { 
        return (x == other.x && y == other.y);
    }
};

struct positionHasher {
    std::size_t operator()(const position& k) const {
        using std::hash;

        return ((hash<unit>()(k.x) ^ (hash<unit>()(k.y) << 1)) >> 1);
    }
};


enum Direction {
    LEFT = 'L',
    RIGHT = 'R',

    UP = 'U',
    DOWN = 'D',
};

struct knot {
    struct position position = {};
    
    robin_hood::unordered_flat_map<struct position, bool, positionHasher> prevPositions;

    void moveToNext(knot prev) {
        unit nextX = prev.position.x;
        unit nextY = prev.position.y;
        
        unit thisX = position.x;
        unit thisY = position.y;

        if(std::abs(nextX - thisX) > 1 || std::abs(nextY - thisY) > 1) {
            if(nextX != thisX) position.x += (thisX < nextX ? 1 : -1);
            if(nextY != thisY) position.y += (thisY < nextY ? 1 : -1);
        }
        
        prevPositions[position] = true;
    }

    void move(char dir) {
        switch(dir) {
        case LEFT:
            position.x -= 1;
            break;
        case RIGHT:
            position.x += 1;
            break;
        case UP:
            position.y -= 1;
            break;
        case DOWN:
            position.y += 1;
            break;
        default:
            break;
        }
        
        prevPositions[position] = true;
    }
};

class Day9 : AOC::Day {
public:
    static const int dayNum = 9;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    void partA() {
        struct knot head = {};
        struct knot tail = {};

        for(std::string& str : this->input.text) {
            std::vector<std::string> splitStr = split(str, ' ');
            
            size_t amount = strtoull(splitStr[1].c_str());
            for(size_t i = 0; i < amount; i++) {
                head.move(str[0]);

                tail.moveToNext(head);
            }
        }

        partASolution = (unit)tail.prevPositions.size();
    }

    void partB() {
#define knotsCount 10

        std::vector<knot> knots = {};

        for(size_t i = 0; i < knotsCount; i++) {
            struct knot knot = {};
            knots.push_back(knot);
        }

        for(std::string& str : this->input.text) {
            std::vector<std::string> splitStr = split(str, ' ');
            size_t amount = strtoull(splitStr[1].c_str());

            for(size_t i = 0; i < amount; i++) {
                knots[0].move(str[0]);

                for(size_t j = 1; j < knots.size(); j++) {
                    knots[j].moveToNext(knots[j - 1]);
                }
            }
        }

        partBSolution = (unit)knots[knotsCount - 1].prevPositions.size();
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