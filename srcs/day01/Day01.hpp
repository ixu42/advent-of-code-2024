#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

class Day01
{
    public:
        void loadData(const std::string& fileName);
        int calculateDist();
        int calculateSimilarityScore();
        std::vector<int>& getFirstColume() { return _firstColume; }
        std::vector<int>& getSecondColume() { return _secondColume; }

    private:
        std::vector<int> _firstColume;
        std::vector<int> _secondColume;
};
