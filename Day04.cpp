#include "include/Day04.hpp"

void Day04::printGrid(std::vector<std::vector<char>> grid)
{
    for (auto& row : grid)
    {
        for (auto c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

bool Day04::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<char> row;
            for (auto c : line)
                row.push_back(c);
            _data.push_back(row);
        }
    }
    else
    {
        std::cerr << "Unable to open file " << fileName << "\n";
        return false;
    }
    /* uncomment to print initial grid */
    // printGrid(_data);
    return true;
}

void Day04::solvePart1()
{
    std::vector<std::vector<char>> updateData(_data.size(), std::vector<char>(_data[0].size(), '.'));

    for (size_t i = 0; i < _data.size(); i++)
    {
        for (size_t j = 0; j < _data[i].size(); j++)
        {
            if (_data[i][j] == 'X')
            {
                // search horizontally
                if (j + 1 < _data[i].size() && _data[i][j + 1] == 'M'
                    && j + 2 < _data[i].size() && _data[i][j + 2] == 'A'
                    && j + 3 < _data[i].size() && _data[i][j + 3] == 'S')
                    {
                        updateData[i][j] = 'X';
                        updateData[i][j + 1] = 'M';
                        updateData[i][j + 2] = 'A';
                        updateData[i][j + 3] = 'S';
                        _resPart1++;
                    }
                // search vertically
                if ((i + 1 < _data.size() && _data[i + 1][j] == 'M')
                    && (i + 2 < _data.size() && _data[i + 2][j] == 'A')
                    && (i + 3 < _data.size() && _data[i + 3][j] == 'S'))
                    {
                        updateData[i][j] = 'X';
                        updateData[i + 1][j] = 'M';
                        updateData[i + 2][j] = 'A';
                        updateData[i + 3][j] = 'S';
                        _resPart1++;
                    }
                // search diagonally
                if ((i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'M')
                    && (i + 2 < _data.size() && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'A')
                    && (i + 3 < _data.size() && j + 3 < _data[i + 3].size() && _data[i + 3][j + 3] == 'S'))
                    {
                        updateData[i][j] = 'X';
                        updateData[i + 1][j + 1] = 'M';
                        updateData[i + 2][j + 2] = 'A';
                        updateData[i + 3][j + 3] = 'S';
                        _resPart1++;
                    }
                if (i + 1 < _data.size() && j - 1 >= 0 && _data[i + 1][j - 1] == 'M'
                    && i + 2 < _data.size() && j - 2 >= 0 && _data[i + 2][j - 2] == 'A'
                    && i + 3 < _data.size() && j - 3 >= 0 && _data[i + 3][j - 3] == 'S')
                    {
                        updateData[i][j] = 'X';
                        updateData[i + 1][j - 1] = 'M';
                        updateData[i + 2][j - 2] = 'A';
                        updateData[i + 3][j - 3] = 'S';
                        _resPart1++;
                    }
            }
            else if (_data[i][j] == 'S')
            {
                if (j + 1 < _data[i].size() && _data[i][j + 1] == 'A'
                    && j + 2 < _data[i].size() && _data[i][j + 2] == 'M'
                    && j + 3 < _data[i].size() && _data[i][j + 3] == 'X')
                    {
                        updateData[i][j] = 'S';
                        updateData[i][j + 1] = 'A';
                        updateData[i][j + 2] = 'M';
                        updateData[i][j + 3] = 'X';
                        _resPart1++;
                    }
                if ((i + 1 < _data.size() && _data[i + 1][j] == 'A')
                    && (i + 2 < _data.size() && _data[i + 2][j] == 'M')
                    && (i + 3 < _data.size() && _data[i + 3][j] == 'X'))
                    {
                        updateData[i][j] = 'S';
                        updateData[i + 1][j] = 'A';
                        updateData[i + 2][j] = 'M';
                        updateData[i + 3][j] = 'X';
                        _resPart1++;
                    }
                if ((i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'A')
                    && (i + 2 < _data.size() && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'M')
                    && (i + 3 < _data.size() && j + 3 < _data[i + 3].size() && _data[i + 3][j + 3] == 'X'))
                    {
                        updateData[i][j] = 'S';
                        updateData[i + 1][j + 1] = 'A';
                        updateData[i + 2][j + 2] = 'M';
                        updateData[i + 3][j + 3] = 'X';
                        _resPart1++;
                    }
                if (i + 1 < _data.size() && j - 1 >= 0 && _data[i + 1][j - 1] == 'A'
                    && i + 2 < _data.size() && j - 2 >= 0 && _data[i + 2][j - 2] == 'M'
                    && i + 3 < _data.size() && j - 3 >= 0 && _data[i + 3][j - 3] == 'X')
                    {
                        updateData[i][j] = 'S';
                        updateData[i + 1][j - 1] = 'A';
                        updateData[i + 2][j - 2] = 'M';
                        updateData[i + 3][j - 3] = 'X';
                        _resPart1++;
                    }
            }
        }
    }
    /* uncomment to print the grid after each irrelevant char is replaced with '.' */
    // printGrid(updateData);
    std::cout << "part1: " << _resPart1 << "\n";
}

void Day04::solvePart2()
{
    std::vector<std::vector<char>> updateData(_data.size(), std::vector<char>(_data[0].size(), '.'));

    for (size_t i = 0; i < _data.size(); i++)
    {
        for (size_t j = 0; j < _data[i].size(); j++)
        {
            if (_data[i][j] == 'M')
            {
                // X-MAS with first row being 'M.S'
                if (j + 2 < _data[i].size() && _data[i][j + 2] == 'S'
                    && i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'A'
                    && i + 2 < _data.size() && _data[i + 2][j] == 'M'
                    && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'S')
                    {
                        updateData[i][j] = 'M';
                        updateData[i][j + 2] = 'S';
                        updateData[i + 1][j + 1] = 'A';
                        updateData[i + 2][j] = 'M';
                        updateData[i + 2][j + 2] = 'S';
                        _resPart2++;
                    }
                // X-MAS with first row being 'M.M'
                if (j + 2 < _data[i].size() && _data[i][j + 2] == 'M'
                    && i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'A'
                    && i + 2 < _data.size() && _data[i + 2][j] == 'S'
                    && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'S')
                    {
                        updateData[i][j] = 'M';
                        updateData[i][j + 2] = 'M';
                        updateData[i + 1][j + 1] = 'A';
                        updateData[i + 2][j] = 'S';
                        updateData[i + 2][j + 2] = 'S';
                        _resPart2++;
                    }
            }
            else if (_data[i][j] == 'S')
            {
                // X-MAS with first row being 'S.M'
                if (j + 2 < _data[i].size() && _data[i][j + 2] == 'M'
                    && i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'A'
                    && i + 2 < _data.size() && _data[i + 2][j] == 'S'
                    && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'M')
                    {
                        updateData[i][j] = 'S';
                        updateData[i][j + 2] = 'M';
                        updateData[i + 1][j + 1] = 'A';
                        updateData[i + 2][j] = 'S';
                        updateData[i + 2][j + 2] = 'M';
                        _resPart2++;
                    }
                // X-MAS with first row being 'S.S'
                if (j + 2 < _data[i].size() && _data[i][j + 2] == 'S'
                    && i + 1 < _data.size() && j + 1 < _data[i + 1].size() && _data[i + 1][j + 1] == 'A'
                    && i + 2 < _data.size() && _data[i + 2][j] == 'M'
                    && j + 2 < _data[i + 2].size() && _data[i + 2][j + 2] == 'M')
                    {
                        updateData[i][j] = 'S';
                        updateData[i][j + 2] = 'S';
                        updateData[i + 1][j + 1] = 'A';
                        updateData[i + 2][j] = 'M';
                        updateData[i + 2][j + 2] = 'M';
                        _resPart2++;
                    }
            }
        }
    }
    /* uncomment to print the grid after each irrelevant char is replaced with '.' */
    // printGrid(updateData);
    std::cout << "part2: " << _resPart2 << "\n";
}

int main()
{
    Day04 day04;
    if (!day04.loadData("input/Day04.txt"))
        return 1;
    day04.solvePart1();
    day04.solvePart2();
}
