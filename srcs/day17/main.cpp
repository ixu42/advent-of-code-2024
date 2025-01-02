#include "Day17.hpp"

int main()
{
    try
    {
        Day17 day17;
        day17.loadData("input/day17.txt");
        day17.solvePart1();
        day17.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
