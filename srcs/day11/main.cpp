#include "../../include/Day11.hpp"

int main()
{
    Day11 day11;
    if (!day11.loadData("input/day11.txt"))
        return 1;
    day11.solvePart1();
    day11.solvePart2();
}
