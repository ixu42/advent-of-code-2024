#include "Day23.hpp"

int main()
{
    try
    {
        Day23 day23;
        day23.loadData("input/day23.txt");

        day23.solvePart1();

        auto start = std::chrono::high_resolution_clock::now();
        day23.solvePart2();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "part2 took " << elapsed.count() << "s\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
