#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Day03
{
    public:
        bool loadData(const std::string& fileName);
        std::string getData() const { return _data; }
        void solvePart1();
        void solvePart2();
    
    private:
        std::string _data;
        long long  _res = 0;
        bool _enabled = true;

        bool isValid(const std::string& s);
        bool isValidNbr(const std::string& s);
        long long multiply(const std::string& s);
        bool enable_and_disable(size_t posDo, size_t posDont, 
                                size_t& posMul, size_t& prevPosMul);
};
