#include "Day24.hpp"

int main()
{
    try
    {
        Day24 day24;
        day24.loadData("input/day24.txt");
        day24.solvePart1();
        day24.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
