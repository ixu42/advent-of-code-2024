#include "include/Day03.hpp"

bool Day03::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
            _data += line;
    }
    else
    {
        std::cerr << "Unable to open file " << fileName << "\n";
        return false;
    }
    return true;
}

bool Day03::isValidNbr(const std::string& s)
{
    if (s.size() < 1 || s.size() > 3)
        return false;

    for (const auto& c : s)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}

bool Day03::isValid(const std::string& s)
{
    // check if there is exactly one comma in the string
    size_t pos = s.find(",");
    if (pos == std::string::npos || s.find(",", pos + 1) != std::string::npos)
        return false;

    std::stringstream ss(s);
    std::string word;
    while (!ss.eof())
    {
        getline(ss, word, ',');
        if (!isValidNbr(word))
            return false;
    }
    return true;
}

long long Day03::multiply(const std::string& s)
{
    std::stringstream ss(s);
    std::string word;
    long long res = 1;
    while (!ss.eof())
    {
        getline(ss, word, ',');
        res *= static_cast<long long>(std::stoi(word));
    }
    return res;
}

void Day03::solvePart1()
{
    size_t pos = _data.find("mul(");
    while (pos != std::string::npos)
    {
        size_t end = _data.find(")", pos);
        std::string sub = _data.substr(pos + 4, end - pos - 4);

        if (isValid(sub))
            _res += multiply(sub);

        pos = _data.find("mul(", pos + 1);
    }
    std::cout << "part1: " << _res << "\n";
}

bool Day03::enable_and_disable(size_t posDo, size_t posDont, 
                                size_t& posMul, size_t& prevPosMul)
{
    if ((posDo < posDont || posDo > posMul ) && posDont < posMul)
    {
        _enabled = false;
        prevPosMul = posMul;
        posMul = _data.find("mul(", posMul + 1);
        return false ;
    }
    else if ((posDont < posDo || posDont > posMul) && posDo < posMul)
        _enabled = true;
    return true;
}

void Day03::solvePart2()
{
    size_t posMul = _data.find("mul(");
    size_t prevPosMul = 0;
    size_t posDo;
    size_t posDont;
    long long _res = 0;

    while (posMul != std::string::npos)
    {
        size_t end = _data.find(")", posMul);
        std::string sub = _data.substr(posMul + 4, end - posMul - 4);
        posDo = _data.find("do()", prevPosMul + 1);
        posDont = _data.find("don't()", prevPosMul + 1);

        // check if there is do() or don't() before current mul()
        if (!enable_and_disable(posDo, posDont, posMul, prevPosMul))
            continue;

        // calculate the result if mul() is enabled and valid
        if (_enabled && isValid(sub))
            _res += multiply(sub);

        prevPosMul = posMul;
        posMul = _data.find("mul(", posMul + 1);
    }
    std::cout << "part2: " << _res << "\n";
}

int main()
{
    Day03 day03;
    if (!day03.loadData("input/Day03.txt"))
        return 1;
    day03.solvePart1();
    day03.solvePart2();
}
