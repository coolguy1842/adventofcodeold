#ifndef __DAY5_H__
#define __DAY5_H__

#include <day.h>
#include <util.h>

class Day5 : AOC::Day {
public:
    static const int dayNum = 5;
    static const bool hasSecondInput = false;

    std::string partASolution = "";
    std::string partBSolution = "";

    using AOC::Day::Day;

    struct crateStruct {
        struct crateStruct* prev;
        char c;
        struct crateStruct* next;
    };
    
    struct crateList {
        struct crateStruct* listStart;
        struct crateStruct* listEnd;
        
        size_t size = 0;

        void push_back(char c) {
            struct crateStruct* crate = new struct crateStruct;
            crate->prev = listEnd;
            crate->c = c;

            if(size++ == 0) {
                listStart = crate;
                listEnd = crate;
                
                return;
            }
            
            listEnd->next = crate;
            listEnd = crate;
        }
        
        void push_front(char c) {
            struct crateStruct* crate = new struct crateStruct;
            crate->prev = listStart;
            crate->c = c;

            if(size++ == 0) {
                listStart = crate;
                listEnd = crate;
                
                return;
            }
            
            listStart->prev = crate;
            listStart = crate;
        }

        char pop_back() {
            size--;
            char c = listEnd->c;

            struct crateStruct* prevEnd = listEnd;
            listEnd = prevEnd->prev;
            delete prevEnd;

            listEnd->next = nullptr;
            return c;
        }
        
        char pop_front() {
            size--;
            char c = listStart->c;

            struct crateStruct* prevStart = listStart;
            listStart = prevStart->next;
            delete prevStart;

            listStart->prev = nullptr;
            return c;
        }
    };
    
    void moveFromStackToStack(int quantity, struct crateList* stack, struct crateList* newStack) {
        for(int i = 0; i < quantity; i++) {
            //printf("%d\n", stack->size);
            char c = stack->pop_back();
            newStack->push_back(c);
        }
    }


    void printCrates(std::vector<struct crateList> crates) {
        for(struct crateList stack : crates) {
            struct crateStruct* curCrate = stack.listEnd;
            
            for(size_t i = 0; i < stack.size; i++) {
                printf("%c", curCrate->c);

                curCrate = curCrate->prev;
            }

            printf("\n");
        }
    }

    // copy for partB
    //std::vector<struct crateList> crates; 
    int idLine = -1;

    void partA() {
        std::vector<struct crateList> crates; 

        while(this->input.text[++idLine][1] != '1');

        for(size_t i = this->input.text[idLine].size() - 1; i > 0; i--) {
            if(this->input.text[idLine][i] == ' ') continue;

            // set id to id - 1
            //int stackID = this->input.text[idLine][i] - 49;

            struct crateList list;

            // loop through all the crates above the id
            for(int j = 0; j < idLine; j++) {
                char crateID = this->input.text[j][i];
                if(crateID == ' ' || crateID == '\0') continue;

                list.push_back(crateID);
            }
            
            crates.push_back(list);
        }
        
        for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::vector<std::string> splitStr = split(this->input.text[i], ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;


            printf("\n\n");
            printCrates(crates);
            moveFromStackToStack(quantity, &crates[moveFrom], &crates[moveTo]);//, false);
        }

        printf("\n\n");
        printCrates(crates);
        printf("t\n");
        //for(std::vector<char>& stack : crates) partASolution += stack[0];
    }

    void partB() {
        /*for(size_t i = idLine + 2; i < this->input.text.size(); i++) {
            std::vector<std::string> splitStr = split(this->input.text[i], ' ');

            int quantity = strtoint(splitStr[1].c_str());
            int moveFrom = strtoint(splitStr[3].c_str()) - 1;
            int moveTo = strtoint(splitStr[5].c_str()) - 1;

            moveFromStackToStack(quantity, &crates[moveFrom], &crates[moveTo], true);
        }
        
        for(std::vector<char>& stack : crates) partBSolution += stack[0];*/
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