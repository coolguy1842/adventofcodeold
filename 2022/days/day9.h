#ifndef __DAY9_H__
#define __DAY9_H__

#include <day.h>
#include <util.h>

#include <bit>

#include <robin_hood.h>


enum Direction {
    LEFT = 'L',
    RIGHT = 'R',

    UP = 'U',
    DOWN = 'D',
};

struct knot {
    struct position {
        int x = 0;
        int y = 0;
        
        bool operator==(const position& p) const { 
            return (this->x == p.x && this->y == p.y);
        }
        
        std::size_t operator()(const position& p) const {
            return ((size_t)p.x << 32) | (size_t)p.y;
        }
    };
    
    struct position position;
    
    robin_hood::unordered_flat_map<struct position, bool, struct position> prevPositions;

    void moveToKnot(struct position& knotPos) {
        unit knotX = knotPos.x;
        unit knotY = knotPos.y;

        unit thisX = position.x;
        unit thisY = position.y;

        if(std::abs(knotX - thisX) > 1 || std::abs(knotY - thisY) > 1) {
            if(knotX != thisX) position.x += (thisX < knotX ? 1 : -1);
            if(knotY != thisY) position.y += (thisY < knotY ? 1 : -1);
        }
        
        prevPositions[position] = true;
    }

    void move(char& dir) {
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

    size_t partASolution = 0;
    size_t partBSolution = 0;

    using AOC::Day::Day;

    std::vector<size_t> amounts;

    void partA() {
        struct knot head = {};
        struct knot tail = {};

        std::vector<std::string> splitStr;
        size_t amount, i;

        for(std::string& str : this->input.text) {
            splitStr = split(str, ' ');
            
            amount = strtoull(splitStr[1].c_str());
            amounts.push_back(amount);

            for(i = 0; i < amount; i++) {
                head.move(str[0]);

                tail.moveToKnot(head.position);
            }
        }

        partASolution = tail.prevPositions.size();
    }

    void partB() {
        #define knotsCount 10U

        knot knots[knotsCount];
        size_t i = 0, j, k;

        for(std::string& str : this->input.text) {
            for(j = 0; j < amounts[i]; j++) {
                knots[0].move(str[0]);

                for(k = 1; k < knotsCount; k++) {
                    knots[k].moveToKnot(knots[k - 1].position);
                }
            }

            i++;
        }

        partBSolution = knots[knotsCount - 1].prevPositions.size();
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