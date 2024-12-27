#include "Day12.hpp"

void Day12::printGrid()
{
    std::cout << "Row: " << _rowSize << "\n";
    std::cout << "Col: " << _colSize << "\n";
    for (const auto& row : _grid)
    {
        for (char c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

bool Day12::loadGrid(const std::string& filename)
{
    std::fstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row;
        for (char c : line)
            row.push_back(c);
        _grid.push_back(row);
    }
    _rowSize = static_cast<int>(_grid.size());
    _colSize = static_cast<int>(_grid[0].size());
    // printGrid();
    return true;
}

bool Day12::withinBounds(int x, int y)
{
    return x >= 0 && x < _rowSize && y >= 0 && y < _colSize;
}

void Day12::bfs(Bool2DVec& visited, int startX, int startY, 
                int& area, int& perimeter)
{
    char plantType = _grid[startX][startY];
    std::queue<Point> q;
    q.push(Point(startX, startY));
    visited[startX][startY] = true;

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();
        area++;

        for (const auto& [dx, dy] : _directions)
        {
            int nx = p.first + dx;
            int ny = p.second + dy;

            if (!withinBounds(nx, ny))
                perimeter++;
            else if (_grid[nx][ny] != plantType)
                perimeter++;
            else if (_grid[nx][ny] == plantType && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                q.push(Point(nx, ny));
            }
        }
    }
}

void Day12::printRegion(int x, int y, int area, int perimeter)
{
    std::cout << "region: " << _grid[x][y] 
                << " area: " << area 
                << " perimeter/sides: " << perimeter << "\n";
}

void Day12::solvePart1()
{
    Bool2DVec visited(_rowSize, std::vector<bool>(_colSize, false));
    int totalPrice = 0;
    for (int i = 0; i < _rowSize; i++)
    {
        for (int j = 0; j < _colSize; j++)
        {
            if (!visited[i][j])
            {
                int area = 0, perimeter = 0;
                bfs(visited, i, j, area, perimeter);
                // printRegion(i, j, area, perimeter);
                totalPrice += area * perimeter;
            }
        }
    }
    std::cout << "part1: " << totalPrice << "\n";
}

void Day12::checkHorizontalBoundary(const Bool2DVec& currRegion, int nx, 
                                    int x, int y, int& sides)
{
    if (!withinBounds(nx, y))
    {
        if (y == 0)
            sides++;
        else if (!currRegion[x][y - 1])
            sides++;
    }
    else if (!currRegion[nx][y])
    {
        if (y == 0 ||!currRegion[x][y - 1])
            sides++;
        else if (currRegion[nx][y - 1])
            sides++;
    }
}

void Day12::checkVerticalBoundary(const Bool2DVec& currRegion, int ny, 
                                    int x, int y, int& sides)
{
    if (!withinBounds(x, ny))
    {
        if (x == 0)
            sides++;
        else if (!currRegion[x - 1][y])
            sides++;
    }
    else if (!currRegion[x][ny])
    {
        if (x == 0 || !currRegion[x - 1][y])
            sides++;
        else if (currRegion[x - 1][ny])
            sides++;
    }
}

void Day12::calculateSides(const Bool2DVec& currRegion, int& sides)
{
    // row-wise traversal
    for (int x = 0; x < _rowSize; x++)
    {
        for (int y = 0; y < _colSize; y++)
        {
            if (currRegion[x][y])
            {
                checkHorizontalBoundary(currRegion, x - 1, x, y, sides);
                checkHorizontalBoundary(currRegion, x + 1, x, y, sides);
            }
        }
    }

    // col-wise traversal
    for (int y = 0; y < _colSize; y++)
    {
        for (int x = 0; x < _rowSize; x++)
        {
            if (currRegion[x][y])
            {
                checkVerticalBoundary(currRegion, y - 1, x, y, sides);
                checkVerticalBoundary(currRegion, y + 1, x, y, sides);
            }
        }
    }
}

void Day12::bfsPart2(Bool2DVec& currRegion, Bool2DVec& visited, 
                        int startX, int startY, int& area)
{
    char plantType = _grid[startX][startY];
    std::queue<Point> q;
    q.push(Point(startX, startY));
    visited[startX][startY] = true;
    currRegion[startX][startY] = true;

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();
        area++;

        for (const auto& [dx, dy] : _directions)
        {
            int nx = p.first + dx;
            int ny = p.second + dy;

            if (!withinBounds(nx, ny))
                continue ;
            else if (_grid[nx][ny] == plantType && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                currRegion[nx][ny] = true;
                q.push(Point(nx, ny));
            }
        }
    }
}

void Day12::solvePart2()
{
    Bool2DVec visited(_rowSize, std::vector<bool>(_colSize, false));
    int totalPrice = 0;
    for (int i = 0; i < _rowSize; i++)
    {
        for (int j = 0; j < _colSize; j++)
        {
            if (!visited[i][j])
            {
                int area = 0, sides = 0;
                Bool2DVec currRegion(_rowSize, std::vector<bool>(_colSize, false));
                bfsPart2(currRegion, visited, i, j, area);
                calculateSides(currRegion, sides);
                // printRegion(i, j, area, sides);
                totalPrice += area * sides;
            }
        }
    }
    std::cout << "part2: " << totalPrice << "\n";
}
