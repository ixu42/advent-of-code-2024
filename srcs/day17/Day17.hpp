#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <cmath>

class Day17
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        std::unordered_map<char, long> _registers;
        std::vector<int> _program;
        std::vector<int> _output;

        long getComboOperand(int operand);
        void adv(int operand);
        void bxl(int operand);
        void bst(int operand);
        void jnz(int operand, int& i);
        void bxc(int operand);
        void out(int operand, bool& outCalled);
        void bdv(int operand);
        void cdv(int operand);
};
