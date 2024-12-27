#include "Day10.hpp"

int main()
{
    Day10 day10;
    if (!day10.loadData("input/day10.txt"))
        return 1;
    day10.solvePart1();
    day10.solvePart2();
}
