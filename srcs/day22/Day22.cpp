#include "Day22.hpp"

void Day22::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    while (std::getline(file, line))
        _initialNums.push_back(std::stoll(line));
}

int64_t Day22::mix(int64_t value, int64_t secretNum)
{
    return value ^ secretNum;
}

int64_t Day22::prune(int64_t secretNum)
{
    return secretNum % 16777216;
}

int64_t Day22::getNext(int64_t num)
{
    int64_t next = num * 64;
    next = mix(next, num);
    next = prune(next);
    int64_t temp = next / 32;
    next = mix(temp, next);
    next = prune(next);
    temp = next * 2048;
    next = mix(temp, next);
    next = prune(next);
    return next;
}

void Day22::solvePart1()
{
    int64_t res = 0;
    for (const auto& num : _initialNums)
    {
        int64_t next = num;
        for (int i = 0; i < 2000; ++i)
            next = getNext(next);
        res += next;
    }
    std::cout << "part1: " << res << "\n";
}

std::vector<Day22::PriceVec> Day22::getAllPrices()
{
    std::vector<std::vector<BananaPrice>> allPrices;
    for (const auto& num : _initialNums)
    {
        std::vector<BananaPrice> prices;
        int64_t next = num;
        int currentPrice = next % 10;
        prices.push_back({currentPrice, 0});
        for (int i = 0; i < 2000; ++i)
        {
            next = getNext(next);
            currentPrice = next % 10;
            prices.push_back({currentPrice, currentPrice - prices.back().price});
        }
        allPrices.push_back(prices);
    }
    return allPrices;
}

bool Day22::isUniqueSeq(const std::vector<int>& sequence, 
                        const std::vector<std::vector<int>>& sequences)
{
    for (const auto& seq : sequences)
    {
        if (seq == sequence)
            return false;
    }
    return true;
}

// part2 takes about 3 minutes to execute
void Day22::solvePart2()
{
    // get all buyers' BananaPrice (including price and change)
    std::vector<PriceVec> allPrices = getAllPrices();

    // key: sequence of four consecutive changes
    // value: bananas count
    std::map<std::vector<int>, int> bananaCount;
    for (const auto& prices : allPrices)
    {
        std::vector<std::vector<int>> sequences;
        for (int i = 1; i < static_cast<int>(prices.size()) - 3; ++i)
        {
            std::vector<int> changes;
            for (int j = 0; j < 4; ++j)
                changes.push_back(prices[i + j].change);
            if (!isUniqueSeq(changes, sequences))
                continue ;
            sequences.push_back(changes);
            if (bananaCount.find(changes) == bananaCount.end())
                bananaCount[changes] = prices[i + 3].price;
            else
                bananaCount[changes] += prices[i + 3].price;
        }
    }

    int maxBananas = 0;
    for (const auto& [changes, bananas] : bananaCount)
    {
        if (bananas > maxBananas)
            maxBananas = bananas;
    }
    std::cout << "part2: " << maxBananas << "\n";
}
