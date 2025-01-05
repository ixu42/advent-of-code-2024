#include "Day19.hpp"

int main()
{
    try
    {
        Day19 day19;
        day19.loadData("input/day19.txt");
        day19.solvePart1();
        day19.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
