#include "Day15.hpp"

int main()
{
    try
    {
        Day15 day15;
        day15.loadData("input/day15.txt");
        day15.solvePart1();
        day15.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
