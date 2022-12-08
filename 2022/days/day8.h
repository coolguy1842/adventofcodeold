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

    bool visibleFromDir(direction dir, unit x, unit y) {
        char treeHeight = this->input.text[y][x];

        switch (dir) {
        case LEFT:
            for(unit i = 1; x - i >= 0; i++) {
                if(treeHeight <= this->input.text[y][x - i]) return false;
            }
            break;
        case RIGHT:
            for(unit i = 1; x + i < width; i++) {
                if(treeHeight <= this->input.text[y][x + i]) return false;
            }
            break;
        case UP:
            for(unit i = 1; y - i >= 0; i++) {
                if(treeHeight <= this->input.text[y - i][x]) return false;
            }
            break;
        case DOWN:
            for(unit i = 1; y + i < height; i++) {
                if(treeHeight <= this->input.text[y + i][x]) return false;
            }
            break;
        default:
            break;
        }

        return true;
    }

    void partA() {
        std::vector<std::string> text = this->input.text;

        unit visibleTrees = 0;

        for(unit x = 0; x < width; x++) {
            for(unit y = 0; y < height; y++) {
                if(x == 0 || x == width - 1) {
                    visibleTrees++;
                    continue;
                }
                else if(y == 0 || y == height - 1) {
                    visibleTrees++;
                    continue;
                }

                if(visibleFromDir(LEFT, x, y)) visibleTrees++;
                else if(visibleFromDir(RIGHT, x, y)) visibleTrees++;
                else if(visibleFromDir(UP, x, y)) visibleTrees++;
                else if(visibleFromDir(DOWN, x, y)) visibleTrees++;
            }
        }

        partASolution = visibleTrees;
    }

    unit scoreFromDir(direction dir, unit x, unit y) {
        char treeHeight = this->input.text[y][x];

        unit score = 0;

        switch (dir) {
        case LEFT:
            for(unit i = 1; x - i >= 0; i++) {
                score++;

                if(treeHeight <= this->input.text[y][x - i]) break;
            }
            break;
        case RIGHT:
            for(unit i = 1; x + i < width; i++) {
                score++;

                if(treeHeight <= this->input.text[y][x + i]) break;
            }
            break;
        case UP:
            for(unit i = 1; y - i >= 0; i++) {
                score++;

                if(treeHeight <= this->input.text[y - i][x]) break;
            }
            break;
        case DOWN:
            for(unit i = 1; y + i < height; i++) {
                score++;

                if(treeHeight <= this->input.text[y + i][x]) break;
            }
            break;
        default:
            break;
        }
        
        return score;
    }

    void partB() {
        std::vector<std::string> text = this->input.text;
        unit highestScore = 0;

        for(unit x = 0; x < width; x++) {
            for(unit y = 0; y < height; y++) {

                unit leftScore = scoreFromDir(LEFT, x, y);
                unit rightScore = scoreFromDir(RIGHT, x, y);
                unit upScore = scoreFromDir(UP, x, y);
                unit downScore = scoreFromDir(DOWN, x, y);

                if(leftScore * rightScore * upScore * downScore > highestScore) {
                    highestScore = treeScore;
                } 
            }
        }

        partBSolution = highestScore;
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