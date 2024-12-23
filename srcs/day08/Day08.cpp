#include "../../include/Day08.hpp"

void Day08::printGrid(std::vector<std::vector<char>>& grid)
{
    for (const auto& row : grid)
    {
        for (const char c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

void Day08::printAntennas()
{
    for (const auto& antenna : _antennas)
    {
        std::cout << antenna.first << " -> ";

        std::cout << "[";
        for (const auto& pair : antenna.second)
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        std::cout << "]\n";
    }
}

void Day08::loadAntennas(const std::vector<std::string>& data)
{
    std::unordered_map<char, std::vector<std::pair<int, int>>> antenna;
    for (size_t r = 0; r < data.size(); r++)
    {
        for (size_t c = 0; c < data[r].size(); c++)
        {
            if (std::islower(data[r][c]) || std::isupper(data[r][c])
                || isdigit(data[r][c]))
            {
                if (_antennas.find(data[r][c]) == _antennas.end())
                    _antennas[data[r][c]] = std::vector<std::pair<int, int>>();
                _antennas[data[r][c]].push_back(std::make_pair(r, c));
            }
        }
    }
}

bool Day08::loadData(const std::string& filename)
{
    std::fstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(file, line))
    {
        data.push_back(line);
        std::vector<char> row;
        for (char c : line)
            row.push_back(c);
        _grid.push_back(row);
    }

    loadAntennas(data);
    return true;
}

void Day08::drawAntinode(const std::pair<int, int>& pos, 
                    std::vector<std::vector<char>>& grid)
{
    if (pos.first >= 0 
        && pos.first < static_cast<int>(grid.size()) 
        && pos.second >= 0 
        && pos.second < static_cast<int>(grid[pos.first].size())) 
        grid[pos.first][pos.second] = '#';
}

int Day08::calculateAntinode(const std::vector<std::vector<char>>& grid)
{
    int res = 0;
    for (const auto& row : grid)
    {
        for (const char c: row)
        {
            if (c == '#')
                res++;
        }
    }
    return res;
}

void Day08::solvePart1()
{
    std::vector<std::vector<char>> grid = _grid;
    for (const auto& antenna : _antennas)
    {
        for (size_t i = 0; i < antenna.second.size(); i++)
        {
            int x1 = antenna.second[i].first;
            int y1 = antenna.second[i].second;
            for (size_t j = i + 1; j < antenna.second.size(); j++)
            {
                int x2 = antenna.second[j].first;
                int y2 = antenna.second[j].second;
                int dx = x2 - x1;
                int dy = y2 - y1;
                int xForward = x2 + std::abs(dx);
                int yForward = y2 + dy;
                int xBackward = x1 - std::abs(dx);
                int yBackward = y1 - dy;
                drawAntinode({xForward, yForward}, grid);
                drawAntinode({xBackward, yBackward}, grid);
            }
        }
    }
    // printGrid(grid);
    std::cout << "part1: " << calculateAntinode(grid) << "\n";
}

void Day08::extendLine(int x, int y, int dx, int dy, 
                        std::set<std::pair<int, int>>& extendedPoints)
{
    int n = 1;
    while (true)
    {
        int xNew = x + n * dx;
        int yNew = y + n * dy;

        if (xNew < 0 || xNew >= static_cast<int>(_grid.size()) 
            || yNew < 0 || yNew >= static_cast<int>(_grid[0].size()))
            break;

        extendedPoints.insert({xNew, yNew});
        n++;
    }
}

void Day08::solvePart2()
{
    std::vector<std::vector<char>> grid = _grid;
    std::set<std::pair<int, int>> extendedPoints;
    for (const auto& antenna : _antennas)
    {
        for (size_t i = 0; i < antenna.second.size(); i++)
        {
            int x1 = antenna.second[i].first;
            int y1 = antenna.second[i].second;
            for (size_t j = i + 1; j < antenna.second.size(); j++)
            {
                int x2 = antenna.second[j].first;
                int y2 = antenna.second[j].second;
                int dx = x2 - x1;
                int dy = y2 - y1;

                extendLine(x1, y1, dx, dy, extendedPoints);
                extendLine(x2, y2, -dx, -dy, extendedPoints);
            }
        }
    }
    for (const auto& point : extendedPoints)
        drawAntinode(point, grid);
    // printGrid(grid);
    std::cout << "part2: " << calculateAntinode(grid) << "\n";
}
