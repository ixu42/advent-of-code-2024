#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <set>

class Day10
{
    public:
        bool loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        using Grid = std::vector<std::vector<int>>;
        using Point = std::pair<int, int>;
        Grid _map;
        int _rowSize;
        int _colSize;
        const std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int bfs(const Grid& grid, int startX, int startY);
        int dfs(const Grid& grid, int startX, int startY, 
                std::set<Point>& visited);       
};
