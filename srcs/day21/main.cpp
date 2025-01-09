#include "Day21.hpp"

int main()
{
    try
    {
        Day21 day21;
        day21.loadData("input/day21.txt");
        // day21.loadData("input/test.txt");

        auto start = std::chrono::high_resolution_clock::now();
        day21.solvePart1();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "time: " << elapsed.count() << " s\n";

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
