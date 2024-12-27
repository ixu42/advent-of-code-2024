#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

class Day02
{
    public:
        void loadData(const std::string& fileName);
        std::vector<std::vector<int>>& getReports() { return _reports; };
        void setReports(std::vector<int> report) { _reports.push_back(report); };
        bool isSafe(std::vector<int>& report);
        bool isSafeIfRemoveOne(std::vector<int>& report);

    private:
        std::vector<std::vector<int>> _reports;
        std::vector<std::vector<int>> _tempReports;
        bool _reportUpdated = false;

        void printReports();
        void printReport(std::vector<int>& report);
        bool checkDiff(const std::vector<int>& report);
        bool checkDiffIfRemoveOne(std::vector<int>& report);
        bool isIncreasing(const std::vector<int>& report);
        bool isIncreasingIfRemoveOne(const std::vector<int>& report, size_t index);
        bool canBecomeIncreasing(const std::vector<int>& report);
        bool isDecreasing(const std::vector<int>& report);
        bool isDecreasingIfRemoveOne(const std::vector<int>& report, size_t index);
        bool canBecomeDecreasing(const std::vector<int>& report);
};
