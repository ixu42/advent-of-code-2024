#include "../../include/Day03.hpp"

int main()
{
    Day03 day03;
    if (!day03.loadData("input/Day03.txt"))
        return 1;
    day03.solvePart1();
    day03.solvePart2();
}
