#include "Day04.hpp"

int main()
{
    Day04 day04;
    if (!day04.loadData("input/Day04.txt"))
        return 1;
    day04.solvePart1();
    day04.solvePart2();
}
