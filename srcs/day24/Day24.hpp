#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>

class Day24
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();

    private:
        std::unordered_map<std::string, int> _wires;
        std::vector<std::vector<std::string>> _instructions;

        void loadInstructions(const std::string& line);
        void printWires() const;
        void printInstructions() const;
        void processInstructions();
        int64_t binaryToDecimal(const std::string& binary) const;
        std::string decimalToBinary(int64_t decimal) const;
        void printCorrectBinaryForZ() const;
        bool inputsWithXY(const std::string a, const std::string b) const;
        bool inputsEndIn00(const std::string a, const std::string b) const;
        std::set<std::string> findFaultyWires() const;
};
