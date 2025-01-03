#include "Day18.hpp"

int main()
{
    try
    {
        Day18 day18;
        day18.loadData("input/day18.txt");
        day18.solvePart1();
        day18.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
