#include "Day19.hpp"

void Day19::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + filename);

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string pattern;
    while (std::getline(ss, pattern, ','))
    {
        if (!pattern.empty() && pattern[0] == ' ')
            pattern = pattern.substr(1);
        _availablePatterns.insert(pattern);
    }
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        _desiredDesigns.push_back(line);
    }
}

// dynamic programming approach
bool Day19::isPossible(const std::string& design)
{
    int n = static_cast<int>(design.size());
    std::vector<bool> dp(n + 1, false); // dp[i] = true if design[0:i] can be formed
    dp[0] = true; // empty design can always be formed

    // iterate over every prefix of design (design[0:i])
    for (int i = 1; i <= n; ++i)
    {
        // within current prefix, divide design[0:i] into two parts:
        // a potential smaller prefix design[0:j] and a substr design[j:i]
        for (int j = 0; j < i; ++j)
        {
            // check if substring from j to i is a valid pattern and prefix is valid
            if (dp[j] && _availablePatterns.count(design.substr(j, i - j)))
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

void Day19::solvePart1()
{
    int possibleCount = 0;

    for (const std::string& design : _desiredDesigns)
    {
        if (isPossible(design))
            ++possibleCount;
    }

    std::cout << "part1: " << possibleCount << "\n";
}

int64_t Day19::countPossibles(const std::string& design)
{
    int n = static_cast<int>(design.size());
    std::vector<int64_t> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (dp[j] && _availablePatterns.count(design.substr(j, i - j)))
                dp[i] += dp[j]; // keep track of the number of ways to form design[0:i]
        }
    }

    return dp[n];
}

void Day19::solvePart2()
{
    int64_t sumOfPossibleCount = 0;

    for (const std::string& design : _desiredDesigns)
    {
        if (isPossible(design))
            sumOfPossibleCount += countPossibles(design);
    }

    std::cout << "part2: " << sumOfPossibleCount << "\n";
}
