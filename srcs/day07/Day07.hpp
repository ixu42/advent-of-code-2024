#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdint>

class Day07
{
    public:
        bool loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        std::vector<std::pair<uint64_t, std::vector<uint64_t>>> _data;
        int countDigits(uint64_t num);
        bool evaluateExpression(const std::vector<uint64_t>& nums, 
                                const std::vector<char>& ops, 
                                uint64_t testValue);
        void generateOpsAndCheckValidity(const std::vector<uint64_t>& nums, 
                        const std::vector<char>& ops, 
                        std::vector<char>& current, size_t index, 
                        uint64_t testValue, bool& isValid);
        void printData();
};
