#include "Day15.hpp"

void Day15::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);
    
    std::string line;
    bool mapLoaded = false;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            mapLoaded = true;
            continue;
        }
        if (!mapLoaded)
        {
            std::vector<char> row;
            for (char c : line)
                row.push_back(c);
            _map.push_back(row);
        }
        else
            _movements += line;
    }
    _rowSize = _map.size();
    _colSize = _map[0].size();
}

void Day15::printMap(const CharGrid& map)
{
    for (const auto& row : map)
    {
        for (char c : row)
            std::cout << c;
        std::cout << "\n";
    }
    std::cout << "\n";
}

// get current position of the robot on map
void Day15::getCurrPos(const CharGrid& map, int& currY, int& currX)
{
    for (int y = 0; y < _rowSize; ++y)
    {
        for (int x = 0; x < _colSize; ++x)
        {
            if (map[y][x] == '@')
            {
                currY = y;
                currX = x;
                break ;
            }
        }
    }
}

Direction Day15::getDirection(char move)
{
    Direction d;
    switch (move)
    {
        case '^':
            d = Direction::UP;
            break ;
        case 'v':
            d = Direction::DOWN;
            break ;
        case '<':
            d = Direction::LEFT;
            break ;
        case '>':
            d = Direction::RIGHT;
            break ;
        default: 
            throw std::runtime_error("Invalid movement");
    }
    return d;
}

void Day15::getNextPos(Direction d, int currY, int currX, int& nextY, int& nextX)
{
    int dy, dx;
    switch (d)
    {
        case Direction::UP:
            dy = -1;
            dx = 0;
            break ;
        case Direction::DOWN:
            dy = 1;
            dx = 0;
            break ;
        case Direction::LEFT:
            dy = 0;
            dx = -1;
            break ;
        case Direction::RIGHT:
            dy = 0;
            dx = 1;
            break ;
        default:
            throw std::runtime_error("Invalid direction");
    }
    nextY = currY + dy;
    nextX = currX + dx;
}

// recursive function for cascading push
bool Day15::push(CharGrid& map, int currY, int currX, Direction d)
{
    int nextY, nextX;
    getNextPos(d, currY, currX, nextY, nextX);

    if (nextY < 0 || nextY >= _rowSize || nextX < 0 || nextX >= _colSize 
        || map[nextY][nextX] == '#')
        return false;

    if (map[nextY][nextX] == 'O')
    {
        if (!push(map, nextY, nextX, d))
            return false;
    }

    if (map[nextY][nextX] == '.')
    {
        map[nextY][nextX] = 'O';
        map[currY][currX] = '.';
        return true;
    }

    return false;
}

void Day15::pushBox(CharGrid& map, int nextY, int nextX, 
                    int& currY, int& currX, Direction d)
{
    if (push(map, nextY, nextX, d))
    {
        map[nextY][nextX] = '@';
        map[currY][currX] = '.';
        currY = nextY;
        currX = nextX;
    }
}

int Day15::getResPart1(const CharGrid& map)
{
    int res = 0;
    for (int y = 0; y < _rowSize; ++y)
    {
        for (int x = 0; x < _colSize; ++x)
        {
            if (map[y][x] == 'O')
                res += y * 100 + x;
        }
    }
    return res;
}

void Day15::solvePart1()
{
    CharGrid map = _map;
    int currX, currY;
    getCurrPos(map, currY, currX);
    for (char move : _movements)
    {
        // printMap(map);
        // std::cout << "move " << move << "\n";
        Direction d = getDirection(move);
        int nextY, nextX;
        getNextPos(d, currY, currX, nextY, nextX);
        if (nextY < 0 || nextY >= _rowSize || nextX < 0 || nextX >= _colSize 
            || map[nextY][nextX] == '#')
            continue ;
        else if (map[nextY][nextX] == 'O')
            pushBox(map, nextY, nextX, currY, currX, d);
        else if (map[nextY][nextX] == '.')
        {
            map[currY][currX] = '.';
            currY = nextY;
            currX = nextX;
            map[currY][currX] = '@';
        }
    }
    // printMap(map);
    std::cout << "part1: " << getResPart1(map) << "\n";
}

Day15::CharGrid Day15::updateMap()
{
    CharGrid newMap;
    for (const auto& row : _map)
    {
        std::vector<char> newRow;
        for (char c : row)
        {
            switch (c)
            {
                case '#':
                    newRow.push_back('#');
                    newRow.push_back('#');
                    break ;
                case '.':
                    newRow.push_back('.');
                    newRow.push_back('.');
                    break ;
                case 'O':
                    newRow.push_back('[');
                    newRow.push_back(']');
                    break ;
                case '@':
                    newRow.push_back('@');
                    newRow.push_back('.');
                    break ;
                default:
                    throw std::runtime_error("Invalid character in map");
            }
        }
        newMap.push_back(newRow);
    }
    return newMap;
}

bool Day15::pushHorizontally(CharGrid& map, int currY, int currX, Direction d)
{
    int nextY, nextX;
    getNextPos(d, currY, currX, nextY, nextX);

    if (nextX < 0 || nextX >= _colSize || map[nextY][nextX] == '#')
        return false;

    char next = map[nextY][nextX];
    if (next == '[' || next == ']')
    {
        if (!pushHorizontally(map, nextY, nextX, d))
            return false;
    }
    next = map[nextY][nextX];
    if ((next == '[' || next == ']'))
        return true;
    if (next == '.')
    {
        if (d == Direction::LEFT)
        {
            map[nextY][nextX] = '[';
            map[nextY][nextX + 1] = ']';
            map[nextY][nextX + 2] = '.';
        }
        else
        {
            map[nextY][nextX] = ']';
            map[nextY][nextX - 1] = '[';
            map[nextY][nextX - 2] = '.';
        }
        return true;
    }
    return false;
}

// move boxes from the end of the traversed path
void Day15::moveBoxesVertically(CharGrid& map, std::vector<Point>& visitedBoxes, int dy)
{
    for (int i = visitedBoxes.size() - 1; i >= 0; i--)
    {
        int nextY = visitedBoxes[i].y + dy;
        int nextX = visitedBoxes[i].x;

        if (nextY < 0 || nextY >= _rowSize)
            continue ;

        map[nextY][nextX] = map[visitedBoxes[i].y][visitedBoxes[i].x];
        map[visitedBoxes[i].y][visitedBoxes[i].x] = '.';
    }
}

// treat the boxes as a tree structure
bool Day15::pushVertically(CharGrid& map, int currY, int currX, Direction d)
{
    std::queue<Point> q;
    q.push({currY, currX});
    if (map[currY][currX] == ']')
        q.push({currY, currX - 1});
    else if (map[currY][currX] == '[')
        q.push({currY, currX + 1});

    std::map<Point, bool> visited;
    std::vector<Point> visitedBoxes;

    int dy = (d == Direction::UP) ? -1 : 1;

    while (!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if (visited[curr])
            continue ;

        visited[curr] = true;
        visitedBoxes.push_back(curr);

        int nextY = curr.y + dy;
        int nextX = curr.x;

        if (nextY < 0 || nextY >= _rowSize)
            continue ;

        char next = map[nextY][nextX];
        if (next == '.')
            continue ;
        else if (next == '#')
            return false;
        else if (next == ']')
        {
            q.push({nextY, nextX});
            q.push({nextY, nextX - 1});
        }
        else if (next == '[')
        {
            q.push({nextY, nextX});
            q.push({nextY, nextX + 1});
        }
    }
    moveBoxesVertically(map, visitedBoxes, dy);
    return true;
}

void Day15::pushRobot(CharGrid& map, int nextY, int nextX, int& currY, int& currX)
{
    map[nextY][nextX] = '@';
    map[currY][currX] = '.';
    currY = nextY;
    currX = nextX;
}

void Day15::pushBoxPart2(CharGrid& map, int nextY, int nextX, 
                            int& currY, int& currX, Direction d)
{
    if (d == Direction::LEFT || d == Direction::RIGHT)
    {
        if (pushHorizontally(map, nextY, nextX, d))
            pushRobot(map, nextY, nextX, currY, currX);
    }
    else if (d == Direction::UP || d == Direction::DOWN)
    {
        if (pushVertically(map, nextY, nextX, d))
            pushRobot(map, nextY, nextX, currY, currX);
    }
}

int Day15::getResPart2(const CharGrid& map)
{
    int res = 0;
    for (int y = 0; y < _rowSize; ++y)
    {
        for (int x = 0; x < _colSize; ++x)
        {
            if (map[y][x] == '[')
                res += y * 100 + x;
        }
    }
    return res;
}

void Day15::solvePart2()
{
    CharGrid map = updateMap();
    _colSize *= 2;
    int currX, currY;
    getCurrPos(map, currY, currX);
    for (char move : _movements)
    {
        // printMap(map);
        // std::cout << "move " << move << "\n";
        Direction d = getDirection(move);
        int nextY, nextX;
        getNextPos(d, currY, currX, nextY, nextX);
        if (nextY < 0 || nextY >= _rowSize || nextX < 0 || nextX >= _colSize 
            || map[nextY][nextX] == '#')
            continue ;
        else if (map[nextY][nextX] == '[' || map[nextY][nextX] == ']')
            pushBoxPart2(map, nextY, nextX, currY, currX, d);
        else if (map[nextY][nextX] == '.')
        {
            map[currY][currX] = '.';
            currY = nextY;
            currX = nextX;
            map[currY][currX] = '@';
        }
    }
    // printMap(map);
    std::cout << "part2: " << getResPart2(map) << "\n";
}
