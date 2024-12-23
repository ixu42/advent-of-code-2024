#include "../../include/Day02.hpp"

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
