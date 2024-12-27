#include "Day12.hpp"

int main()
{
    Day12 day12;
    if (!day12.loadGrid("input/day12.txt"))
        return 1;
    day12.solvePart1();
    day12.solvePart2();
}
