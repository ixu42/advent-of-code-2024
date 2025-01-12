#include "Day25.hpp"

int main()
{
    try
    {
        Day25 day25;
        day25.loadData("input/day25.txt");
        day25.solve();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
