#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <unordered_set>

class Day19
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();

    private:
        std::unordered_set<std::string> _availablePatterns;
        std::vector<std::string> _desiredDesigns;

        bool isAvailablePattern(const std::string& pattern);
        bool isPossible(const std::string& design);
        int64_t countPossibles(const std::string& design);
};
