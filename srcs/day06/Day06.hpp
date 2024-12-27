#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <chrono>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Day06
{
    public:
        bool initData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:

        std::vector<std::vector<char>> _data;
        std::vector<std::vector<char>> _dataWithPath;
        std::pair<int, int> _initialPos;
        Direction _initialDirection = Direction::UP;

        void printGrid(const std::vector<std::vector<char>>& grid);
        void getInitialPos();
        bool withInGrid(const std::pair<int, int>& pos, 
                        const std::vector<std::vector<char>>& grid);
        std::pair<int, int> getDirection(Direction direction);
        void changeDirection(Direction& currDirection);
        std::pair<int, int> getNextPos(const std::pair<int, int>& currPos, 
                                        Direction currDirection);
        int calculateVisited(const std::vector<std::vector<char>>& grid);
        bool isInThePath(std::vector<std::vector<char>> dataWithPath, int r, int c);
        bool causeGuardStuckInLoop(const std::vector<std::vector<char>>& grid);
};
