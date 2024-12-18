#include "include/Day02.hpp"

bool Day02::checkDiff(const std::vector<int>& report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        int diff = std::abs(report[i + 1] - report[i]);
        if (diff > 3 || diff < 1)
            return false;
    }
    return true;
}

bool Day02::isSafe(std::vector<int>& report)
{
    if (report.size() < 2)
        return false;

    // check if the levels are either all increasing or all decreasing
    bool increasing = true;
    bool decreasing = true;
    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] < report[i + 1])
            decreasing = false;
        if (report[i] > report[i + 1])
            increasing = false;
    }

    if (!increasing && !decreasing)
        return false;
    
    // check if two adjacent levels differ by at least one and at most three
    return checkDiff(report);
}

bool Day02::isIncreasing(const std::vector<int>& report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] >= report[i + 1])
            return false;
    }
    return true;
}

bool Day02::isIncreasingIfRemoveOne(const std::vector<int>& report, size_t index)
{
    std::vector<int> temp = report;
    temp.erase(temp.begin() + index);
    if (isIncreasing(temp))
    {
        _tempReports.push_back(temp);
        _reportUpdated = true;
    }
    temp = report;
    temp.erase(temp.begin() + index + 1);
    if (isIncreasing(temp))
    {
        _tempReports.push_back(temp);
        _reportUpdated = true;
    }
    if (_reportUpdated)
        return true;
    return false;
}

bool Day02::canBecomeIncreasing(const std::vector<int>& report)
{
    size_t index;
    bool isAscending = true;
    _tempReports.push_back(report);

    for (size_t i = 0; i < report.size() - 1; i++)
    {
        if (report[i] >= report[i + 1])
        {
            index = i;
            isAscending = false;
            break ;
        }
    }

    if (!isAscending)
        return isIncreasingIfRemoveOne(report, index);
    return true;
}

bool Day02::isDecreasing(const std::vector<int>& report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] <= report[i + 1])
            return false;
    }
    return true;
}

bool Day02::isDecreasingIfRemoveOne(const std::vector<int>& report, size_t index)
{
    std::vector<int> temp = report;
    temp.erase(temp.begin() + index);
    if (isDecreasing(temp))
    {
        _tempReports.push_back(temp);
        _reportUpdated = true;
    }
    temp = report;
    temp.erase(temp.begin() + index + 1);
    if (isDecreasing(temp))
    {
        _tempReports.push_back(temp);
        _reportUpdated = true;
    }
    if (_reportUpdated)
        return true;
    return false;
}

bool Day02::canBecomeDecreasing(const std::vector<int>& report)
{
    size_t index;
    bool isDescending = true;
    _tempReports.push_back(report);

    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] <= report[i + 1])
        {
            index = i;
            isDescending = false;
            break ;
        }
    }

    if (!isDescending)
        return isDecreasingIfRemoveOne(report, index);
    return true;
}

bool Day02::checkDiffIfRemoveOne(std::vector<int>& report)
{
    size_t index;
    bool diffOk = true;

    for (int i = 0; i < report.size() - 1; i++)
    {
        int diff = std::abs(report[i + 1] - report[i]);
        if (diff > 3 || diff < 1)
        {
            index = i;
            diffOk = false;
            break ;
        }
    }

    if (!diffOk)
    {
        std::vector<int> temp = report;
        temp.erase(temp.begin() + index);
        if (checkDiff(temp))
            return true;
        temp = report;
        temp.erase(temp.begin() + index + 1);
        return checkDiff(temp);
    }
    return true;
}

bool Day02::isSafeIfRemoveOne(std::vector<int>& report)
{
    _reportUpdated = false;
    _tempReports.clear();

    if (report.size() < 2)
        return false;

    if (!canBecomeIncreasing(report) && !canBecomeDecreasing(report))
        return false;

    if (_reportUpdated)
    {
        for (auto& _tempReport: _tempReports)
        {
            if (checkDiff(_tempReport))
                return true;
        }
        return false;
    }
    return checkDiffIfRemoveOne(report);
}

void Day02::printReports()
{
    for (auto& report: _reports)
    {
        for (size_t i = 0; i < report.size(); i++)
            std::cout << report[i] << " ";
        std::cout << "\n";
    }
}

void Day02::printReport(std::vector<int>& report)
{
    for (size_t i = 0; i < report.size(); i++)
        std::cout << report[i] << " ";
    std::cout << "\n";
}

void Day02::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    int num;
    while (file >> num)
    {
        std::vector<int> report;
        report.push_back(num);
        while (file >> num)
        {
            report.push_back(num);
            if (file.peek() == '\n')
                break;
        }
        setReports(report);
    }
}

int main()
{
    Day02 day02;
    day02.loadData("input/Day02.txt");

    // PART 1
    int safeCount = 0;
    for (auto& report: day02.getReports())
    {
        if (day02.isSafe(report))
            safeCount++;
    }
    std::cout << "Part 1: " << safeCount << "\n";

    // PART 2
    safeCount = 0;
    for (auto& report: day02.getReports())
    {
        if (day02.isSafeIfRemoveOne(report))
            safeCount++;
    }
    std::cout << "Part 2: " << safeCount << "\n";
}
