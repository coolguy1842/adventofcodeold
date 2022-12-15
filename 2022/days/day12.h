#ifndef __DAY12_H__
#define __DAY12_H__

#include <day.h>
#include <util.h>
#include <stack>

#include <cmath>

#include <queue>
#include <array>

static size_t width;
static size_t height;

namespace dijkstra {
    
struct position {
    size_t x;
    char y;
    size_t z;
        
    bool operator==(const position& pos) { return x == pos.x && z == pos.z; }
}; 

struct cell {
    struct position position; 

    bool visited = false;
};

bool isNeighbourValid(position& parentPos, position& pos, std::vector<std::vector<cell>>& grid, size_t& width, size_t& height) {
    if((pos.x < 0 || pos.x >= width) || (pos.z < 0 || pos.z >= height)) return false; 

    struct cell& cell = grid[pos.z][pos.x];

    return (cell.position.y - parentPos.y <= 1) && !cell.visited;
}

std::array<cell*, 4> getValidNeighbours(position& pos, std::vector<std::vector<cell>>& grid, size_t& width, size_t& height) {
    std::array<cell*, 4> neighbours = {nullptr, nullptr, nullptr, nullptr};

    position leftPos = pos;
    leftPos.x--;
    
    position rightPos = pos;
    rightPos.x++;

    position upPos = pos;
    upPos.z--;

    position downPos = pos;
    downPos.z++;
    
    if(isNeighbourValid(pos, leftPos, grid, width, height)) neighbours[0] = &grid[leftPos.z][leftPos.x];
    if(isNeighbourValid(pos, rightPos, grid, width, height)) neighbours[1] = &grid[rightPos.z][rightPos.x];
    if(isNeighbourValid(pos, upPos, grid, width, height)) neighbours[2] = &grid[upPos.z][upPos.x];
    if(isNeighbourValid(pos, downPos, grid, width, height)) neighbours[3] = &grid[downPos.z][downPos.x];

    return neighbours;
}

int dijkstraSearch(struct std::vector<std::vector<dijkstra::cell>>& grid, struct position& pos, struct position& dest, int maxScore = __INT_MAX__) {
    struct queueContents {
        cell* cell;
        int totalCost = 0;

        bool operator>(const queueContents& qC) const { return totalCost > qC.totalCost; }
    };

    std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    
    queue.emplace(&grid[pos.z][pos.x]);

    struct cell* curCell;
    while(!queue.empty()) {
        const struct queueContents qC = queue.top();
        queue.pop();

        curCell = qC.cell;
        const int& totalCost = qC.totalCost;

        
        if(curCell->visited) continue;
        curCell->visited = true;
        
        if(totalCost > maxScore) continue;
 
        for(cell* cell : getValidNeighbours(curCell->position, grid, width, height)) {
            if(!cell) continue;
            if(cell->position == dest) return totalCost + 1;

            queue.emplace(cell, totalCost + 1);
        }
    }

    return __INT_MAX__;
}

};

class Day12 : AOC::Day {
public:
    static const int dayNum = 12;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;

    dijkstra::position startPos;
    dijkstra::position endPos;

    std::vector<dijkstra::position> positions;

    std::vector<std::vector<dijkstra::cell>> grid = {};
        
    void readInput(std::vector<std::vector<dijkstra::cell>>& grid) {
        width = this->input.text[0].size();
        height = this->input.text.size();

        grid = std::vector<std::vector<dijkstra::cell>>(height, std::vector<dijkstra::cell>());

        for(size_t z = 0; z < height; z++) {
            for(size_t x = 0; x < width; x++) {
                dijkstra::cell cell = {};

                char& y = this->input.text[z][x];
                cell.position = {x, y, z};

                switch (y) {
                case 'S':
                    cell.position.y = 'a';
                    startPos = cell.position;
                    
                    positions.push_back(cell.position);
                    break;
                case 'a':
                    positions.push_back(cell.position);
                    break;
                case 'E':
                    cell.position.y = 'z';
                    endPos = cell.position;
                    break;
                default:
                    break;
                }

                grid[z].push_back(cell);
            }   
        }
    }

    void partA() {
        readInput(grid);

        partASolution = dijkstra::dijkstraSearch(grid, startPos, endPos);
    }

    void partB() {
        int lowest = __INT_MAX__;
        
        for(struct dijkstra::position& pos : positions) {
            for(std::vector<dijkstra::cell>& cells : grid) {
                for(dijkstra::cell& cell : cells) {
                    cell.visited = false;
                }
            }

            lowest = std::min(dijkstra::dijkstraSearch(grid, pos, endPos, lowest), lowest);
        }

        partBSolution = lowest;
    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("%llu\n", partASolution);
        printf("---- Part B ----\n");
        printf("%llu\n", partBSolution);
        printf("----------------\n\n");
        
    }
};

#endif