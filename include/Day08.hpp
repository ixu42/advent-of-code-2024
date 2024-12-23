#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <set>
#include <utility>

class Day08
{
    public:
        bool loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        std::vector<std::vector<char>> _grid;
        std::unordered_map<char, std::vector<std::pair<int, int>>> _antennas;

        void loadAntennas(const std::vector<std::string>& data);
        void printGrid(std::vector<std::vector<char>>& grid);
        void printAntennas();
        void drawAntinode(const std::pair<int, int>& pos, 
                            std::vector<std::vector<char>>& grid);
        int calculateAntinode(const std::vector<std::vector<char>>& grid);
        void extendLine(int x, int y, int dx, int dy,
                        std::set<std::pair<int, int>>& extendedPoints);
};
