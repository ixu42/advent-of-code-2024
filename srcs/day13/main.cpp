#include "Day13.hpp"

int main()
{
    try
    {
        Day13 day13;
        day13.loadData("input/day13.txt");
        day13.solvePart1();
        day13.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
