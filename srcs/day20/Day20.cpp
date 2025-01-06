#include "Day20.hpp"

void Day20::printMap(const CharGrid& map) const
{
    std::cout << "rows: " << _rows << " cols: " << _cols << "\n";
    std::cout << "start: " << _start.y << " " << _start.x << "\n";
    for (const auto& row : map)
    {
        for (const auto& c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

void Day20::initStartPos()
{
    for (int y = 0; y < _rows; ++y)
    {
        for (int x = 0; x < _cols; ++x)
        {
            if (_map[y][x] == 'S')
            {
                _start = {y, x};
                return ;
            }
        }
    }
}

void Day20::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + filename);
    
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row;
        for (const auto& c : line)
            row.push_back(c);
        _map.push_back(row);
    }
    _rows = _map.size();
    _cols = _map[0].size();
    initStartPos();
    // printMap(_map);
}

void Day20::markAndDrawPath(std::map<Pos, Pos>& parent, const Pos& end)
{
    CharGrid mapWithPath = _map;
    for (Pos p = end; !(p == _start); p = parent[p])
        _path.push_back(p);
    _path.push_back(_start);

    for (const Pos& p : _path)
        mapWithPath[p.y][p.x] = 'O';

    // uncomment the following to draw the path
    // for (int y = 0; y < _rows; ++y)
    // {
    //     for (int x = 0; x < _cols; ++x)
    //         std::cout << mapWithPath[y][x];
    //     std::cout << "\n";
    // }
}

std::vector<int> Day20::findPathAndRecordTime()
{
    std::queue<Pos> q;
    q.push(_start);
    std::vector<std::vector<bool>> visited(_rows, std::vector<bool>(_cols, false));
    std::vector<Pos> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::map<Pos, Pos> parent; // to track the path

    int time = 0;
    std::vector<int> timeToExit;
    while (!q.empty())
    {
        int levelSize = static_cast<int>(q.size());
        for (int i = 0; i < levelSize; ++i)
        {
            Pos cur = q.front();
            q.pop();

            for (const auto& d : dirs)
            {
                Pos next = {cur.y + d.y, cur.x + d.x};
                if (next.y < 0 || next.y >= _rows || next.x < 0 || next.x >= _cols
                    || _map[next.y][next.x] == '#' || visited[next.y][next.x])
                    continue ;

                parent[next] = cur;
                if (_map[next.y][next.x] == 'E')
                {
                    markAndDrawPath(parent, next);
                    timeToExit.push_back(time + 1); // include the step to 'E'
                }
                q.push(next);
                visited[next.y][next.x] = true;
            }
        }
        time++;
    }
    return timeToExit;
}

int Day20::timeSaved(int timeWithoutCheats) const
{
    std::queue<Pos> q;
    q.push(_start);
    std::vector<std::vector<bool>> visited(_rows, std::vector<bool>(_cols, false));
    std::vector<Pos> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int time = 0;
    while (!q.empty())
    {
        int levelSize = static_cast<int>(q.size());
        for (int i = 0; i < levelSize; ++i)
        {
            Pos cur = q.front();
            q.pop();

            for (const auto& d : dirs)
            {
                Pos next = {cur.y + d.y, cur.x + d.x};
                if (next.y < 0 || next.y >= _rows || next.x < 0 || next.x >= _cols
                    || _map[next.y][next.x] == '#' || visited[next.y][next.x])
                    continue ;
                if (_map[next.y][next.x] == 'E')
                    return timeWithoutCheats - (time + 1);
                q.push(next);
                visited[next.y][next.x] = true;
            }
        }
        time++;
    }
    return -1;
}

// brute force, takes about 17 seconds to execute part1
void Day20::solvePart1()
{
    std::vector<int> timeToExit = findPathAndRecordTime();
    // run the following to verify that only one path exists
    // std::cout << "path count: " << timeToExit.size() << "\n";
    // std::cout << "time to exit: ";
    // for (const auto& t : timeToExit)
    //     std::cout << t << " ";
    // std::cout << "\n";

    int res = 0;
    for (int y = 1; y < _rows - 1; ++y)
    {
        for (int x = 1; x < _cols - 1; ++x)
        {
            if (_map[y][x] == '#')
            {
                _map[y][x] = '.';
                if (timeSaved(timeToExit[0]) >= 100)
                    res++;
                _map[y][x] = '#';
            }   
        }
    }
    std::cout << "part1: " << res << "\n";
}

/**
 * if a cheat has the same start and end positions, it's the same cheat =>
 * part2 checks two positions on the path, if the sum of their horizontal 
 * and vertical distances is within 20, and the cheat saves at least 100 steps, 
 * it is considered valid in part2.
 */
void Day20::solvePart2()
{
    std::vector<int> timeToExit = findPathAndRecordTime();

    int pathSize = static_cast<int>(_path.size());
    int res = 0;

    for (int i = 0; i < pathSize - 1; ++i)
    {
        for (int j = i + 1; j < pathSize; ++j)
        {
            int diff = std::abs(_path[i].y - _path[j].y) + std::abs(_path[i].x - _path[j].x);
            if (diff > 20)
                continue ;
            int remainingtime = i + pathSize - 1 - j;
            int timeSaved = timeToExit[0] - (diff + remainingtime);
            if (timeSaved >= 100)
                res++;
        }
    }
    std::cout << "part2: " << res << "\n";
}
