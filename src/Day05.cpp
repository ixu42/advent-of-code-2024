#include "../include/Day05.hpp"

void Day05::loadRules(const std::string& line)
{
    std::stringstream ss(line);
    int a, b;
    char separator;
    if (ss >> a >> separator >> b && separator == '|')
        _rules.emplace_back(a, b);
    else
        std::cerr << "Malformed line: " << line << "\n";
}

void Day05::loadUpdates(const std::string& line)
{
    std::stringstream ss(line);
    std::string nbr;
    std::vector<int> update;
    while (std::getline(ss, nbr, ','))
        update.push_back(std::stoi(nbr));
    _updates.push_back(update);
}

void Day05::printData()
{
    std::cout << "Rules:\n";
    for (const auto& rule : _rules)
        std::cout << rule.first << " " << rule.second << "\n";
    std::cout << "Updates:\n";
    for (const auto& update : _updates)
    {
        for (const auto& nbr : update)
            std::cout << nbr << " ";
        std::cout << "\n";
    }
}

void Day05::printUpdate(const std::vector<int>& update)
{
    for (int x : update)
        std::cout << x << " ";
    std::cout << "\n";
}

bool Day05::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    bool rulesLoaded = false;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << fileName << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            rulesLoaded = true;
        if (!rulesLoaded)
            loadRules(line);
        else
        {
            if (line.empty())
                continue ;
            loadUpdates(line);
        }
    }
    // printData();
    return true;
}

bool Day05::isInRightOrder(int left, int right)
{
    for (const auto& rule : _rules)
    {
        if ((left == rule.first && right == rule.second))
            return true;
    }
    return false;
}

void Day05::checkOrder(std::vector<int>& update, bool& correctlyOrdered)
{
    correctlyOrdered = true;
    for (size_t i = 0; i < update.size(); i++)
    {
        int left = update[i];
        for (size_t j = i + 1; j < update.size(); j++)
        {
            int right = update[j];
            if (!isInRightOrder(left, right))
            {
                correctlyOrdered = false;
                break ;
            }
        }
        if (!correctlyOrdered)
            break ;
    }
}

void Day05::solvePart1()
{
    bool correctlyOrdered;
    int middleNumber;
    for (auto& update : _updates)
    {
        checkOrder(update, correctlyOrdered);
        if (correctlyOrdered)
        {
            middleNumber = update[update.size() / 2];
            _resPart1 += middleNumber;
        }
    }
    std::cout << "part1: " << _resPart1 << "\n";
}

std::vector<int> Day05::topologicalSort(std::unordered_map<int, std::vector<int>>& graph, 
                                        std::unordered_map<int, int>& inDegree)
{
    std::queue<int> q;
    for (const auto& [page, degree] : inDegree)
    {
        if (degree == 0)
            q.push(page);
    }

    std::vector<int> sortedUpdate;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        sortedUpdate.push_back(current);

        for (int neighbor : graph[current])
        {
            if (--inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return sortedUpdate;
}

std::vector<int> Day05::reorderUpdate(std::vector<int>& update)
{
    // build graph for current update
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> inDegree;

    // initialize in-degree for all pages in update
    for (int page : update)
        inDegree[page] = 0;

    // add edges (how many numbers before the current) based on rules
    for (const auto& [from, to] : _rules)
    {
        if (inDegree.find(from) != inDegree.end() && inDegree.find(to) != inDegree.end())
        {
            graph[from].push_back(to);
            inDegree[to]++;
        }
    }

    std::vector<int> sortedUpdate = topologicalSort(graph, inDegree);
    
    return sortedUpdate;
}

void Day05::solvePart2()
{
    bool correctlyOrdered;
    std::vector<int> sortedUpdate;
    int middleNumber;
    for (auto& update : _updates)
    {
        checkOrder(update, correctlyOrdered);
        if (!correctlyOrdered)
        {
            // printUpdate(update);
            sortedUpdate = reorderUpdate(update);
            // std::cout << "=>";
            // printUpdate(sortedUpdate);
            middleNumber = sortedUpdate[sortedUpdate.size() / 2];
            _resPart2 += middleNumber;
        }
    }
    std::cout << "part2: " << _resPart2 << "\n";
}

int main()
{
    Day05 day05;
    if (!day05.loadData("input/day05.txt"))
        return 1;
    day05.solvePart1();
    day05.solvePart2();
}
