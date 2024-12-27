#include "Day09.hpp"

int main()
{
    Day09 day09;
    if (!day09.loadData("input/day09.txt"))
        return 1;
    day09.solvePart1();
    day09.solvePart2();    
}
