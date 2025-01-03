#include "Day18.hpp"

void Day18::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        Pos pos;
        std::getline(ss, token, ',');
        pos.x = std::stoi(token);
        std::getline(ss, token, ',');
        pos.y = std::stoi(token);
        _bytes.push_back(pos);
    }
}

int Day18::countMinSteps(const CharGrid& grid, const Pos& start, const Pos& end)
{
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<std::pair<Pos, int>> q;
    BoolGrid visited(rows, std::vector<bool>(cols, false));
    std::vector<Pos> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    q.push({start, 0});
    visited[start.y][start.x] = true;

    while (!q.empty())
    {
        auto [pos, steps] = q.front();
        q.pop();

        if (pos.y == end.y && pos.x == end.x)
            return steps;
        for (const auto& dir : directions)
        {
            Pos nextPos = {pos.y + dir.y, pos.x + dir.x};
            if (nextPos.y >= 0 && nextPos.y < rows && nextPos.x >= 0 
                && nextPos.x < cols && !visited[nextPos.y][nextPos.x] 
                && grid[nextPos.y][nextPos.x] == '.')
            {
                q.push({nextPos, steps + 1});
                visited[nextPos.y][nextPos.x] = true;
            }
        }
    }
    return -1;
}

void Day18::solvePart1()
{
    int bytesFallen = 1024;
    int gridRows = 71;
    int gridCols = 71;
    CharGrid grid(gridRows, std::vector<char>(gridCols, '.'));

    for (int i = 0; i < bytesFallen; i++)
        grid[_bytes[i].y][_bytes[i].x] = '#';

    int steps = countMinSteps(grid, {0, 0}, {gridRows - 1, gridCols - 1});
    std::cout << "part1: " << steps << "\n";
}

void Day18::solvePart2()
{
    int bytesFallen = 1024;
    int gridRows = 71;
    int gridCols = 71;
    CharGrid grid(gridRows, std::vector<char>(gridCols, '.'));

    while (true)
    {
        for (int i = 0; i < bytesFallen; i++)
            grid[_bytes[i].y][_bytes[i].x] = '#';

        int steps = countMinSteps(grid, {0, 0}, {gridRows - 1, gridCols - 1});
        if (steps == -1)
            break;

        bytesFallen++;
    }

    Pos blockingByte = _bytes[bytesFallen - 1];
    std::cout << "part2: " << blockingByte.x << "," << blockingByte.y << "\n";
}
