#ifndef __DAY10_H__
#define __DAY10_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

#define INVALID_ID 0U - 1
unit strength;

typedef void (*instructionFunction)(std::vector<std::string>& args, class CPU* cpu);

class Instruction {
public:
    std::string name;
    unit cycles; // cycles it takes to complete instruction

    instructionFunction execute;
    
    Instruction(std::string name, size_t cycles, instructionFunction execute) : name(name), cycles(cycles), execute(execute) {

    }

    // required by robinhood(not sure why)
    Instruction() {

    }
};

#define CRT_WIDTH 40
#define CRT_HEIGHT 6

struct CRT {
public:
    char grid[CRT_HEIGHT][CRT_WIDTH + 1];

    void updateGrid(size_t rdtsc, unit x) {
        size_t pos = rdtsc % 40;
        size_t curCol = rdtsc / 40;

        switch(std::abs((unit)pos - x)) {
        case 0: case 1:
            grid[curCol][pos] = '#';
            break;
        default:
            grid[curCol][pos] = '.';
            break;
        }
    }

    void printGrid() {
        for(size_t i = 0; i < CRT_HEIGHT; i++) {
            grid[i][CRT_WIDTH] = '\0';
            printf("%s\n", grid[i]);
        }
    }
};

class CPU {
public:
    struct Task {
        Instruction instruction;
        std::vector<std::string> args;
        unit cycles;

        Task(struct Instruction instruction, std::vector<std::string> args) : instruction(instruction), args(args) {
            this->cycles = instruction.cycles;
        }
    };

    unit x = 1;

    std::vector<class Task> taskQueue;
    class Task* runningTask;

    bool activeTask = false;

    size_t rdtsc = 0;

    robin_hood::unordered_flat_map<size_t, class Instruction> instructions;
    robin_hood::unordered_flat_map<std::string, size_t> instructionsIdLookup;

    void processA(size_t& strength) {
        if(!activeTask) {
            runningTask = &taskQueue[0];

            activeTask = true;
        }

        display.updateGrid(rdtsc, x);
        rdtsc++;
        
        if(((unit)this->rdtsc - 20) % 40 == 0) {
            strength += this->rdtsc * this->x;
        }

        runningTask->cycles--;

        if(runningTask->cycles <= 0) {
            runningTask->instruction.execute(runningTask->args, this);
            activeTask = false;

            taskQueue.erase(taskQueue.begin());
        }
    }

    struct CRT display; 

    void queueInstruction(size_t instructionId, std::vector<std::string>& args) {
        struct Task task = Task(instructions[instructionId], args);
        taskQueue.push_back(task);
    }
    
    void run(std::vector<std::string>& args) {
        struct Task task = Task(*instructionFromName(args[0]), args);

        taskQueue.push_back(task);
    }

    void addInstruction(std::string name, size_t cycles, instructionFunction execute) {
        Instruction instruction = Instruction(name, cycles, execute);
        
        instructionsIdLookup[name] = instructions.size();
        this->instructions.insert({instructions.size(), instruction});
    }

    Instruction* instructionFromName(std::string name) {
        if(instructionsIdLookup.contains(name)) {
            return &instructions[instructionsIdLookup[name]];
        }

        return nullptr;
    }

    size_t instructionIDFromName(std::string name) {
        if(instructionsIdLookup.contains(name)) {
            return instructionsIdLookup[name];
        }

        return INVALID_ID;
    }
};

class Day10 : AOC::Day {
public:
    static const int dayNum = 10;
    static const bool hasSecondInput = false;

    size_t partASolution = 0;
    size_t partBSolution = 0;

    using AOC::Day::Day;

    struct CPU cpuA;

    static void noopFunction(std::vector<std::string>& args, class CPU* cpu) {}
    static void addXFunction(std::vector<std::string>& args, class CPU* cpu) {
        cpu->x += strtoint(args[1].c_str()); 
    }

    void initCPU() {
        cpuA = {};

        cpuA.addInstruction("noop", 1, (instructionFunction)&noopFunction);
        cpuA.addInstruction("addx", 2, (instructionFunction)&addXFunction);
    }

    void partA() {
        initCPU();

        std::vector<std::string> args;

        for(std::string& str : this->input.text) {
            args = split(str, ' ');

            cpuA.run(args);
        }

        while(cpuA.taskQueue.size() > 0 || cpuA.activeTask) {
            cpuA.processA(partASolution);
        }
    }

    void partB() {

    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%llu\n", partASolution);
        printf("---- Part B ----\n");
        cpuA.display.printGrid();
        printf("----------------\n\n");
        
    }
};

#endif