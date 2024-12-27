#include "Day01.hpp"

int main()
{
    Day01 day01;
    day01.loadData("input/day01.txt");

    std::vector<int>& _firstColume = day01.getFirstColume();
    std::vector<int>& _secondColume = day01.getSecondColume();

    // sort both vectors in ascending order
    std::sort(_firstColume.begin(), _firstColume.end());
    std::sort(_secondColume.begin(), _secondColume.end());

    // PART 1
    int sumOfDiff = day01.calculateDist();
    std::cout << "part1: " << sumOfDiff << "\n";

    // PART 2
    int similarityScore = day01.calculateSimilarityScore();
    std::cout << "part2: " << similarityScore << "\n";
}
