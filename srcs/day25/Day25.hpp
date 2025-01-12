#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Day25
{
    public:
        void loadData(const std::string& fileName);
        void solve();

    private:
        std::vector<std::vector<std::string>> _lockGrids;
        std::vector<std::vector<std::string>> _keyGrids;
        std::vector<std::vector<int>> _locks;
        std::vector<std::vector<int>> _keys;
        int _gridHeight;

        bool parseLine(const std::string& line, std::vector<std::string>& lock,
            std::vector<std::string>& key, bool& startLoading, bool& loadingLocks,
            bool& loadingKeys);
        std::vector<std::vector<int>> calculatePinHeights(
            const std::vector<std::vector<std::string>>& items);
};
