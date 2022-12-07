#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <string>
#include <string.h>

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> out;
    std::string substr;

    for(char c : str) {
        if(c == delim) {
            out.push_back(substr);
            substr.clear();

            continue;
        }
        
        substr += c;
    }

    out.push_back(substr);

    return out;
}

std::vector<std::string> split(std::string str, std::string delim) {
    std::vector<std::string> out;
    std::string substr;

    size_t pos = 0;
    
    while((pos = str.find(delim)) != std::string::npos) {
        out.push_back(str.substr(0, pos));
        
        str.erase(0, pos + delim.length());
    }

    out.push_back(str);

    return out;
}


// shaves off ~200us compared to std::stoi in day 4
int strtoint(const char* str) {
    int out = 0;

    while(*str) {
        out = out * 10 + (*str++ - '0');
    }

    return out;
}

unit strtounit(const char* str) {
    unit out = 0;

    while(*str) {
        out = out * 10 + (*str++ - '0');
    }

    return out;
}

#endif