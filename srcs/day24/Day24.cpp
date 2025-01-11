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
            std::string in0 = (*it)[0];
            std::string in1 = (*it)[2];
            if (_wires.find(in0) != _wires.end() 
                && _wires.find(in1) != _wires.end())
            {
                std::string op = (*it)[1];
                std::string out = (*it)[3];
                if (op == "AND")
                    _wires[out] = _wires[in0] & _wires[in1];
                else if (op == "OR")
                    _wires[out] = _wires[in0] | _wires[in1];
                else if (op == "XOR")
                    _wires[out] = _wires[in0] ^ _wires[in1];
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

std::string Day24::decimalToBinary(int64_t decimal) const
{
    std::string binary;
    while (decimal > 0)
    {
        binary = std::to_string(decimal % 2) + binary;
        decimal /= 2;
    }
    return binary;
}

// used in testing
void Day24::printCorrectBinaryForZ() const
{
    std::map<std::string, int> xWires;
    for (const auto& [key, value] : _wires)
    {
        if (key.size() == 3 && key[0] == 'x')
            xWires[key] = value;
    }

    std::string binaryStr1;
    for (auto it = xWires.rbegin(); it != xWires.rend(); ++it)
        binaryStr1 += std::to_string(it->second);

    std::map<std::string, int> yWires;
    for (const auto& [key, value] : _wires)
    {
        if (key.size() == 3 && key[0] == 'y')
            yWires[key] = value;
    }
    std::string binaryStr2;
    for (auto it = yWires.rbegin(); it != yWires.rend(); ++it)
        binaryStr2 += std::to_string(it->second);

    int64_t z = binaryToDecimal(binaryStr1) + binaryToDecimal(binaryStr2);
    std::cout << "Correct binary for z: " << "\n";

    std::string binaryStrZ = decimalToBinary(z);
    std::cout << binaryStrZ << "\n";
}

bool Day24::inputsWithXY(const std::string a, const std::string b) const
{
    return (a[0] == 'x' && b[0] == 'y') || (a[0] == 'y' && b[0] == 'x');
}

bool Day24::inputsEndIn00(const std::string a, const std::string b) const
{
    return a.substr(1) == "00" && b.substr(1) == "00";
}

/**
 * The rules as mentioned in 
 * https://www.reddit.com/r/adventofcode/comments/1hla5ql/2024_day_24_part_2_a_guide_on_the_idea_behind_the/
 * 
 * 1. If the output of a gate is z, then the operation has to be XOR unless it 
 * is the last bit.
 * 
 * 2. If the output of a gate is not z and the inputs are not x, y then it has 
 * to be AND / OR, but not XOR.
 * 
 * 3. If you have an XOR gate with inputs x, y, there must be another XOR gate 
 * with this gate as an input. Search through all gates for an XOR-gate with 
 * this gate as an input; if it does not exist, your (original) XOR gate is faulty.
 * 
 * 4. Similarly, if you have an AND-gate, there must be an OR-gate with this gate 
 * as an input. If that gate doesn't exist, the original AND gate is faulty.
 * 
 * 3 and 4 don't apply for the gates with inputs x00, y00.
 */

std::set<std::string> Day24::findFaultyWires() const
{
    std::set<std::string> faultyWires;
    for (const auto& instruction : _instructions)
    {
        std::string op = instruction[1];
        std::string out = instruction[3];
        std::string in0 = instruction[0];
        std::string in1 = instruction[2];
        if (out[0] == 'z' && out != "z45" && op != "XOR")
            faultyWires.insert(out);
        if (out[0] != 'z' && !inputsWithXY(in0, in1) && op == "XOR")
            faultyWires.insert(out);
        if (op == "XOR" && inputsWithXY(in0, in1) && !inputsEndIn00(in0, in1))
        {
            bool found = false;
            for (const auto& i : _instructions)
            {
                if (i[1] == "XOR" && (i[0] == out || i[2] == out))
                {
                    found = true;
                    break ;
                }
            }
            if (!found)
                faultyWires.insert(out);
        }
        if (op == "AND" && inputsWithXY(in0, in1) && !inputsEndIn00(in0, in1))
        {
            bool found = false;
            for (const auto& i : _instructions)
            {
                if (i[1] == "OR" && (i[0] == out || i[2] == out))
                {
                    found = true;
                    break ;
                }
            }
            if (!found)
                faultyWires.insert(out);
        }
    }
    return faultyWires;
}

void Day24::solvePart2()
{
    std::set<std::string> faultyWires = findFaultyWires();

    for (auto it = faultyWires.begin(); it != faultyWires.end(); ++it)
    {
        std::cout << *it;
        if (std::next(it) == faultyWires.end())
            std::cout << "\n";
        else
            std::cout << ",";
    }
}
