#ifndef __DAY17_H__
#define __DAY17_H__

#include <day.h>
#include <util.h>

#include <stdlib.h>

#include <robin_hood.h>

class shape {
private:
    bool* data;
public:
    struct position {
        size_t x, y;

        bool operator==(const position& p) const { 
            return (this->x == p.x && this->y == p.y);
        }
        
        std::size_t operator()(const position& p) const {
            return (p.x << 32) | p.y;
        }
    };


    size_t width;
    size_t height;


    shape(size_t width, size_t height) {
        data = (bool*)malloc((width * height));
    }

    void freeData() {
        free(data);
    }

    bool getValue(size_t x, size_t y) {
        return this->data[x + (this->width * y)];
    }
    
    void setValue(size_t x, size_t y, bool value) {
        this->data[x + (this->width * y)] = value;
    }

    void setValues(size_t y, std::vector<bool> values) {
        for(size_t x = 0; x < values.size(); x++) {
            this->data[x + (this->width * y)] = values[x];
        }
    }
    
    void setValues(std::vector<std::vector<bool>> values) {
        for(size_t y = 0; y < values.size(); y++) {
            for(size_t x = 0; x < values[y].size(); x++) {
                setValue(x, y, values[y][x]);
            }
        }
    }

    bool collides(robin_hood::unordered_flat_map<struct position, bool, struct position>& grid, size_t offsetX, size_t offsetY) {
        if(offsetY <= 0) return true;

        for(size_t x = 0; x < this->width; x++) {
            if(!this->getValue(x, 0)) continue;

            if(grid[position{offsetX + x, offsetY}]) return true;
        }

        return false;
    }
};

class Day17 : AOC::Day {
public:
    static const int dayNum = 17;
    static const bool hasSecondInput = false;

    unit partASolution = 0;
    unit partBSolution = 0;

    using AOC::Day::Day;
    
    std::vector<shape> shapes;
    robin_hood::unordered_flat_map<shape::position, bool, shape::position> grid;

    size_t height = 0;
    size_t width = 5;

    size_t curShapeIdx = 0;
    shape::position curShapePos = {};

    void initShapes() {
        // shape 0 =
        // ####
        shapes.push_back(shape(4, 1));
        shapes[0].setValues(0, {1, 1, 1, 1});

        // shape 1 =
        // .#.
        // ###
        // .#.
        shapes.push_back(shape(3, 3));
        shapes[1].setValues({
            {0, 1, 0}, 
            {1, 1, 1}, 
            {0, 1, 0}
        });
        
        // shape 2 =
        // ..#
        // ..#
        // ###
        shapes.push_back(shape(3, 3));
        shapes[2].setValues({
            {1, 1, 1}, 
            {0, 0, 1}, 
            {0, 0, 1}
        });

        // shape 3 =
        // #
        // #
        // #
        // #
        shapes.push_back(shape(1, 4));
        shapes[3].setValues({
            {1}, 
            {1}, 
            {1},
            {1}
        });

        // shape 4 =
        // ##
        // ##
        shapes.push_back(shape(2, 2));
        shapes[4].setValues({
            {1, 1}, 
            {1, 1}
        });
    }

    void partA() {
        initShapes();

        shape curShape = shapes[curShapeIdx];
        curShapePos = {3, height + 4};

        for(char c : this->input.text[0]) {
            switch (c) {
            case '>':
                if((curShapePos.x + 1) + curShape.width >= width) break;

                curShapePos.x += 1;
                break;
            case '<':
                if(curShapePos.x - 1 < 0) break;

                curShapePos.x -= 1;
                break;
            default:
                break;
            }

            if(curShape.collides(grid, curShapePos.x, curShapePos.y - 1)) {
                height = std::max(curShapePos.y + curShape.height, height);

                for(size_t y = 0; y < curShape.height; y++) {
                    for(size_t x = 0; x < curShape.width; x++) {
                        grid[{y + curShapePos.y, x + curShapePos.x}] = curShape.getValue(x, y);
                    }   
                }

                if(++curShapeIdx >= shapes.size()) curShapeIdx = 0;
                curShape = shapes[curShapeIdx];
                curShapePos = {3, height + 4};
            }
            else curShapePos.y -= 1;
        }

        printf("%llu\n", height);
    }

    void partB() {

    }

    void printResults() {
        printf("---- Part A ----\n");
        printf("\n");
        //printf("---- Part B ----\n");
        //printf("\n");
        printf("----------------\n\n");
        
    }
};

#endif