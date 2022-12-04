#ifndef __DAYNUM_H__
#define __DAYNUM_H__

#include <day.h>
#include <util.h>

#include <robin_hood.h>

namespace partA {
    struct Rucksack {
        robin_hood::unordered_flat_map<char, bool> compartment1;
        robin_hood::unordered_flat_map<char, bool> compartment2;

        bool hasItemInCompartment1(char item) {
            return this->compartment1.find(item) != this->compartment1.end();
        }
        
        bool hasItemInCompartment2(char item) {
            return this->compartment2.find(item) != this->compartment2.end();
        }

        bool hasItemInBoth(char item) {
            return this->hasItemInCompartment1(item) && this->hasItemInCompartment2(item);
        } 
    };
};

namespace partB {
    struct Rucksack {
        robin_hood::unordered_flat_map<char, bool> items;
        
        bool hasItemInRucksack(char item) {
            return this->items.find(item) != this->items.end();
        }
    };

    struct Group {
        struct Rucksack rucksacks[3];
    };
};

class Day3 : AOC::Day {
public:
    static const int dayNum = 3;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    void partA() {
        std::vector<struct partA::Rucksack> rucksacks;
        std::vector<char> items;

        for(std::string& str : this->input.text) {
            struct partA::Rucksack rucksack;

            for(size_t i = 0; i < str.size() / 2; i++) {
                if(rucksack.hasItemInCompartment1(str[i])) continue;
                
                rucksack.compartment1[str[i]] = true;
            }

            for(size_t i = str.size() / 2; i < str.size(); i++) {
                if(rucksack.hasItemInCompartment2(str[i])) continue;
                
                rucksack.compartment2[str[i]] = true;
            }

            rucksacks.push_back(rucksack);
        }

        for(struct partA::Rucksack& rucksack : rucksacks) {
            for(auto pair : rucksack.compartment1) {
                if(rucksack.hasItemInCompartment2(pair.first)) {
                    items.push_back(pair.first);
                }
            }
        }

        for(char c : items) {
            int num = c - (isupper(c) ? 38 : 96);  

            partASolution += num;
        }
    }

    void partB() {
        std::vector<struct partB::Group> groups;
        struct partB::Group newGroup = {};

        size_t i = 0;
        for(std::string& str : this->input.text) {
            struct partB::Rucksack rucksack;
            
            for(char& c : str) {
                if(rucksack.hasItemInRucksack(c)) continue;

                rucksack.items[c] = false;
            }
        
            newGroup.rucksacks[i] = rucksack;

            if(++i == 3) {
                i = 0;
                groups.push_back(newGroup);
                newGroup = {};
            }
        }
        
        groups.push_back(newGroup);
        std::vector<char> items;

        for(struct partB::Group& group : groups) {
            struct partB::Rucksack rucksack = group.rucksacks[0];

            for(auto& pair : rucksack.items) {
                if(group.rucksacks[1].hasItemInRucksack(pair.first) && group.rucksacks[2].hasItemInRucksack(pair.first)) {
                    items.push_back(pair.first);
                }
            }
        }

        for(char& c : items) {
            int num = c - (isupper(c) ? 38 : 96);  

            partBSolution += num;
        }
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%lld\n", partASolution);
        printf("---- Part B ----\n");
        printf("%lld\n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif