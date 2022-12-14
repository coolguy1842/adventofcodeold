#ifndef __DAY_H__
#define __DAY_H__

#include <stdio.h>

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define unit long long int

namespace AOC {

struct input {
    std::vector<std::string> text;
    std::vector<unit> number;

    bool numberValid;
};

class Day {
private:
    void readInput(struct input* input, std::string file) {
        std::ifstream filestream(file);
        
        if(!filestream) {
            throw std::runtime_error("ERROR: Input file doesn't exist.\n");
        }

        input->numberValid = true;

        std::string line;
        while(std::getline(filestream, line)) {
            input->text.push_back(line);

            if(!input->numberValid) continue;
            
            std::stringstream sstream(line);

            unit number;
            sstream >> number;

            if(sstream.fail()) {
                input->numberValid = false;
                input->number.clear();
                input->number = {};
                
                continue;
            }

            input->number.push_back(number);
        }

        filestream.close();
    }
    
protected:
    struct input input;
    //struct input input2;

public:
    Day(std::string input) {//, std::string input2 = std::string()) {
        if(input.size() > 0) readInput(&this->input, input);
        //if(input2.size() > 0) readInput(&this->input2, input2);
    }

    ~Day() {}

    struct input getInput() { return this->input; }
    //struct input getInput2() { return this->input2; }

    void partA();
    void partB();

    void printResults();
};

};

#endif