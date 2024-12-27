#include "Day01.hpp"

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
