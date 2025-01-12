#include "Day25.hpp"

bool Day25::parseLine(const std::string& line, std::vector<std::string>& lock,
    std::vector<std::string>& key, bool& startLoading, bool& loadingLocks,
    bool& loadingKeys)
{
    if (line.empty())
    {
        startLoading = true;
        if (loadingLocks)
        {
            _lockGrids.push_back(lock);
            lock.clear();
        }
        else if (loadingKeys)
        {
            _keyGrids.push_back(key);
            key.clear();
        }
        loadingLocks = false;
        loadingKeys = false;
        return false ;
    }
    else
    {
        if (startLoading)
        {
            startLoading = false;
            if (line.find("#") != std::string::npos)
            {
                loadingLocks = true;
                lock.push_back(line);
            }
            else
            {
                loadingKeys = true;
                key.push_back(line);
            }
        }
        else
        {
            if (loadingLocks)
                lock.push_back(line);
            else if (loadingKeys)
                key.push_back(line);
        }
    }
    return true;
}

std::vector<std::vector<int>> Day25::calculatePinHeights(
    const std::vector<std::vector<std::string>>& items)
{
    std::vector<std::vector<int>> pinHeights;
    for (const auto& item : items)
    {
        int cols = item[0].size();
        int rows = item.size();
        std::vector<int> lock;
        for (int col = 0; col < cols; col++)
        {
            int pinHeight = -1;
            for (int row = 0; row < rows; row++)
            {
                if (item[row][col] == '#')
                    pinHeight++;
            }
            lock.push_back(pinHeight);
        }
        pinHeights.push_back(lock);
    }
    return pinHeights;
}

void Day25::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    std::vector<std::string> lock;
    std::vector<std::string> key;
    bool startLoading = true;
    bool loadingLocks = false;
    bool loadingKeys = false;

    while (std::getline(file, line))
    {
        if (!parseLine(line, lock, key, startLoading, loadingLocks, loadingKeys))
            continue ;
    }

    if (loadingLocks)
        _lockGrids.push_back(lock);
    else if (loadingKeys)
        _keyGrids.push_back(key);

    _locks = calculatePinHeights(_lockGrids);
    _keys = calculatePinHeights(_keyGrids);
    _gridHeight = _lockGrids[0].size();
}

void Day25::solve()
{
    int cols = _locks[0].size();
    int matchingHeight = _gridHeight - 2;
    int fitCount = 0;

    for (const auto& lock : _locks)
    {
        for (const auto& key : _keys)
        {
            bool fit = true;
            for (int i = 0; i < cols; ++i)
            {
                int lockPinHeight = lock[i];
                int keyPinHeight = key[i];
                if (lockPinHeight + keyPinHeight > matchingHeight)
                {
                    fit = false;
                    break ;
                }
            }
            if (fit)
                fitCount++;
        }
    }

    std::cout << "day25: " << fitCount << "\n";
}
