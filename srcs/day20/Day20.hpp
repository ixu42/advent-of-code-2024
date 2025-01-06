#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <chrono>

class Day20
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();

    private:
        using CharGrid = std::vector<std::vector<char>>;

        struct Pos
        {
            int y;
            int x;
            bool operator==(const Pos& other) const
            {
                return y == other.y && x == other.x;
            }
            bool operator<(const Pos& other) const
            {
                return y < other.y || (y == other.y && x < other.x);
            }
        };

        CharGrid _map;
        int _rows;
        int _cols;
        Pos _start;
        std::vector<Pos> _path;

        void initStartPos();
        void printMap(const CharGrid& map) const;
        void markAndDrawPath(std::map<Pos, Pos>& parent, const Pos& end);
        std::vector<int> findPathAndRecordTime();
        int timeSaved(int timeWithoutCheats) const;
};
