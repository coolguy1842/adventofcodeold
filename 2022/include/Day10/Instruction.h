#ifndef __DAY10_INSTRUCTION_H__
#define __DAY10_INSTRUCTION_H__

#define unit long long int

#include <string>
#include <vector>

typedef void (*instructionFunction)(std::vector<std::string>& args, class CPU* cpu);

class Instruction {
public:
    std::string name;
    unit cycles; // cycles it takes to complete instruction

    instructionFunction execute;
    
    Instruction(std::string name, size_t cycles, instructionFunction execute) : name(name), cycles(cycles), execute(execute) {}

    // required by robinhood(not sure why)
    Instruction() {}
};

#endif