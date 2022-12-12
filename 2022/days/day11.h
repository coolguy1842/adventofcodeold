#ifndef __DAY11_H__
#define __DAY11_H__

#include <day.h>
#include <util.h>

#include <algorithm>

static size_t magicOperator = 1;

enum Action {
    MUL = '*',
    ADD = '+',
};

class Monkey {
public:
    struct Operation {
        char action;

        unit actionValue;
        bool valueIsSelf = false;
    } operation;

    struct Test {
        int divisibleBy;

        size_t trueMonkeyNum;
        size_t falseMonkeyNum;
        Monkey* trueMonkey;
        Monkey* falseMonkey;
    } test;

    std::vector<unit> items;
    size_t inspected;

    Monkey() {
        this->inspected = 0;
        this->items = {};
        this->test = {};
        this->operation = {};
    }

    void swapItem(std::vector<unit>::iterator& it, Monkey* newMonkey) {
        newMonkey->items.push_back(*it);
        it = this->items.erase(it);
    }

    void runOperationOnItemA(std::vector<unit>::iterator& it) {
        this->inspected++;

        switch (this->operation.valueIsSelf) {
        case true:
            switch (this->operation.action) {
            case MUL: *it *= *it; break;
            case ADD: *it += *it; break;
            default:
                break;
            }
            break;
        default:
            switch (this->operation.action) {
            case MUL: *it *= this->operation.actionValue; break;
            case ADD: *it += this->operation.actionValue; break;
            default:
                break;
            }
            break;
        }

        *it /= 3;

        if(*it % test.divisibleBy != 0) {
            swapItem(it, this->test.falseMonkey);
            return;
        }

        swapItem(it, this->test.trueMonkey);
    }
    
    void runOperationOnItemB(std::vector<unit>::iterator& it) {
        this->inspected++;

        if(this->operation.valueIsSelf) {
            switch (this->operation.action) {
            case MUL: *it *= *it; break;
            case ADD: *it += *it; break;
            default:
                break;
            }
        }
        else {
            switch (this->operation.action) {
            case MUL: *it *= this->operation.actionValue; break;
            case ADD: *it += this->operation.actionValue; break;
            default:
                break;
            }
        }

        *it %= magicOperator;

        if(*it % test.divisibleBy != 0) {
            swapItem(it, this->test.falseMonkey);
            return;
        }

        swapItem(it, this->test.trueMonkey);
    }
};

struct monkeySortOperator {
    inline bool operator() (const Monkey& monkey1, const Monkey& monkey2) {
        return (monkey1.inspected < monkey2.inspected);
    }
};

class Day11 : AOC::Day {
public:
    static const int dayNum = 11;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;


    using AOC::Day::Day;
    std::vector<struct Monkey> monkeysA;
    std::vector<struct Monkey> monkeysB;

    void partA() {
        Monkey curMonkey = Monkey();

        size_t curLine = 0;

        for(std::string& str : this->input.text) {
            if(str.size() <= 0) {
                monkeysA.push_back(curMonkey);

                curLine = -1;
                curMonkey.items.clear();
                curMonkey.operation.valueIsSelf = false;
            }
            else {
                switch(curLine) {
                case 1: {
                    for(std::string& str2 : split(split(str, ": ")[1], ", ")) {
                        curMonkey.items.push_back(strtounit(str2.c_str()));
                    }
                    break;
                }
                case 2: {
                    std::vector<std::string> splitStr = split(split(str, " = ")[1], ' ');

                    if(splitStr[2] == "old") curMonkey.operation.valueIsSelf = true;
                    else curMonkey.operation.actionValue = strtoint(splitStr[2].c_str());
                    
                    curMonkey.operation.action = splitStr[1][0];
                    break;
                }
                case 3: {
                    curMonkey.test.divisibleBy = strtoint(split(str, "y ")[1].c_str());
                    magicOperator *= curMonkey.test.divisibleBy;

                    break;
                }
                case 4: {
                    curMonkey.test.trueMonkeyNum = strtoull(split(str, "y ")[1].c_str());
                    break;
                }
                case 5: {
                    curMonkey.test.falseMonkeyNum = strtoull(split(str, "y ")[1].c_str());
                    break;
                }
                default:
                    break;
                }
            }

            curLine++;
        }
        monkeysA.push_back(curMonkey);
        
        monkeysB = monkeysA;

        for(Monkey& monkey : monkeysA) {
            monkey.test.falseMonkey = &monkeysA[monkey.test.falseMonkeyNum];
            monkey.test.trueMonkey = &monkeysA[monkey.test.trueMonkeyNum];
        }

        for(size_t runs = 0; runs < 20; runs++) {
            for(Monkey& monkey : monkeysA) {
                for(auto it = monkey.items.begin(); it != monkey.items.end(); ) {
                    monkey.runOperationOnItemA(it);
                }
            }
        }

        size_t highest[2] = {0, 0};

        for(Monkey& monkey : monkeysA) {
            if(monkey.inspected > highest[0]) {
                highest[1] = highest[0];
                highest[0] = monkey.inspected;
            }
            else if(monkey.inspected > highest[1]) {
                highest[1] = monkey.inspected;
            }
        }

        partASolution = highest[0] * highest[1];
    }

    void partB() {
        for(Monkey& monkey : monkeysB) {
            monkey.test.falseMonkey = &monkeysB[monkey.test.falseMonkeyNum];
            monkey.test.trueMonkey = &monkeysB[monkey.test.trueMonkeyNum];
        }

        for(size_t runs = 0; runs < 10000; runs++) {
            for(Monkey& monkey : monkeysB) {
                for(auto it = monkey.items.begin(); it != monkey.items.end(); ) {
                    monkey.runOperationOnItemB(it);
                }
            }
        }

        size_t highest[2] = {0, 0};

        for(Monkey& monkey : monkeysB) {
            if(monkey.inspected > highest[0]) {
                highest[1] = highest[0];
                highest[0] = monkey.inspected;
            }
            else if(monkey.inspected > highest[1]) {
                highest[1] = monkey.inspected;
            }
        }

        partBSolution = highest[0] * highest[1];
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