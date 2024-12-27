#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>

class Day12 
{
    public:
        bool loadGrid(const std::string& filename);
        void solvePart1();
        void solvePart2();
    
    private:
        using Bool2DVec = std::vector<std::vector<bool>>;
        using Point = std::pair<int, int>;

        std::vector<std::vector<char>> _grid;
        int _rowSize;
        int _colSize;
        std::vector<Point> _directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        bool withinBounds(int x, int y);
        void bfs(Bool2DVec& visited, int startX, int startY,  
                    int& area, int& perimeter);
        void checkHorizontalBoundary(const Bool2DVec& currRegion, int nx, 
                                        int x, int y, int& sides);
        void checkVerticalBoundary(const Bool2DVec& currRegion, int ny, 
                                    int x, int y, int& sides);
        void calculateSides(const Bool2DVec& currRegion, int& sides);
        void bfsPart2(Bool2DVec& currRegion, Bool2DVec& visited, int startX, int startY,  
                    int& area);
        void printGrid();
        void printRegion(int x, int y, int area, int perimeter);
};
