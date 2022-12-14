#ifndef __DAY12_H__
#define __DAY12_H__

#include <day.h>
#include <util.h>
#include <stack>

#include <cmath>

#include <queue>

namespace dijkstra {
    
struct position {
    size_t x;
    char y;
    size_t z;
        
    bool operator==(const position& pos) {
        return x == pos.x && z == pos.z;
    }
}; 

struct cell {
    struct position position; 

    int totalCost = __INT_MAX__, cost = 1;

    bool visited = false;
};

struct grid {
    std::vector<std::vector<struct cell>> data;

    size_t width() { return this->data[0].size(); }
    size_t height() { return this->data.size(); }
};

bool isNeighbourValid(position& parentPos, position& pos, std::vector<std::vector<cell>>& grid, size_t& width, size_t& height) {
    if(pos.x < 0 || (size_t)pos.x >= width) return false; 
    if(pos.z < 0 || (size_t)pos.z >= height) return false; 
    if(grid[pos.z][pos.x].visited) return false;

    return grid[pos.z][pos.x].position.y - parentPos.y <= 1;
}

std::vector<cell*> getValidNeighbours(position& pos, std::vector<std::vector<cell>>& grid, size_t& width, size_t& height) {
    std::vector<cell*> neighbours = {};

    position leftPos = pos;
    leftPos.x -= 1;
    
    position rightPos = pos;
    rightPos.x += 1;

    position downPos = pos;
    downPos.z += 1;
    
    position upPos = pos;
    upPos.z -= 1;
    
    if(isNeighbourValid(pos, leftPos, grid, width, height)) neighbours.push_back(&grid[leftPos.z][leftPos.x]);
    if(isNeighbourValid(pos, rightPos, grid, width, height)) neighbours.push_back(&grid[rightPos.z][rightPos.x]);
    if(isNeighbourValid(pos, downPos, grid, width, height)) neighbours.push_back(&grid[downPos.z][downPos.x]);
    if(isNeighbourValid(pos, upPos, grid, width, height)) neighbours.push_back(&grid[upPos.z][upPos.x]);

    return neighbours;
}

int dijkstraSearch(struct std::vector<std::vector<dijkstra::cell>> grid, struct position& pos, struct position& dest) {
    size_t height = grid.size();
    size_t width = grid[0].size();
    
    grid[pos.z][pos.x].totalCost = 0.0;

    struct queueContents {
        cell* cell;

        bool operator>(const queueContents& qC) const { return cell->totalCost > qC.cell->totalCost; }
    };

    std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    
    queue.emplace(&grid[pos.z][pos.x]);

    while(!queue.empty()) {
        struct queueContents qC = queue.top();
        struct cell* curCell = qC.cell;

        queue.pop();

        if(curCell->visited) continue;
        curCell->visited = true;
 
        if (curCell->position == dest) {
            return curCell->totalCost;
        }

        for(cell* cell : getValidNeighbours(curCell->position, grid, width, height)) {
            if((cell->totalCost = std::min(curCell->totalCost + cell->cost, cell->totalCost)) != __INT_MAX__) {
                queue.emplace(cell);
            }
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
        grid = {};

        for(size_t z = 0; z < this->input.text.size(); z++) {
            grid.push_back({});

            for(size_t x = 0; x < this->input.text[0].size(); x++) {
                dijkstra::cell cell = {};
                cell.position = {x, this->input.text[z][x], z};
                
                cell.cost = 1;
                cell.totalCost = __INT_MAX__;
                cell.visited = false;

                if(this->input.text[z][x] == 'S') {
                    cell.position.y = 'a';
                    startPos = cell.position;
                }
                else if(this->input.text[z][x] == 'E') {
                    cell.position.y = 'z';
                    endPos = cell.position;
                }
                
                if(this->input.text[z][x] == 'a') {
                    positions.push_back(cell.position);
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

        for(dijkstra::position pos : positions) {
            lowest = std::min(dijkstra::dijkstraSearch(grid, pos, endPos), lowest);
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