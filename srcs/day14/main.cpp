#include "Day14.hpp"

int main()
{
    try
    {
        Day14 day14;
        day14.loadData("input/day14.txt");
        day14.solvePart1();
        day14.solvePart2();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}
