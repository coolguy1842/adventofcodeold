#ifndef __DAY2_H__
#define __DAY2_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

namespace RPS {
enum Outcomes {
    LOSE = 0,
    DRAW = 3,
    WIN = 6
};

enum shapeIDS {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2,
};

struct Shape {
    int id;
    int beatsID;
    int losesID;
    int score;
};

struct Shape shapes[3] = {
    {ROCK, SCISSORS, PAPER, 1},
    {PAPER, ROCK, SCISSORS, 2},
    {SCISSORS, PAPER, ROCK, 3},
};  

robin_hood::unordered_flat_map<char, struct Shape> shapesList = {
    {'A', shapes[ROCK]},
    {'B', shapes[PAPER]},
    {'C', shapes[SCISSORS]},
    
    {'X', shapes[ROCK]},
    {'Y', shapes[PAPER]},
    {'Z', shapes[SCISSORS]}
};

namespace PartB {
enum Actions {
    LOSE = 'X',
    DRAW = 'Y',
    WIN = 'Z',
};
};
};

class Day2 : AOC::Day {
public:
    static const int dayNum = 2;
    static const bool hasSecondInput = false;

    long long int partAScore = 0;
    long long int partBScore = 0;

    using AOC::Day::Day;

    void partA() {
        for(std::string& str : this->input.text) {
            struct RPS::Shape opponentShape = RPS::shapesList[str[0]];
            struct RPS::Shape counterShape = RPS::shapesList[str[2]];
            partAScore += counterShape.score;

            if(counterShape.beatsID == opponentShape.id) {
                // win
                partAScore += RPS::Outcomes::WIN;
            }
            else if(counterShape.losesID == opponentShape.id) {
                // loss
                partAScore += RPS::Outcomes::LOSE;
            }
            else {
                // draw
                partAScore += RPS::Outcomes::DRAW;
            }
        }
    }

    void partB() {
        for(std::string& str : this->input.text) {
            struct RPS::Shape opponentShape = RPS::shapesList[str[0]];
            
            switch(str[2]) {
            case RPS::PartB::Actions::WIN:
                partBScore += RPS::shapes[opponentShape.losesID].score + RPS::Outcomes::WIN;
                break;
            case RPS::PartB::Actions::DRAW:
                partBScore += opponentShape.score + RPS::Outcomes::DRAW;
                break;
            case RPS::PartB::Actions::LOSE:
                partBScore += RPS::shapes[opponentShape.beatsID].score + RPS::Outcomes::LOSE;
                break;
            default:
                break;
            };
        }
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("score: %lld\n", partAScore);
        printf("---- Part B ----\n");
        printf("SCORE: %lld\n", partBScore);
        printf("----------------\n\n");
    }
};

#endif