#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <queue>
#include <utility>

class Day18
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        struct Pos
        {
            int y;
            int x;
        };
        using CharGrid = std::vector<std::vector<char>>;
        using BoolGrid = std::vector<std::vector<bool>>;
        std::vector<Pos> _bytes;

        int countMinSteps(const CharGrid& grid, const Pos& start, const Pos& end);
};
