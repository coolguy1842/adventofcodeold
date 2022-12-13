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
    std::vector<std::vector<struct position>> data;

    size_t width() { return this->data[0].size(); }
    size_t height() { return this->data.size(); }
};

bool isNeighbourValid(position& parentPos, position& pos, std::vector<std::vector<cell>>& cellDetails, size_t& width, size_t& height) {
    if(pos.x < 0 || (size_t)pos.x >= width) return false; 
    if(pos.z < 0 || (size_t)pos.z >= height) return false; 
    if(cellDetails[pos.z][pos.x].visited) return false;

    return cellDetails[pos.z][pos.x].position.y - parentPos.y <= 1;
}

std::vector<cell*> getValidNeighbours(position& pos, std::vector<std::vector<cell>>& cellDetails, size_t& width, size_t& height) {
    std::vector<cell*> neighbours = {};

    position leftPos = pos;
    leftPos.x -= 1;
    
    position rightPos = pos;
    rightPos.x += 1;

    position downPos = pos;
    downPos.z += 1;
    
    position upPos = pos;
    upPos.z -= 1;
    
    if(isNeighbourValid(pos, leftPos, cellDetails, width, height)) neighbours.push_back(&cellDetails[leftPos.z][leftPos.x]);
    if(isNeighbourValid(pos, rightPos, cellDetails, width, height)) neighbours.push_back(&cellDetails[rightPos.z][rightPos.x]);
    if(isNeighbourValid(pos, downPos, cellDetails, width, height)) neighbours.push_back(&cellDetails[downPos.z][downPos.x]);
    if(isNeighbourValid(pos, upPos, cellDetails, width, height)) neighbours.push_back(&cellDetails[upPos.z][upPos.x]);

    return neighbours;
}

int dijkstraSearch(struct grid& grid, struct position& pos, struct position& dest) {
    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    size_t height = grid.height();
    size_t width = grid.width();

    // Declare a 2D array of structure to hold the details
    // of that cell
    std::vector<std::vector<struct cell>> cellDetails;
    
    for(size_t z = 0; z < height; z++) {
        cellDetails.push_back({});
        
        for(size_t x = 0; x < width; x++) {
            struct cell cell = {};

            cell.position = grid.data[z][x];

            cell.cost = 1;
            cell.totalCost = __INT_MAX__;
            cell.visited = false;

            cellDetails[z].push_back(cell);
        }
    }

    
    cellDetails[pos.z][pos.x].totalCost = 0.0;

    struct queueContents {
        cell* cell;

        bool operator>(const queueContents& qC) const { return cell->totalCost > qC.cell->totalCost; }
    };

    std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    
    queue.emplace(&cellDetails[pos.z][pos.x]);

    while(!queue.empty()) {
        struct queueContents qC = queue.top();
        struct cell* curCell = qC.cell;

        queue.pop();

        if(curCell->visited) continue;
        curCell->visited = true;
 
        if (curCell->position == dest) {
            return curCell->totalCost;
        }

        for(cell* cell : getValidNeighbours(curCell->position, cellDetails, width, height)) {
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

    dijkstra::grid grid = {};
        
    void readInput(struct dijkstra::grid& grid) {
        grid.data = {};

        for(size_t z = 0; z < this->input.text.size(); z++) {
            grid.data.push_back({});

            for(size_t x = 0; x < this->input.text[0].size(); x++) {
                grid.data[z].push_back(dijkstra::position{x, this->input.text[z][x], z});

                if(this->input.text[z][x] == 'S') {
                    grid.data[z][x].y = 'a';
                    startPos = grid.data[z][x];
                }
                else if(this->input.text[z][x] == 'E') {
                    grid.data[z][x].y = 'z';
                    endPos = grid.data[z][x];
                }
                
                if(this->input.text[z][x] == 'a') {
                    positions.push_back(this->grid.data[z][x]);
                }
            }   
        }
    }

    void partA() {
        readInput(grid);

        partASolution = dijkstra::dijkstraSearch(grid, startPos, endPos);
    }

    void partB() {
        partBSolution = __INT_MAX__;

        for(dijkstra::position pos : positions) {
            partBSolution = (size_t)std::min(dijkstra::dijkstraSearch(grid, pos, endPos), (int)partBSolution);
        }
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