#include "../../include/Day06.hpp"

void Day06::printGrid(const std::vector<std::vector<char>>& grid)
{
    for (const auto& row : grid)
    {
        for (char c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

void Day06::getInitialPos()
{
    for (size_t r = 0; r < _data.size(); r++)
    {
        for (size_t c = 0; c < _data[r].size(); c++)
        {
            if (_data[r][c] == '^')
            {
                _initialPos = std::make_pair(r, c);
                return ;
            }
        }
    }
}

bool Day06::initData(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << fileName << "\n";
        return false;
    }

    while (std::getline(file, line))
    {
        std::vector<char> row;
        for (char c : line)
            row.push_back(c);
        _data.push_back(row);
    }
    getInitialPos();
    return true;
}

std::pair<int, int> Day06::getDirection(Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
            return std::make_pair(-1, 0);
        case Direction::DOWN:
            return std::make_pair(1, 0);
        case Direction::LEFT:
            return std::make_pair(0, -1);
        case Direction::RIGHT:
            return std::make_pair(0, 1);
    }
    return std::make_pair(-1, 0);
}

std::pair<int, int> Day06::getNextPos(const std::pair<int, int>& currPos, 
                                        Direction currDirection)
{
    std::pair<int, int> direction = getDirection(currDirection);
    std::pair<int, int> nextPos;
    nextPos = std::make_pair(currPos.first + direction.first, 
                                currPos.second + direction.second);
    return nextPos;
}

void Day06::changeDirection(Direction& currDirection)
{
    switch (currDirection)
    {
        case Direction::UP:
            currDirection = Direction::RIGHT;
            break ;
        case Direction::RIGHT:
            currDirection = Direction::DOWN;
            break ;
        case Direction::DOWN:
            currDirection = Direction::LEFT;
            break ;
        case Direction::LEFT:
            currDirection = Direction::UP;
            break ;
    }
}

int Day06::calculateVisited(const std::vector<std::vector<char>>& grid)
{
    int res = 0;
    for (const auto& row : grid)
    {
        for (char c : row)
        {
            if (c == 'X')
                res++;
        }
    }
    return res;
}

void Day06::solvePart1()
{
    _dataWithPath = _data;
    std::pair<int, int> currPos = _initialPos;
    Direction currDirection = _initialDirection;
    while (currPos.first >= 0 && currPos.second >= 0 
            && currPos.first < static_cast<int>(_data.size()) 
            && currPos.second < static_cast<int>(_data[currPos.first].size()) 
            && _data[currPos.first][currPos.second] != '#')
    {
        _dataWithPath[currPos.first][currPos.second] = 'X';

        std::pair<int, int> nextPos = getNextPos(currPos, currDirection);

        if (nextPos.first < 0 || nextPos.second < 0 
            || nextPos.first >= static_cast<int>(_data.size()) 
            || nextPos.second >= static_cast<int>(_data[nextPos.first].size()))
            break;

        if (_data[nextPos.first][nextPos.second] == '#')
            changeDirection(currDirection);

        currPos = getNextPos(currPos, currDirection);
    }
    std::cout << "Part1: " << calculateVisited(_dataWithPath) << "\n";
}

bool Day06::withInGrid(const std::pair<int, int>& pos, 
                        const std::vector<std::vector<char>>& grid)
{
    if (pos.first >= 0 && pos.second >= 0 
        && pos.first < static_cast<int>(grid.size()) 
        && pos.second < static_cast<int>(grid[pos.first].size()))
        return true;
    return false;
}

bool Day06::isInThePath(std::vector<std::vector<char>> dataWithPath, 
                        int r, int c)
{
    if (r < 0 || c < 0 || r >= static_cast<int>(dataWithPath.size()) 
        || c >= static_cast<int>(dataWithPath[r].size()))
        return false;
    return dataWithPath[r][c] == 'X';
}

// if same pos and direction is encountered twice, guard is stuck in loop
bool Day06::causeGuardStuckInLoop(const std::vector<std::vector<char>>& grid)
{
    std::map<std::pair<int, int>, std::set<Direction>> visited;
    std::pair<int, int> currPos = _initialPos;
    Direction currDirection = _initialDirection;
    while (withInGrid(currPos, grid)  
            && grid[currPos.first][currPos.second] != '#' 
            && grid[currPos.first][currPos.second] != 'O')
    {
        if (visited.find(currPos) != visited.end() 
            && visited[currPos].count(currDirection) > 0)
            return true;

        visited[currPos].insert(currDirection);

        std::pair<int, int> nextPos = getNextPos(currPos, currDirection);  
        while (withInGrid(nextPos, grid) 
            && (grid[nextPos.first][nextPos.second] == '#' 
            || grid[nextPos.first][nextPos.second] == 'O'))
        {
            changeDirection(currDirection);
            nextPos = getNextPos(currPos, currDirection);
        }

        currPos = nextPos;
    }
    return false;
}

void Day06::solvePart2()
{
    std::vector<std::vector<char>>  dataPart2 = _data;
    int res = 0;
    for (size_t r = 0; r < dataPart2.size(); r++)
    {
        for (size_t c = 0; c < dataPart2[r].size(); c++)
        {
            if (dataPart2[r][c] == '#' || dataPart2[r][c] == '^'
                || !isInThePath(_dataWithPath, r, c))
                continue ;
            char original = dataPart2[r][c];
            dataPart2[r][c] = 'O';
            if (causeGuardStuckInLoop(dataPart2))
                res++;
            dataPart2[r][c] = original;
        }
    }
    std::cout << "Part2: " << res << "\n";
}
