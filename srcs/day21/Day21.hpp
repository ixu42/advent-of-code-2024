#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <algorithm>
#include <chrono>

class Day21
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        // void solvePart2();

    private:
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
        using CharGrid = std::vector<std::string>;

        inline static const CharGrid NUMPAD = {
            "789",
            "456",
            "123",
            "#0A"
        };

        inline static const CharGrid DIRPAD = {
            "#^A",
            "<v>"
        };

        inline static const std::vector<Pos> MOVES = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        std::vector<std::string> _codes;

        void getCharPos(const CharGrid& keypad, char num, int& y, int& x);
        bool isValid(const CharGrid& keypad, int y, int x);
        std::vector<std::string> bfs(const CharGrid& keypad, char start, char target);
        std::vector<std::string> getSeqForNumPad(const std::string& code);
        std::vector<std::string> getSeqForDirPad(const std::vector<std::string>& curSeq);
};
