#include "../../include/Day06.hpp"

int main()
{
    Day06 day06;
    if (!day06.initData("input/day06.txt"))
        return 1;
    day06.solvePart1();
    auto start = std::chrono::high_resolution_clock::now();
    day06.solvePart2();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                    stop - start);
    std::cout << "Time to solve part2: " << duration.count() << "s\n";
}
