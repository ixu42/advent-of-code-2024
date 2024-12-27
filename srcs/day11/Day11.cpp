#include "Day11.hpp"

bool Day11::loadData(const std::string& filename)
{
    std::fstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << filename << "\n";
        return false;
    }
    std::string line, stone;
    std::getline(file, line);
    std::stringstream ss(line);
    while (ss >> stone)
        _stonesVec.push_back(std::stoull(stone));
    return true;
}

bool Day11::hasEvenNumOfDigits(BigInt stone)
{
    if (stone == 0)
        return false;
    BigInt count = 0;
    while (stone)
    {
        count++;
        stone /= 10;
    }
    return count % 2 == 0;
}

std::pair<BigInt, BigInt> Day11::splitNumber(BigInt stone)
{
    int digits = 0;
    BigInt temp = stone;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    int half_digits = digits / 2;

    BigInt left = stone / static_cast<BigInt>(pow(10, half_digits));
    BigInt right = stone % static_cast<BigInt>(pow(10, half_digits));

    return {left, right};
}

void Day11::solvePart1()
{
    size_t blinks = 25;
    std::vector<BigInt> stonesVec = _stonesVec;
    for (size_t i = 0; i < blinks; i++)
    {
        std::vector<BigInt> newStonesVec; // to hold updated stones
        newStonesVec.reserve(stonesVec.size() * 2);
        for (size_t j = 0; j < stonesVec.size(); j++)
        {
            if (stonesVec[j] == 0)
                newStonesVec.push_back(1);
            else if (hasEvenNumOfDigits(stonesVec[j]))
            {
                auto [left, right] = splitNumber(stonesVec[j]);
                newStonesVec.push_back(left);
                newStonesVec.push_back(right);
            }
            else
                newStonesVec.push_back(stonesVec[j] * 2024);
        }
        stonesVec.swap(newStonesVec);
    }
    std::cout << "part1: " << stonesVec.size() << "\n";
}

void Day11::updateMap(std::unordered_map<BigInt, BigInt>& stonesMap, 
                        size_t blinks)
{
    for (size_t i = 0; i < blinks; i++)
    {
        std::unordered_map<BigInt, BigInt> newStonesMap;
        newStonesMap.reserve(newStonesMap.size() * 2);
        for (auto [key, value] : stonesMap)
        {
            if (key == 0)
            {
                if (newStonesMap.find(1) == newStonesMap.end())
                    newStonesMap[1] = value;
                else
                    newStonesMap[1] += value;
            }
            else if (hasEvenNumOfDigits(key))
            {
                auto [left, right] = splitNumber(key);
                if (newStonesMap.find(left) == newStonesMap.end())
                    newStonesMap[left] = value;
                else
                    newStonesMap[left] += value;
                if (newStonesMap.find(right) == newStonesMap.end())
                    newStonesMap[right] = value;
                else
                    newStonesMap[right] += value;
            }
            else
            {
                if (newStonesMap.find(key * 2024) == newStonesMap.end())
                    newStonesMap[key * 2024] = value;
                else
                    newStonesMap[key * 2024] += value;
            }
        }
        stonesMap.swap(newStonesMap);
    }
}

void Day11::solvePart2()
{
    size_t blinks = 75;
    std::unordered_map<BigInt, BigInt> stonesMap;
    for (BigInt i : _stonesVec)
    {
        if (stonesMap.find(i) == stonesMap.end())
            stonesMap[i] = 1;
        else
            stonesMap[i]++;
    }
    updateMap(stonesMap, blinks);
    BigInt res = 0;
    for (auto [key, value] : stonesMap)
        res += value;
    std::cout << "part2: " << res << "\n";
}
