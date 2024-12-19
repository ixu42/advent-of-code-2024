#include "../include/Day01.hpp"

int Day01::calculateDist()
{
    int sumOfDiff = 0;

    for (unsigned int i = 0; i < _firstColume.size(); i++)
    {
        int currentDiff = std::abs(_firstColume[i] - _secondColume[i]);
        sumOfDiff += currentDiff;
    }

    return sumOfDiff;
}

int Day01::calculateSimilarityScore()
{
    int num;
    int counter;
    int similarityScore = 0;

    for (unsigned int i = 0; i < _firstColume.size(); i++)
    {
        num = _firstColume[i];
        counter = 0;
        for (unsigned int j = 0; j < _secondColume.size(); j++)
        {
            if (num == _secondColume[j])
                counter++;
        }
        similarityScore += num * counter;
    }

    return similarityScore;
}

void Day01::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    int num;
    while (file >> num)
    {
        _firstColume.push_back(num);
        file >> num;
        _secondColume.push_back(num);
    }
}

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
