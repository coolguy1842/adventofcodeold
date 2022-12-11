#ifndef __DAY10_CPU_H__
#define __DAY10_CPU_H__

#define unit long long int
#define INVALID_ID 0U - 1

#include <robin_hood.h>

#include <linkedList.h>

#include <Day10/CRT.h>
#include <Day10/Instruction.h>

class CPU {
public:
    // neaten registers up
    struct Registers {
        unit x = 1;
    };

    size_t rdtsc = 0;
    struct Registers registers;

    class linkedList<struct Task> taskQueue;
    struct Task* runningTask;

    struct CRT display; 
    unit strength;

    robin_hood::unordered_flat_map<size_t, struct Instruction*> instructions;
    robin_hood::unordered_flat_map<std::string, size_t> instructionsIdLookup;

    void partA() {
        // having unsigned allows wrapback which will give wrong results
        if(((unit)this->rdtsc - 20) % 40 == 0) {
            strength += this->rdtsc * this->registers.x;
        }
    }

    void partB() {
        this->display.updateGrid(rdtsc, this->registers.x);
    }

    void process() {
        partB();
        rdtsc++;
        partA(); 
    
        switch (--runningTask->cycles) {
        case 0:
            runningTask->instruction->execute(runningTask->args, this);

            taskQueue.pop_front();
            runningTask = &taskQueue.begin()->data;
            break;
        default:
            break;
        }
    }

    void run(size_t& instructionId, std::vector<std::string>& args) {
        taskQueue.push_back(Task(instructions[instructionId], args));
    }
    
    void run(std::vector<std::string>& args) {
        taskQueue.push_back(Task(instructionFromName(args[0]), args));
    }

    void addInstruction(std::string name, size_t cycles, instructionFunction execute) {
        Instruction* instruction = new Instruction(name, cycles, execute);
        
        instructionsIdLookup[name] = instructions.size();
        this->instructions.insert({instructions.size(), instruction});
    }

    Instruction* instructionFromName(std::string name) {
        if(instructionsIdLookup.contains(name)) return instructions[instructionsIdLookup[name]];

        return nullptr;
    }

    size_t instructionIDFromName(std::string name) {
        if(instructionsIdLookup.contains(name)) return instructionsIdLookup[name];

        return INVALID_ID;
    }

    void deleteInstructions() {
        for(auto& pair : this->instructions) {
            delete pair.second;
        }
    }
};

#endif