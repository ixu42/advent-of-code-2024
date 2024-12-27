#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <boost/multiprecision/cpp_int.hpp>

using BigInt = boost::multiprecision::cpp_int;

class Day11
{
    public:
        bool loadData(const std::string &filename);
        void solvePart1();
        void solvePart2();

    private:
        std::vector<BigInt> _stonesVec;

        bool hasEvenNumOfDigits(BigInt stone);
        std::pair<BigInt, BigInt> splitNumber(BigInt stone);
        void updateMap(std::unordered_map<BigInt, BigInt>& stonesMap, 
                        size_t blinks);
};
