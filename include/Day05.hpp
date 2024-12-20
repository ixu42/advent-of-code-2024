#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

class Day05
{
    public:
        void loadRules(const std::string& line);
        void parseRules(const std::vector<std::string>& rules);
        void loadUpdates(const std::string& line);
        bool loadData(const std::string& filename);
        void printData();
        void printUpdate(const std::vector<int>& update);
        void solvePart1();
        void solvePart2();
    
    private:
        std::vector<std::pair<int, int>> _rules;
        std::vector<std::vector<int>> _updates;
        int _resPart1 = 0;
        int _resPart2 = 0;

        bool isInRightOrder(int left, int right);
        void checkOrder(std::vector<int>& update, bool& correctlyOrdered);
        std::vector<int> reorderUpdate(std::vector<int>& update);
        std::vector<int> topologicalSort(std::unordered_map<int, std::vector<int>> graph, 
                                            std::unordered_map<int, int>& inDegree);
};
