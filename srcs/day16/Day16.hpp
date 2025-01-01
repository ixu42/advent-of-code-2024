#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>

class Day16
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();
    
    private:
        // directions: [0] north, [1] east, [2] south, [3] west
        const int DX[4] = {0, 1, 0, -1};
        const int DY[4] = {-1, 0, 1, 0};
        const char WALL = '#';
        const char START = 'S';
        const char END = 'E';
        const int INF = INT_MAX;

        struct Pos
        {
            int y;
            int x;
        };

        struct State
        {
            int y, x, dir, cost;
            bool operator>(const State& other) const
            {
                return cost > other.cost;
            }
        };

        using CharGrid = std::vector<std::vector<char>>;
        using IntVec = std::vector<int>;
        using Int2DVec = std::vector<IntVec>;
        using Int3DVec = std::vector<Int2DVec>;
        using TupleVec = std::vector<std::tuple<int, int, int>>;
        using Tuple2DVec = std::vector<TupleVec>;
        using Tuple3DVec = std::vector<Tuple2DVec>;
        using Tuple4DVec = std::vector<Tuple3DVec>;
        using BoolVec = std::vector<bool>;
        using Bool2DVec = std::vector<BoolVec>;

        CharGrid _map;
        int _rowSize;
        int _colSize;
        Pos _start;
        Pos _end;

        void getStartAndEndPos();
        void drawMap(const CharGrid& map) const;
        // part1
        void drawPath(CharGrid& map, int ey, int ex, int edir, const Tuple3DVec& parent);
        int findMinScore(CharGrid& map);
        // part2
        int markPathsAndCountTiles(CharGrid& map, int ey, int ex, int edir, const Tuple4DVec& parent);
        int countAllValidTiles(CharGrid& map);

};
