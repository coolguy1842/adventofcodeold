#ifndef __DAY8_H__
#define __DAY8_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

class Day8 : AOC::Day {
public:
    static const int dayNum = 8;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    enum direction {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };

    unit width = (unit)this->input.text[0].size();
    unit height = (unit)this->input.text.size();

    bool visibleFromDir(direction dir, unit x, unit y, unit* score) {
        char treeHeight = this->input.text[y][x];

        *score = 0;

        switch (dir) {
        case LEFT:
            for(x--; x >= 0; x--) {
                (*score)++;

                if(treeHeight <= this->input.text[y][x]) return false;
            }
            break;
        case RIGHT:
            for(x++; x < width; x++) {
                (*score)++;

                if(treeHeight <= this->input.text[y][x]) return false;
            }
            break;
        case UP:
            for(y--; y >= 0; y--) {
                (*score)++;

                if(treeHeight <= this->input.text[y][x]) return false;
            }
            break;
        case DOWN:
            for(y++; y < height; y++) {                
                (*score)++;

                if(treeHeight <= this->input.text[y][x]) return false;
            }
            break;
        default:
            break;
        }

        return true;
    }

    void partA() {
        unit scoreLeft = 0;
        unit scoreRight = 0;
        unit scoreUp = 0;
        unit scoreDown = 0;
        unit totalScore;
        bool visible = false;

        for(unit x = 1; x < width - 1; x++) {
            for(unit y = 1; y < height - 1; y++) {

                switch (this->input.text[y][x]) {
                case '0':
                    break;                
                default:
                    visible = visibleFromDir(LEFT, x, y, &scoreLeft);
                    visible = visibleFromDir(RIGHT, x, y, &scoreRight) ? true : visible;
                    visible = visibleFromDir(UP, x, y, &scoreUp) ? true : visible;
                    visible = visibleFromDir(DOWN, x, y, &scoreDown) ? true : visible;

                    if(visible) partASolution++;

                    totalScore = scoreLeft * scoreRight * scoreUp * scoreDown;
                    if(totalScore > partBSolution) partBSolution = totalScore;
                    break;
                }

            }
        }

        partASolution += ((width + height) * 2) - 4;
    }

    void partB() {

    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%lld \n", partASolution);
        printf("---- Part B ----\n");
        printf("%lld \n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif