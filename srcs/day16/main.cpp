#include "Day16.hpp"

int main()
{
    try
    {
        Day16 day16;
        day16.loadData("input/day16.txt");
        day16.solvePart1();
        day16.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
