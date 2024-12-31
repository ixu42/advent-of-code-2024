#include "Day14.hpp"

void Day14::printBots()
{
    for (const auto& bot : _bots)
    {
        std::cout << "pos=<" << bot.px << "," << bot.py << ">, vel=<" 
                    << bot.vx << "," << bot.vy << ">\n";
    }
}

void Day14::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    while (std::getline(file, line))
    {
        Bot bot;
        std::regex pattern(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
        std::smatch matches;

        if (std::regex_match(line, matches, pattern))
        {
            bot.px = std::stoi(matches[1]);
            bot.py = std::stoi(matches[2]);
            bot.vx = std::stoi(matches[3]);
            bot.vy = std::stoi(matches[4]);
        }
        else
            throw std::runtime_error("Invalid line format: " + line);

        _bots.push_back(bot);
    }
    // printBots();
}

void Day14::drawBotsOnGrid(int px, int py, int nx, int ny, 
                            int xMax, int yMax, IntGrid& grid)
{
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            if (x == px && y == py)
                grid[y][x]--;
            if (x == nx && y == ny)
                grid[y][x]++;
        }
    }
}

void Day14::printGrid(int xMax, int yMax, IntGrid& grid)
{
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            if (grid[y][x] == 0)
                std::cout << ".";
            else
                std::cout << grid[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Day14::calculateResPart1(int xMax, int yMax, IntGrid& grid)
{
    int quadrants[4] = {0, 0, 0, 0};

    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            bool found = false;
            for (const auto& bot : _bots)
            {
                if (bot.px == x && bot.py == y)
                {
                    found = true;
                    break ;
                }
            }
            if (found)
            {
                if (x < xMax / 2 && y < yMax / 2)
                    quadrants[0] += grid[y][x];
                else if (x > xMax / 2 && y < yMax / 2)
                    quadrants[1] += grid[y][x];
                else if (x < xMax / 2 && y > yMax / 2)
                    quadrants[2] += grid[y][x];
                else if (x > xMax / 2 && y > yMax / 2)
                    quadrants[3] += grid[y][x];
            }
        }
    }
    return quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
}

void Day14::solvePart1()
{
    int xMax = 101; // col
    int yMax = 103; // row
    IntGrid grid = IntGrid(yMax, std::vector<int>(xMax, 0));
    for (const auto& bot : _bots)
        grid[bot.py][bot.px]++;

    for (int t = 1; t <= 100; t++)
    {
        for (auto& bot : _bots)
        {
            int nx = (bot.px + bot.vx) % xMax;
            nx = nx < 0 ? nx + xMax : nx;
            int ny = (bot.py + bot.vy) % yMax;
            ny = ny < 0 ? ny + yMax : ny;
            drawBotsOnGrid(bot.px, bot.py, nx, ny, xMax, yMax, grid);
            // printGrid(xMax, yMax, grid);
            bot.px = nx;
            bot.py = ny;
        }
    }

    int res = calculateResPart1(xMax, yMax, grid);
    std::cout << "part1: " << res << "\n";
}

void Day14::initStartPos(int xMax, int yMax, IntGrid& grid, 
                            BoolGrid& visited, std::queue<Point>& q)
{
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            if (grid[y][x] == 0)
            {
                visited[y][x] = true;
                q.push({x, y});
                break ;
            }
        }
    }
}

bool Day14::checkTree(int xMax, int yMax, IntGrid& grid, BoolGrid& visited)
{
    int unvisited = 0;
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            if (grid[y][x] == 0 && !visited[y][x])
            {
                unvisited++;
                if (unvisited > 42)
                {   
                    printGrid(xMax, yMax, grid);
                    return true;
                }
            }
        }
    }
    return false;
}

// flood fill to check if bots form a christmas tree
bool Day14::botsFormChristmasTree(int xMax, int yMax, IntGrid& grid)
{
    IntGrid gridCopy = grid;
    std::queue<Point> q;
    BoolGrid visited(yMax, std::vector<bool>(xMax, false));
    std::vector<Point> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    initStartPos(xMax, yMax, gridCopy, visited, q);

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();

        for (const auto& [dx, dy] : directions)
        {
            int nx = p.first + dx;
            int ny = p.second + dy;

            if (nx < 0 || nx >= xMax || ny < 0 || ny >= yMax)
                continue ;
            else if (gridCopy[ny][nx] == 0 && !visited[ny][nx])
            {
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    return checkTree(xMax, yMax, gridCopy, visited);
}

void Day14::solvePart2()
{
    int xMax = 101;
    int yMax = 103;
    IntGrid grid = IntGrid(yMax, std::vector<int>(xMax, 0));
    for (const auto& bot : _bots)
        grid[bot.py][bot.px]++;

    for (int t = 1; t <= 10000000; t++)
    {
        for (auto& bot : _bots)
        {
            int nx = (bot.px + bot.vx) % xMax;
            nx = nx < 0 ? nx + xMax : nx;
            int ny = (bot.py + bot.vy) % yMax;
            ny = ny < 0 ? ny + yMax : ny;
            drawBotsOnGrid(bot.px, bot.py, nx, ny, xMax, yMax, grid);
            bot.px = nx;
            bot.py = ny;
        }
        std::cout << "checking t: " << t << "\n";
        if (botsFormChristmasTree(xMax, yMax, grid))
        {
            std::cout << "part2: " << t << "\n";
            break ;
        }
    }
}
