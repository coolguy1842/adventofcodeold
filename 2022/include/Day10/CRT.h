#ifndef __DAY10_CRT_H__
#define __DAY10_CRT_H__

#define CRT_WIDTH 40
#define CRT_HEIGHT 6

#define unit long long int

#include <stdio.h>
#include <cmath>

#define offChar 176
#define onChar 178

struct CRT {
public:
    char grid[CRT_HEIGHT][CRT_WIDTH + 1];

    void updateGrid(size_t rdtsc, unit x) {
        size_t pos = rdtsc % 40;
        size_t curCol = rdtsc / 40;

        switch(std::abs((unit)pos - x)) {
        case 0: case 1:
            grid[curCol][pos] = onChar;
            break;
        default:
            grid[curCol][pos] = offChar;
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



#endif