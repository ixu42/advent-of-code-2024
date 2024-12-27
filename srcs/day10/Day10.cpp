#include "Day10.hpp"

bool Day10::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << fileName << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        for (char c : line)
            row.push_back(std::stoi(std::string(1, c)));
        _map.push_back(row);
    }

    _rowSize = _map.size();
    _colSize = _map[0].size();

    return true;
}

int Day10::bfs(const Grid& grid, int startX, int startY)
{
    std::queue<Point> q;
    std::set<Point> visited; // not necessary to revisit tiles
    std::set<Point> reachable9;

    q.push({startX, startY});
    visited.insert({startX, startY});

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (const auto& [dx, dy] : directions)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < _rowSize && ny < _colSize)
            {
                if (grid[nx][ny] == grid[x][y] + 1 
                && visited.find({nx, ny}) == visited.end())
                {
                    visited.insert({nx, ny});
                    q.push({nx, ny});
                    if (grid[nx][ny] == 9)
                        reachable9.insert({nx, ny});
                }
            }
        }
    }
    return reachable9.size();
}

void Day10::solvePart1()
{
    int totalScore = 0;
    for (int x = 0; x < _rowSize; x++)
    {
        for (int y = 0; y < _colSize; y++)
        {
            if (_map[x][y] == 0)
                totalScore += bfs(_map, x, y);
        }
    }
    std::cout << "part1: " << totalScore << "\n";
}

int Day10::dfs(const Grid& grid, int x, int y, 
                std::set<Point>& visited)
{
    if (grid[x][y] == 9)
        return 1;

    int count = 0;
    for (const auto& [dx, dy] : directions)
    {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && ny >= 0 && nx < _rowSize && ny < _colSize)
        {
            if (grid[nx][ny] == grid[x][y] + 1 
                && visited.find({nx, ny}) == visited.end())
            {
                visited.insert({nx, ny});
                count += dfs(grid, nx, ny, visited);
                visited.erase({nx, ny}); // unmark the tile for other paths
            }
        }
    }
    return count;
}

void Day10::solvePart2()
{
    int totalRatings = 0;
    std::set<Point> visited;
    for (int x = 0; x < _rowSize; x++)
    {
        for (int y = 0; y < _colSize; y++)
        {
            if (_map[x][y] == 0)
            {
                visited.insert({x, y});
                int rating = dfs(_map, x, y, visited);
                totalRatings += rating;
            }
        }
    }
    std::cout << "part2: " << totalRatings << "\n";
}
