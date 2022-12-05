#ifndef __DAY5_H__
#define __DAY5_H__

#include <day.h>
#include <util.h>

void moveFromStackToStack(int quantity, std::vector<char>* stack, std::vector<char>* newStack, bool preserveOrder) {
    for(int i = 0; i < quantity; i++) {
        newStack->insert(newStack->begin() + (preserveOrder ? i : 0), (*stack)[0]);
        stack->erase(stack->begin());
    }
}


class Day5 : AOC::Day {
public:
    static const int dayNum = 5;
    static const bool hasSecondInput = false;

    std::string partASolution = "";
    std::string partBSolution = "";

    using AOC::Day::Day;

    // debugging purposes 
    void printCrates(std::vector<std::vector<char>> crates) {
        for(size_t i = 0; i < crates.size(); i++) {
            for(int j = crates[i].size() - 1; j >= 0; j--) {
                printf("%c", crates[i][j]);
            }
            printf("\n");
        }
    } 

    std::vector<std::vector<char>> crates; 
    int idLine = -1;

    void partA() {
        std::vector<std::vector<char>> crates; 

        while(this->input.text[++idLine][1] != '1');

        for(size_t i = 0; i < this->input.text[idLine].size(); i++) {
            if(this->input.text[idLine][i] != ' ') {
                // set id to id - 1
                int stackID = (this->input.text[idLine][i] - 48) - 1;
                crates.push_back({});
                this->crates.push_back({});
                // loop through all the crates above the id

                for(int j = 0; j < idLine; j++) {
                    int crateID = this->input.text[j][i];
                    if(crateID == ' ' || crateID == '\0') continue;
                    
                    crates[stackID].push_back(crateID);
                    this->crates[stackID].push_back(crateID);
                }
            }
        }
        
        for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::string str = this->input.text[i];
            std::vector<std::string> splitStr = split(str, ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;

            moveFromStackToStack(quantity, &crates[moveFrom], &crates[moveTo], false);
        }

        for(std::vector<char> stack : crates) {
            partASolution += stack[0];
        }
    }

    void partB() {
        for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::string str = this->input.text[i];
            std::vector<std::string> splitStr = split(str, ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;

            moveFromStackToStack(quantity, &crates[moveFrom], &crates[moveTo], true);
        }
        
        for(std::vector<char> stack : crates) {
            partBSolution += stack[0];
        }
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%s\n", partASolution.c_str());
        printf("---- Part B ----\n");
        printf("%s\n", partBSolution.c_str());
        printf("----------------\n\n");
        
    }
};

#endif