#include "../../include/Day09.hpp"

void Day09::printLine(const std::vector<int>& line)
{
    for (int c : line)
    {
        if (c > 10)
            std::cout << "(" << c << ")";
        else if (c == -1)
            std::cout << ".";
        else
            std::cout << c;
    }
    std::cout << "\n";
}

bool Day09::hasGap(const std::vector<int>& line)
{
    bool dotOccurred = false;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == -1)
            dotOccurred = true;
        if (dotOccurred && line[i] != -1)
            return true;
    }
    return false;
}

bool Day09::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << fileName << '\n';
        return false;
    }
    std::string line;
    std::getline(file, line);

    bool isFile = true;
    int id = 0;
    for (char c : line)
    {
        if (isFile)
        {
            for (int n = 0; n < c - '0'; n++)
                _extended.push_back(id);
            id++;
        }
        else
        {
            for (int n = 0; n < c - '0'; n++)
                _extended.push_back(-1);
        }
        isFile = !isFile;
    }
    return true;
}

uint64_t Day09::calculateChecksum(const std::vector<int>& line)
{
    uint64_t res = 0;
    for (uint64_t i = 0; i < static_cast<uint64_t>(line.size()); i++)
    {
        if (line[i] == -1)
            continue ;
        res += line[i] * i;
    }
    return res;
}

void Day09::solvePart1()
{
    std::vector<int> rearranged = _extended;
    // move file block one at a time from back to front
    for (int i = rearranged.size() - 1; i >= 0; i--)
    {
        if (!hasGap(rearranged))
            break ;
        if (rearranged[i] != -1)
        {
            int temp = rearranged[i];
            rearranged[i] = -1;
            for (int j = 0; j < i; j++)
            {
                if (rearranged[j] == -1)
                {
                    rearranged[j] = temp;
                    break ;
                }
            }
        }
    }
    std::cout << "part1: " << calculateChecksum(rearranged) << "\n";
}

void Day09::findSpaceAndInsert(std::vector<int>& rearranged, 
                                std::map<int, int, std::greater<int>>& fileSizes, 
                                std::map<int, int, std::greater<int>>& fileStartPos)
{
    for (const auto& [id, size] : fileSizes)
    {
        if (id == 0)
            break ;
        // find the leftmost free span of sufficient size
        for (int j = 0; j < fileStartPos[id]; j++)
        {
            if (rearranged[j] != -1)
                continue ;

            int k = j;
            while (rearranged[k] == -1)
                k++;
            if (k - j >= size)
            {
                for (int l = j; l < j + size; l++)
                    rearranged[l] = id;
                // replace previous file ids with '.'
                for (int l = fileStartPos[id]; l < fileStartPos[id] + fileSizes[id]; l++)
                    rearranged[l] = -1;
                break ;
            }
            else
                j = k;
        }
    }
}

void Day09::solvePart2()
{
    std::vector<int> rearranged = _extended;
    int id;
    int size = 0;
    int i = rearranged.size() - 1;
    std::map<int, int, std::greater<int>> fileSizes;
    std::map<int, int, std::greater<int>> fileStartPos;
    while (i >= 0)
    {
        if (rearranged[i] == -1)
        {
            i--;
            continue ;
        }
        id = rearranged[i];
        size = 1;
        i--;
        while (i >= 0 && rearranged[i] == id)
        {
            size++;
            i--;
        }
        fileSizes[id] = size;
        fileStartPos[id] = i + 1;
    }

    findSpaceAndInsert(rearranged, fileSizes, fileStartPos);
    std::cout << "part2: " << calculateChecksum(rearranged) << "\n";
}
