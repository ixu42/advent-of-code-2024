#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Day04
{
    public:
        bool loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();

        void printGrid(std::vector<std::vector<char>> grid);
    
    private:
        std::vector<std::vector<char>> _data;
        int _resPart1 = 0;
        int _resPart2 = 0;
};
