#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Day15
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        struct Point
        {
            int y; // row
            int x; // col
            bool operator<(const Point& other) const
            {
                return (y < other.y) || (y == other.y && x < other.x);
            }
        };

        using CharGrid = std::vector<std::vector<char>>;
        CharGrid _map;
        int _rowSize;
        int _colSize;
        std::string _movements;

        void printMap(const CharGrid& map);
        void getCurrPos(const CharGrid& map, int& currY, int& currX);
        Direction getDirection(char move);
        void getNextPos(Direction d, int currY, int currX, int& nextY, int& nextX);
        bool push(CharGrid& map, int currY, int currX, Direction);
        void pushBox(CharGrid& map, int nextY, int nextX, 
                        int& currY, int& currX, Direction d);
        int getResPart1(const CharGrid& map);

        CharGrid updateMap();
        bool pushHorizontally(CharGrid& map, int currY, int currX, Direction d);
        bool pushVertically(CharGrid& map, int currY, int currX, Direction d);
        void moveBoxesVertically(CharGrid& map, std::vector<Point>& visitedSlice, int dy);
        void pushRobot(CharGrid& map, int nextY, int nextX, int& currY, int& currX);
        void pushBoxPart2(CharGrid& map, int nextY, int nextX, 
                            int& currY, int& currX, Direction d);
        int getResPart2(const CharGrid& map);
};
