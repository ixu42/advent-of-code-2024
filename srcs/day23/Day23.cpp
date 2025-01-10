#include "Day23.hpp"

void Day23::printGraph()
{
    for (const auto& [key, value] : _graph)
    {
        std::cout << key << ": ";
        for (const auto& v : value)
        {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    std::cout << "graph size: " << _graph.size() << "\n";
}

void Day23::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + filename);
    
    std::string line;
    std::vector<std::pair<std::string, std::string>> connections;
    while (std::getline(file, line))
    {
        size_t pos = line.find("-");
        connections.push_back({line.substr(0, pos), line.substr(pos + 1)});
    }

    for (const auto& connection : connections)
    {
        _graph[connection.first].insert(connection.second);
        _graph[connection.second].insert(connection.first);
    }

    // printGraph();
}

std::set<std::set<std::string>> Day23::findTriangles()
{
    std::set<std::set<std::string>> groups;

    for (const auto& [current, neighbors] : _graph)
    {
        for (const auto& n : neighbors)
        {
            if (_graph.find(n) != _graph.end())
            {
                for (const auto& nn : _graph[n])
                {
                    if (_graph[current].find(nn) != _graph[current].end())
                        groups.insert({current, n, nn});
                }
            }
        }
    }

    return groups;
}

void Day23::solvePart1()
{
    std::set<std::set<std::string>> groups = findTriangles();

    int count = 0;
    for (const auto& group : groups)
    {
        for (const auto& g : group)
        {
            if (g.size() > 0 && g[0] == 't')
            {
                count++;
                break ;
            }
        }
    }
    std::cout << "part1: " << count << "\n";
}

// Bron-Kerbosch algorithm
// R: current clique
// P: potential candidates for the clique
// X: nodes already processed and not included in the clique
// for each v in P, a recursive depth-first search is performed to
// explore the maximal cliques that include v
void Day23::bronKerbosch(std::unordered_set<std::string>& R, 
                            std::unordered_set<std::string>& P, 
                            std::unordered_set<std::string>& X, 
                            std::vector<std::unordered_set<std::string> >& cliques)
{
    if (P.empty() && X.empty())
    {
        cliques.push_back(R);
        return ;
    }

    while (!P.empty())
    {
        std::string v = *P.begin();
        std::unordered_set<std::string> newR = R;
        newR.insert(v);

        std::unordered_set<std::string> newP;
        for (const auto& p : P)
        {
            if (_graph[v].find(p) != _graph[v].end())
                newP.insert(p);
        }

        std::unordered_set<std::string> newX;
        for (const auto& x : X)
        {
            if (_graph[v].find(x) != _graph[v].end())
                newX.insert(x);
        }

        bronKerbosch(newR, newP, newX, cliques);

        P.erase(v);
        X.insert(v);
    }
}

void Day23::solvePart2()
{
    std::unordered_set<std::string> R, P, X;
    for (const auto&node : _graph)
        P.insert(node.first);

    std::vector<std::unordered_set<std::string>> allCliques;
    bronKerbosch(R, P, X, allCliques);

    int maxCliqueSize = 0;
    std::unordered_set<std::string> maxClique;
    for (const auto& clique : allCliques)
    {
        if (static_cast<int>(clique.size()) > maxCliqueSize)
        {
            maxCliqueSize = clique.size();
            maxClique = clique;
        }
    }

    std::vector<std::string> result(maxClique.begin(), maxClique.end());
    std::sort(result.begin(), result.end());

    std::string password = "";
    for (size_t i = 0; i < result.size(); ++i)
    {
        password += result[i];
        if (i < result.size() - 1)
            password += ",";
    }
    std::cout << "part2: " << password << "\n";
}
