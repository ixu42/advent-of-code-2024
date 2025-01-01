#include "Day16.hpp"

void Day16::getStartAndEndPos()
{
    int counter = 0;
    for (int r = 0; r < _rowSize; ++r)
    {
        for (int c = 0; c < _colSize; ++c)
        {
            if (_map[r][c] == START)
            {
                _start.y = r;
                _start.x = c;
                counter++;
                if (counter == 2)
                    return;
            }
            else if (_map[r][c] == END)
            {
                _end.y = r;
                _end.x = c;
                counter++;
                if (counter == 2)
                    return;
            }
        }
    }
}

void Day16::drawMap(const CharGrid& map) const
{
    std::cout << "row size: " << _rowSize << "\n";
    std::cout << "col size: " << _colSize << "\n";
    std::cout << "start pos: " << _start.y << ", " << _start.x << "\n";
    std::cout << "end pos: " << _end.y << ", " << _end.x << "\n";
    for (const auto& row : map)
    {
        for (const char c : row)
            std::cout << c;
        std::cout << "\n";
    }
}

void Day16::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row;
        for (const auto& c : line)
            row.push_back(c);
        _map.push_back(row);
    }
    _rowSize = _map.size();
    _colSize = _map[0].size();
    getStartAndEndPos();
    // drawMap(_map);
}

// backtrack parent from child (end towards start) to draw path
void Day16::drawPath(CharGrid& map, int ey, int ex, int edir, 
                        const Tuple3DVec& parent)
{
    int y = ey, x = ex, dir = edir;

    while (true)
    {
        auto [py, px, pdir] = parent[y][x][dir];

        if (py == -1 && px == -1) break ;

        char symbol = ' ';
        if (pdir == 0 && symbol == ' ') symbol = '^';
        else if (pdir == 1 && symbol == ' ') symbol = '>';
        else if (pdir == 2 && symbol == ' ') symbol = 'v';
        else if (pdir == 3 && symbol == ' ') symbol = '<';
        if (map[y][x] != START && map[y][x] != END) map[y][x] = symbol;

        y = py;
        x = px;
        dir = pdir;
    }

    // drawMap(map);
}

// track a single best path and find minimum cost
int Day16::findMinScore(CharGrid& map)
{
    Int3DVec dist(_rowSize, Int2DVec(_colSize, IntVec(4, INF))); // store min cost
    Tuple3DVec parent(_rowSize, Tuple2DVec(_colSize, TupleVec(4, {-1, -1, -1})));
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    dist[_start.y][_start.x][1] = 0; // start facing east
    pq.push({_start.y, _start.x, 1, 0}); // y, x, direction, cost

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();

        int x = curr.x, y = curr.y, dir = curr.dir, cost = curr.cost;

        if (y == _end.y && x == _end.x)
        {
            drawPath(map, _end.y, _end.x, dir, parent);
            return cost;
        }

        // move forward
        int ny = y + DY[dir], nx = x + DX[dir];
        if (ny >= 0 && ny < _rowSize && nx >= 0 
            && nx < _colSize && map[ny][nx] != WALL)
        {
            if (cost + 1 < dist[ny][nx][dir])
            {
                dist[ny][nx][dir] = cost + 1;
                parent[ny][nx][dir] = std::make_tuple(y, x, dir);
                pq.push({ny, nx, dir, cost + 1});
            }
        }

        // rotate clockwise
        int newDir = (dir + 1) % 4;
        if (cost + 1000 < dist[y][x][newDir])
        {
            dist[y][x][newDir] = cost + 1000;
            parent[y][x][newDir] = std::make_tuple(y, x, dir);
            pq.push({y, x, newDir, cost + 1000});
        }

        // rotate counterclockwise
        newDir = (dir + 3) % 4;
        if (cost + 1000 < dist[y][x][newDir])
        {
            dist[y][x][newDir] = cost + 1000;
            parent[y][x][newDir] = std::make_tuple(y, x, dir);
            pq.push({y, x, newDir, cost + 1000});
        }
    }

    return INF; // if no path found
}

void Day16::solvePart1()
{
    CharGrid map = _map;
    int minScore = findMinScore(map);
    std::cout << "part1: "<< minScore << "\n";
}

// backtrack from end towards start to mark and count all valid tiles
// a tile is valid if it's on one of the best paths
int Day16::markPathsAndCountTiles(CharGrid& map, int ey, int ex, int edir,
                                    const Tuple4DVec& parent)
{
    std::queue<std::tuple<int, int, int>> stack;
    stack.push(std::make_tuple(ey, ex, edir));
    int tilesCount = 0;

    while (!stack.empty())
    {
        auto [y, x, dir] = stack.front();
        stack.pop();

        if (map[y][x] != 'O')
        {
            map[y][x] = 'O';
            tilesCount++;
        }

        for (const auto& p : parent[y][x][dir])
            stack.push(p);
    }
    // drawMap(map);
    return tilesCount;
}

// track all best paths and count all tiles on those paths
int Day16::countAllValidTiles(CharGrid& map)
{
    Int3DVec dist(_rowSize, Int2DVec(_colSize, IntVec(4, INF)));
    // for each child, store a vector of parents
    Tuple4DVec parent(_rowSize, Tuple3DVec(_colSize, Tuple2DVec(4)));
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    dist[_start.y][_start.x][1] = 0;
    pq.push({_start.y, _start.x, 1, 0});

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();

        int x = curr.x, y = curr.y, dir = curr.dir, cost = curr.cost;

        if (y == _end.y && x == _end.x)
            return markPathsAndCountTiles(map, _end.y, _end.x, dir, parent);

        int ny = y + DY[dir], nx = x + DX[dir];
        if (ny >= 0 && ny < _rowSize && nx >= 0 
            && nx < _colSize && map[ny][nx] != WALL)
        {
            if (cost + 1 < dist[ny][nx][dir])
            {
                dist[ny][nx][dir] = cost + 1;
                parent[ny][nx][dir].clear();
                parent[ny][nx][dir].push_back({y, x, dir});
                pq.push({ny, nx, dir, cost + 1});
            }
            else if (cost + 1 == dist[ny][nx][dir])
                parent[ny][nx][dir].push_back({y, x, dir});
        }

        int newDir = (dir + 1) % 4;
        if (cost + 1000 < dist[y][x][newDir])
        {
            dist[y][x][newDir] = cost + 1000;
            parent[y][x][newDir].clear();
            parent[y][x][newDir].push_back({y, x, dir});
            pq.push({y, x, newDir, cost + 1000});
        }
        else if (cost + 1000 == dist[y][x][newDir])
            parent[y][x][newDir].push_back({y, x, dir});

        newDir = (dir + 3) % 4;
        if (cost + 1000 < dist[y][x][newDir])
        {
            dist[y][x][newDir] = cost + 1000;
            parent[y][x][newDir].clear();
            parent[y][x][newDir].push_back({y, x, dir});
            pq.push({y, x, newDir, cost + 1000});
        }
        else if (cost + 1000 == dist[y][x][newDir])
            parent[y][x][newDir].push_back({y, x, dir});
    }

    return INF;
}

void Day16::solvePart2()
{
    CharGrid map = _map;
    int tilesCount = countAllValidTiles(map);
    std::cout << "part2: " << tilesCount << "\n";
}
