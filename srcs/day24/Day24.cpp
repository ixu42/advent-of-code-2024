#include "Day24.hpp"

void Day24::printWires() const
{
    for (const auto& [key, value] : _wires)
        std::cout << key << ": " << value << "\n";
}

void Day24::printInstructions() const
{
    for (const auto& i : _instructions)
    {
        for (const auto& j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
}

void Day24::loadInstructions(const std::string& line)
{
    std::vector<std::string> instruction;
    std::string element;
    for (const auto& c : line)
    {
        if (c == ' ' && !element.empty())
        {
            instruction.push_back(element);
            element.clear();
        }
        else if (c == '-' || c == '>' || c == ' ')
            continue ;
        else
            element += c;
    }
    instruction.push_back(element);
    _instructions.push_back(instruction);
}

void Day24::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + filename);
    
    std::string line;
    bool wiresParsed = false;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            wiresParsed = true;
            continue ;
        }
        if (!wiresParsed)
        {
            std::string wire = line.substr(0, line.find(":"));
            std::string value = line.substr(line.find(":") + 2);
            _wires[wire] = std::stoi(value);
        }
        else
            loadInstructions(line);
    }
    // printWires();
    // printInstructions();
}

void Day24::processInstructions()
{
    std::vector<std::vector<std::string>> instructions = _instructions;
    while (!instructions.empty())
    {
        for (auto it = instructions.begin(); it != instructions.end(); )
        {
            std::string wireLeft = (*it)[0];
            std::string wireRight = (*it)[2];
            if (_wires.find(wireLeft) != _wires.end() 
                && _wires.find(wireRight) != _wires.end())
            {
                std::string op = (*it)[1];
                std::string res = (*it)[3];
                if (op == "AND")
                    _wires[res] = _wires[wireLeft] & _wires[wireRight];
                else if (op == "OR")
                    _wires[res] = _wires[wireLeft] | _wires[wireRight];
                else if (op == "XOR")
                    _wires[res] = _wires[wireLeft] ^ _wires[wireRight];
                it = instructions.erase(it);
            }
            else
                ++it;
        }
    }
    // printWires();
}

int64_t Day24::binaryToDecimal(const std::string& binary) const
{
    int64_t decimal = 0;
    int64_t base = 1;
    for (int i = binary.size() - 1; i >= 0; --i)
    {
        if (binary[i] == '1')
            decimal += base;
        base *= 2;
    }
    return decimal;
}

void Day24::solvePart1()
{
    processInstructions();

    std::map<std::string, int> zWires;
    for (const auto& [key, value] : _wires)
    {
        if (key.size() == 3 && key[0] == 'z')
        zWires[key] = value;
    }

    std::string binaryStr;
    std::map<std::string, int>::reverse_iterator it;
    for (it = zWires.rbegin(); it != zWires.rend(); ++it)
        binaryStr += std::to_string(it->second);

    std::cout << "part1: " << binaryToDecimal(binaryStr) << "\n";
}
