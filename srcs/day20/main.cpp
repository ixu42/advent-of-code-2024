#include "Day20.hpp"

int main()
{
    try
    {
        Day20 day20;
        day20.loadData("input/day20.txt");

        auto start = std::chrono::high_resolution_clock::now();
        day20.solvePart1();
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "part1 took "
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
            << "s\n";

        day20.solvePart2();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
