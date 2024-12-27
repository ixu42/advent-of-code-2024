#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Day09
{
    public:
        bool loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        std::vector<int> _extended;

        void printLine(const std::vector<int>& line);
        bool hasGap(const std::vector<int>& line);
        uint64_t calculateChecksum(const std::vector<int>& line);
        void findSpaceAndInsert(std::vector<int>& rearranged, 
                                std::map<int, int, std::greater<int>>& fileSizes, 
                                std::map<int, int, std::greater<int>>& fileStartPos);
};
