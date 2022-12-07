#ifndef __DAY7_H__
#define __DAY7_H__

#include <day.h>

#include <robin_hood.h>
#include <util.h>

namespace partA {

struct command {
    std::string name;
    std::vector<std::string> args;
};

struct rawFile {
    bool isDir = false;
    unit size;

    std::string name;
};

struct command commandFromStr(std::string str) {
    std::vector<std::string> splitStr = split(str, ' ');

    struct command cmd;
    cmd.name = splitStr[1];

    for(size_t i = 2; i < splitStr.size(); i++) {
        cmd.args.push_back(splitStr[i]);
    } 

    return cmd;
}

struct rawFile fileFromStr(std::string str) {
    std::vector<std::string> splitStr = split(str, ' ');

    struct rawFile file;

    file.isDir = false;
    file.size = strtounit(splitStr[0].c_str());
    file.name = splitStr[1];
    
    return file;
}

struct rawFile dirFromStr(std::string str) {
    std::vector<std::string> splitStr = split(str, ' ');

    struct rawFile file;

    file.isDir = true;
    file.name = splitStr[1] + "/";
    
    return file;
}

struct rawFile rawFileFromStr(std::string str) {
    std::vector<std::string> splitStr = split(str, ' ');

    if(splitStr[0] == "dir") return dirFromStr(str);
    else return fileFromStr(str);
}

unit getDirSize(std::string dir, robin_hood::unordered_flat_map<std::string, std::vector<struct rawFile>> dirContents) {
    unit size = 0; 

    for(rawFile& file : dirContents[dir]) {
        switch(file.isDir) {
        case false:
            size += file.size;
            break;
        default:
            size += getDirSize(dir + file.name, dirContents);
            break;
        }
    }

    return size;
}

};

class Day7 : AOC::Day {
public:
    static const int dayNum = 7;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = __LONG_LONG_MAX__;

    using AOC::Day::Day;
    std::string curDir = "";
    robin_hood::unordered_flat_map<std::string, std::vector<struct partA::rawFile>> dirContents = {};
    robin_hood::unordered_flat_map<std::string, unit> dirSizes = {};

    void partA() {
        for(std::string& str : this->input.text) {
            if(str[0] == '$') {

                struct partA::command command = partA::commandFromStr(str);

                if(command.name == "cd") {
                    if(command.args[0] == "/") {
                        curDir = std::string("/");
                    }
                    else if(command.args[0] == "..") {
                        std::vector<std::string> splitStr = split(curDir, '/');
                        curDir.clear();
                        
                        for(size_t i = 0; i < splitStr.size() - 2; i++) {
                            curDir += splitStr[i].append("/");
                        }
                    }
                    else {
                        curDir += command.args[0].append("/");
                    }
                }
            }
            else {
                partA::rawFile file = partA::rawFileFromStr(str);

                dirContents[curDir].push_back(file);
            }
        }

        for(auto pair : dirContents) {
            unit size = partA::getDirSize(pair.first, dirContents);
            dirSizes[pair.first] = size;
        
            if(size <= 100000) partASolution += size;
        }
    }

    void partB() {
        unit available = 70000000 - dirSizes["/"];
        unit sizeToDelete = 30000000;
        
        for(auto& pair : dirContents) {
            unit size = dirSizes[pair.first];
            unit test = available + size;

            if(test >= sizeToDelete && size < partBSolution) {
                partBSolution = size;
            }
        }
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%lld \n", partASolution);
        printf("---- Part B ----\n");
        printf("%lld \n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif