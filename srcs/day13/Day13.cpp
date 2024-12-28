#include "Day13.hpp"

void Day13::loadClawMachine(const std::string& line, ClawMachine& clawMachine)
{
    char key;
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, token, ':');
    if (token == "Prize")
        key = 'P';
    else if (token[token.size() - 1] == 'A')
        key = 'A';
    else if (token[token.size() - 1] == 'B')
        key = 'B';
    else
        throw std::runtime_error("Invalid line: " + line);
    std::getline(ss, token);
    std::string part;
    std::stringstream tokenStream(token);
    std::getline(tokenStream, part, ',');
    int x = std::stoull(part.substr(3));
    std::getline(tokenStream, part);
    int y = std::stoull(part.substr(3));
    clawMachine[key] = {x, y};
}

void Day13::printData()
{
    for (const auto& clawMachine : _data)
    {
        for (const auto& [key, value] : clawMachine)
            std::cout << key << ": (" << value.first << ", " << value.second << ")\n";
        std::cout << '\n';
    }
}

void Day13::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filename);

    std::string line;
    ClawMachine clawMachine;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            _data.push_back(clawMachine);
            clawMachine.clear();
            continue;
        }
        loadClawMachine(line, clawMachine);
    }
    _data.push_back(clawMachine);
    // printData();
}

// brute force
void Day13::solvePart1()
{
    int res = 0;
    for (auto& machine : _data)
    {
        int ax = machine['A'].first, ay = machine['A'].second;
        int bx = machine['B'].first, by = machine['B'].second;
        int px = machine['P'].first, py = machine['P'].second;

        int cost = 0;
        bool intersect = false;
        for (int a = 0; a <= 100; ++a)
        {
            for (int b = 0; b <= 100; ++b)
            {
                if (a * ax + b * bx == px && a * ay + b * by == py)
                {
                    intersect = true;
                    cost = 3 * a + b;
                    res += cost;
                    break ;
                }
            }
            if (intersect)
                break ;
        }
    }
    std::cout << "part1: " << res << "\n";
}

// Cramer's rule
void Day13::solvePart2()
{
    int64_t res = 0;
    for (auto& machine : _data)
    {
        int64_t ax = machine['A'].first, ay = machine['A'].second;
        int64_t bx = machine['B'].first, by = machine['B'].second;
        int64_t px = machine['P'].first, py = machine['P'].second;
        px += 10000000000000, py += 10000000000000;
        int d = ax * by - ay * bx;
        if (d != 0)
        {
            if ((px * by - py * bx) % d == 0
                && (ax * py - ay * px) % d == 0)
            {
                int64_t a = (px * by - bx * py) / d;
                int64_t b = (ax * py - ay * px) / d;
                if (a >= 0 && b >= 0)
                    res += 3 * a + b;
            }
        }
    }
    std::cout << "part2: " << res << "\n";
}
