#include "../../include/Day07.hpp"

int main()
{
    Day07 day07;
    if (!day07.loadData("input/day07.txt"))
        return 1;
    day07.solvePart1();
    day07.solvePart2();
}
