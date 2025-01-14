#include "Day21.hpp"

void Day21::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + filename);
    
    std::string line;
    while (std::getline(file, line))
        _codes.push_back(line);
}

void Day21::getCharPos(const CharGrid& keypad, char num, int& y, int& x)
{
    int rows = keypad.size();
    int cols = keypad[0].size();
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (keypad[r][c] == num)
            {
                y = r;
                x = c;
                return ;
            }
        }
    }
    throw std::runtime_error("Invalid number " + num);
}

bool Day21::isValid(const CharGrid& keypad, int y, int x)
{
    int rows = keypad.size();
    int cols = keypad[0].size();
    if (y < 0 || y >= rows || x < 0 || x >= cols)
        return false;
    return keypad[y][x] != '#';
}

std::vector<std::string> Day21::bfs(const CharGrid& keypad, char start, char target)
{
    int startY = 0, startX = 0;
    getCharPos(keypad, start, startY, startX);

    std::queue<Pos> q;
    std::queue<std::string> sequences;
    q.push({startY, startX});
    sequences.push("");

    std::map<Pos, int> visited;
    visited[{startY, startX}] = 0;

    std::vector<std::string> result;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();
        std::string seq = sequences.front();
        sequences.pop();

        if (keypad[y][x] == target)
        {
            std::string completeSeq = seq + 'A';
            if (result.empty() || (completeSeq.length() == result[0].length()))
                result.push_back(completeSeq);
            else
                break ; // stop once all shortest paths are processed
        }

        for (int i = 0; i < 4; ++i)
        {
            int ny = y + MOVES[i].y;
            int nx = x + MOVES[i].x;

            if (isValid(keypad, ny, nx))
            {
                Pos nextPos = {ny, nx};
                int newDist = seq.length() + 1;
                if (visited.find(nextPos) == visited.end() || newDist <= visited[nextPos])
                {
                    visited[nextPos] = newDist;
                    q.push({ny, nx});
                    std::string nextMove = seq + (i == 0 ? "^" : i == 1 ? "v" : i == 2 ? "<" : ">");
                    sequences.push(nextMove);
                }
            }
        }
    }
    return result;
}

std::vector<std::string> Day21::getSeqForNumPad(const std::string& code)
{
    std::vector<std::string> seq;
    char start = 'A';
    for (char c : code)
    {
        std::vector<std::string> toAppend = bfs(NUMPAD, start, c);
        if (seq.empty())
            seq = toAppend;
        else
        {
            std::vector<std::string> seqTemp;
            for (const auto& s : toAppend)
            {
                for (const auto& s1 : seq)
                    seqTemp.push_back(s1 + s);
            }
            seq = std::move(seqTemp);
        }
        start = c;
    }
    return seq;
}

std::vector<std::string> Day21::getSeqForDirPad(const std::vector<std::string>& curSequences)
{
    std::vector<std::string> nextSequences;
    for (const auto& curseq : curSequences)
    {
        std::vector<std::string> seq;
        char start = 'A';
        bool seqTooLong = false;
        for (char c : curseq)
        {
            std::vector<std::string> toAppend = bfs(DIRPAD, start, c);
            if (seq.empty())
                seq = toAppend;
            else
            {
                std::vector<std::string> SeqTemp;
                for (const auto& s : toAppend)
                {
                    for (const auto& s2 : seq)
                    {
                        if (!nextSequences.empty() 
                            && (s2.length() + s.length() > nextSequences[0].length()))
                            {
                                seqTooLong = true;
                                break ;
                            }
                        SeqTemp.push_back(s2 + s);
                    }
                    if (seqTooLong)
                        break ;
                }
                if (seqTooLong)
                    break ;
                seq = std::move(SeqTemp);
            }
            start = c;
        }
        if (seqTooLong)
            continue ;
        if (nextSequences.empty() || seq[0].length() < nextSequences[0].length())
            nextSequences = std::move(seq);
        else if (seq[0].length() == nextSequences[0].length())
        {
            for (const auto& s : seq)
                nextSequences.push_back(s);
        }
    }
    return nextSequences;
}

void Day21::solvePart1()
{
    int totalComplexity = 0;
    for (const auto& code : _codes)
    {
        std::vector<std::string> seq = getSeqForNumPad(code);
        std::vector<std::string> nextSeq = getSeqForDirPad(seq);
        nextSeq = getSeqForDirPad(nextSeq);
        int numericPart = stoi(code);
        totalComplexity += numericPart * nextSeq[0].size();
    }
    std::cout << "part1: " << totalComplexity << "\n";
}

int64_t Day21::getCost(char a, char b, const CharGrid& keypad, int depth)
{
    static std::map<std::tuple<char, char, int>, int64_t> cache;
    auto cacheKey = std::make_tuple(a, b, depth);

    if (cache.find(cacheKey) != cache.end())
        return cache[cacheKey];

    if (depth == 0) // reaching the bot controlled by human
    {
        std::vector<std::string> sequences = bfs(DIRPAD, a, b);
        int64_t minCost = std::numeric_limits<int64_t>::max();
        for (const auto& seq : sequences)
            minCost = std::min(minCost, static_cast<int64_t>(seq.size()));
        cache[cacheKey] = minCost;
        return minCost;
    }

    std::vector<std::string> sequences = bfs(keypad, a, b);
    int64_t minCost = std::numeric_limits<int64_t>::max();
    for (const auto& s : sequences)
    {
        std::string seq = 'A' + s;
        int64_t cost = 0;
        for (int64_t i = 0; i < static_cast<int64_t>(seq.size()) - 1; ++i)
        {
            char a1 = seq[i];
            char b1 = seq[i + 1];
            cost += getCost(a1, b1, DIRPAD, depth - 1);
        }
        minCost = std::min(minCost, cost);
    }

    cache[cacheKey] = minCost;
    return minCost;
}

int64_t Day21::getCodeCost(const std::string& code, int depth)
{
    int64_t cost = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(code.size()) - 1; ++i)
    {
        char a = code[i];
        char b = code[i + 1];
        cost += getCost(a, b, NUMPAD, depth);
    }
    return cost;
}

void Day21::solvePart2()
{
    int64_t totalComplexity = 0;
    for (const auto& code : _codes)
    {
        int64_t numericPart = stoi(code);
        int64_t cost = getCodeCost("A" + code, 25);
        totalComplexity += numericPart * cost;
    }
    std::cout << "part2: " << totalComplexity << "\n";
}
