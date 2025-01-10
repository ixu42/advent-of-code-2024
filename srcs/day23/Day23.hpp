#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <chrono>

class Day23
{
    public:
        void loadData(const std::string& filename);
        void solvePart1();
        void solvePart2();
    
    private:
        std::unordered_map<std::string, std::unordered_set<std::string>> _graph;

        void printGraph();
        std::set<std::set<std::string>> findTriangles();
        void bronKerbosch(std::unordered_set<std::string>& R, 
                            std::unordered_set<std::string>& P, 
                            std::unordered_set<std::string>& X, 
                            std::vector<std::unordered_set<std::string>>& cliques);
};
