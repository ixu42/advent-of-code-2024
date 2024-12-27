#include "Day08.hpp"

int main()
{
    Day08 day08;
    if (!day08.loadData("input/day08.txt"))
        return 1;
    day08.solvePart1();
    day08.solvePart2();
}
