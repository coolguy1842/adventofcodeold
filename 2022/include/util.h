#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <string>
#include <string.h>

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> out;
    std::string cur;

    for(char c : str) {
        if(c == delim) {
            out.push_back(cur);
            cur.clear();

            continue;
        }
        
        cur += c;
    }

    out.push_back(cur);

    return out;
}

std::vector<std::string> split(std::string str, std::string delim) {
    std::vector<std::string> out;
    std::string cur;

    size_t end = 0;

    while((end = str.find(delim, end + delim.length())) != std::string::npos) {
        printf("%lld\n", end);
    }

    out.push_back(cur);

    return out;
}

#endif