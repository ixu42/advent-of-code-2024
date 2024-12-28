#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

class Day13
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();

    private:
        using ClawMachine = std::unordered_map<char, std::pair<int, int>>;
        std::vector<ClawMachine> _data;

        void loadClawMachine(const std::string& line, ClawMachine& clawMachine);
        void printData();
};
