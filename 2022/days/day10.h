#ifndef __DAY10_H__
#define __DAY10_H__

#include <day.h>
#include <util.h>

#include <linkedList.h>

#include <robin_hood.h>

#include <Day10/CPU.h>

void noopFunction(std::vector<std::string>& args, class CPU* cpu) {}
void addXFunction(std::vector<std::string>& args, class CPU* cpu) {
    cpu->registers.x += strtoint(args[1].c_str()); 
}

class Day10 : AOC::Day {
public:
    static const int dayNum = 10;
    static const bool hasSecondInput = false;

    size_t partASolution = 0;
    size_t partBSolution = 0;

    using AOC::Day::Day;

    struct CPU cpu;

    void initCPU() {
        cpu = {};

        cpu.addInstruction("noop", 1, (instructionFunction)&noopFunction);
        cpu.addInstruction("addx", 2, (instructionFunction)&addXFunction);
    }

    void partA() {
        initCPU();

        std::vector<std::string> args;

        for(std::string& str : this->input.text) {
            args = split(str, ' ');

            cpu.run(args);
        }

        cpu.runningTask = &cpu.taskQueue.begin()->data;

        while(cpu.taskQueue.size() > 0) {
            cpu.process();
        }
    }

    void partB() {

    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%llu\n", cpu.strength);
        printf("---- Part B ----\n");
        cpu.display.printGrid();
        printf("----------------\n\n");
        
    }
};

#endif