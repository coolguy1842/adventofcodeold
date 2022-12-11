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

    void runOperationOnItem(std::vector<unit>::iterator& it, bool partA) {
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

        switch (partA) {
        case true: {
            *it /= 3;
            break;
        }
        default: {
            *it %= magicOperator;
            break;
        }
        }

        if(*it % test.divisibleBy != 0) {
            swapItem(it, this->test.falseMonkey);
            return;
        }

        swapItem(it, this->test.trueMonkey);
    }

    void printMonkey() {
        for(size_t item : this->items) {
            printf("%lld, ", item);
        }

        printf("\n");
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

    void partA() {
        std::vector<struct Monkey> monkeys;
        Monkey curMonkey = Monkey();

        size_t curLine = 0;

        for(std::string& str : this->input.text) {
            if(str.size() <= 0) {
                monkeys.push_back(curMonkey);

                curLine = -1;
                curMonkey = Monkey();
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

        monkeys.push_back(curMonkey);

        for(Monkey& monkey : monkeys) {
            monkey.test.falseMonkey = &monkeys[monkey.test.falseMonkeyNum];
            monkey.test.trueMonkey = &monkeys[monkey.test.trueMonkeyNum];
        }

        for(size_t runs = 0; runs < 20; runs++) {
            for(size_t i = 0; i < monkeys.size(); i++) {
                struct Monkey* monkey = &monkeys[i];

                for(auto it = monkey->items.begin(); it != monkey->items.end(); ) {
                    monkey->runOperationOnItem(it, true);
                }
            }
        }

        std::sort(monkeys.rbegin(), monkeys.rend(), monkeySortOperator());
        partASolution = monkeys[0].inspected * monkeys[1].inspected;
    }

    void partB() {
        std::vector<struct Monkey> monkeys;
        Monkey curMonkey = Monkey();

        size_t curLine = 0;

        for(std::string& str : this->input.text) {
            if(str.size() <= 0) {
                monkeys.push_back(curMonkey);

                curLine = -1;
                curMonkey = Monkey();
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

        monkeys.push_back(curMonkey);

        for(Monkey& monkey : monkeys) {
            monkey.test.falseMonkey = &monkeys[monkey.test.falseMonkeyNum];
            monkey.test.trueMonkey = &monkeys[monkey.test.trueMonkeyNum];
        }

        for(size_t runs = 0; runs < 10000; runs++) {
            for(size_t i = 0; i < monkeys.size(); i++) {
                struct Monkey* monkey = &monkeys[i];

                for(auto it = monkey->items.begin(); it != monkey->items.end(); ) {
                    monkey->runOperationOnItem(it, false);
                }
            }
        }

        for(Monkey monkey : monkeys) {
            monkey.printMonkey();
        }

        std::sort(monkeys.rbegin(), monkeys.rend(), monkeySortOperator());
        partBSolution = monkeys[0].inspected * monkeys[1].inspected;
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