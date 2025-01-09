#include "Day22.hpp"

int main()
{
    try
    {
        Day22 day22;
        day22.loadData("input/day22.txt");

        day22.solvePart1();

        auto start = std::chrono::high_resolution_clock::now();
        day22.solvePart2();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "part2 takes " << elapsed.count() << " s\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
