#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <exception>
#include <stdexcept>
#include <vector>
#include <queue>

class Day14
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        struct Bot
        {
            // position
            int px;
            int py;
            // velocity
            int vx;
            int vy;
        };
        using IntGrid = std::vector<std::vector<int>>;
        using Point = std::pair<int, int>;
        using BoolGrid = std::vector<std::vector<bool>>;
        std::vector<Bot> _bots;

        void printBots();
        void printGrid(int xMax, int yMax, IntGrid& grid);
        void drawBotsOnGrid(int px, int py, int nx, int ny, 
                            int xMax, int yMax, IntGrid& grid);
        int calculateResPart1(int xMax, int yMax, IntGrid& grid);
        void initStartPos(int xMax, int yMax, IntGrid& grid, 
                            BoolGrid& visited, std::queue<Point>& q);
        bool checkTree(int xMax, int yMax, IntGrid& grid, BoolGrid& visited);
        bool botsFormChristmasTree(int xMax, int yMax, IntGrid& grid);
};
