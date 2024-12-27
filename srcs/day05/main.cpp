#include "Day05.hpp"

int main()
{
    Day05 day05;
    if (!day05.loadData("input/day05.txt"))
        return 1;
    day05.solvePart1();
    day05.solvePart2();
}
