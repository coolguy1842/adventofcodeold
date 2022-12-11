#ifndef __DAY5_H__
#define __DAY5_H__

#include <day.h>
#include <util.h>

#include <linkedList.h>

class Day5 : AOC::Day {
public:
    static const int dayNum = 5;
    static const bool hasSecondInput = false;

    std::string partASolution = "";
    std::string partBSolution = "";

    using AOC::Day::Day;

    void moveFromStackToStack(int quantity, linkedList<char>& stack, linkedList<char>& newStack, bool preserveOrder) {
        switch(preserveOrder) {
        case true:
            for(int i = 0; i < quantity; i++) {
                char c = stack.pop_front();
                newStack.insert(i, c);
            }
            break;
        default:
            for(int i = 0; i < quantity; i++) {
                char c = stack.pop_front();
                newStack.push_front(c);
            }
            break;
        }
    }

    void printStack(linkedList<char>& stack) {
        linkedList<char>::part* part = stack.begin();

        for(size_t i = 0; i < stack.size(); i++) {
            printf("%c", part->data);
            part = part->next;
        }

        printf("\n");
    }

    void printCrates(linkedList<linkedList<char>>& crates) {
        linkedList<linkedList<char>>::part* part = crates.begin();

        for(size_t i = 0; i < crates.size(); i++) {
            printStack(part->data);

            part = part->next;
        }
    }

    int idLine = -1;
    linkedList<linkedList<char>> cratesA; 
    linkedList<linkedList<char>> cratesB; 

    void partA() {
        while(this->input.text[++idLine][1] != '1');

        for(size_t i = this->input.text[idLine].size() - 1; i > 0; i--) {
            if(this->input.text[idLine][i] == ' ') continue;

            linkedList<char> listA = linkedList<char>();
            linkedList<char> listB = linkedList<char>();

            for(int j = 0; j < idLine; j++) {
                char crateID = this->input.text[j][i];
                if(crateID == ' ' || crateID == '\0') continue;

                listA.push_back(crateID);
                listB.push_back(crateID);
            }
            
            cratesA.push_front(listA);
            cratesB.push_front(listB);
        }
        

        for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::vector<std::string> splitStr = split(this->input.text[i], ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;

            moveFromStackToStack(quantity, cratesA[moveFrom], cratesA[moveTo], false);
        }
        
        linkedList<linkedList<char>>::part* partPtr = cratesA.begin(); 
        for(size_t i = 0; i < cratesA.size(); i++) {
            partASolution += partPtr->data[0];
            partPtr = partPtr->next;
        }
    }

    void partB() {
        for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::vector<std::string> splitStr = split(this->input.text[i], ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;

            moveFromStackToStack(quantity, cratesB[moveFrom], cratesB[moveTo], true);
        }
        
        linkedList<linkedList<char>>::part* partPtr = cratesB.begin(); 
        for(size_t i = 0; i < cratesB.size(); i++) {
            partBSolution += partPtr->data[0];
            partPtr = partPtr->next;
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