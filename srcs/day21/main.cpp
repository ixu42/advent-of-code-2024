#include "Day21.hpp"

int main()
{
    try
    {
        Day21 day21;
        day21.loadData("input/day21.txt");
        day21.solvePart1();
        day21.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
