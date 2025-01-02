#include "Day17.hpp"

void Day17::loadData(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file " + fileName);

    std::string line;
    bool registersLoaded = false;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            registersLoaded = true;
            continue ;
        }
        if (!registersLoaded)
        {
            if (line.size() < 13 || (line[9] != 'A' && line[9] != 'B' && line[9] != 'C'))
                throw std::runtime_error("Invalid register line: " + line);
            char key = line[9];
            long value = std::stol(line.substr(12));
            _registers[key] = value;
        }
        else
        {
            std::string s = line.substr(9);
            std::stringstream ss(s);
            std::string token;
            while (std::getline(ss, token, ','))
                _program.push_back(std::stoi(token));
        }
    }
    if (_program.size() % 2 != 0)
        throw std::runtime_error("Invalid program size.");
}

long Day17::getComboOperand(int operand)
{
    long ret;

    if (operand >= 0 && operand <= 3)
        ret = operand;
    else if (operand == 4)
        ret = _registers['A'];
    else if (operand == 5)
        ret = _registers['B'];
    else if (operand == 6)
        ret = _registers['C'];
    else
        throw std::runtime_error("Invalid operand for adv: " + std::to_string(operand));

    return ret;
}

void Day17::adv(int operand)
{
    long numerator = _registers['A'];
    long comboOperand = getComboOperand(operand);
    long denominator = std::pow(2, comboOperand);

    _registers['A'] = numerator / denominator;
}

void Day17::bxl(int operand)
{
    _registers['B'] = _registers['B'] ^ operand;
}

void Day17::bst(int operand)
{
    long comboOperand = getComboOperand(operand);
    _registers['B'] = comboOperand % 8;
}

void Day17::jnz(int operand, int& i)
{
    if (_registers['A'] != 0)
        i = operand - 2;
}

void Day17::bxc(int operand)
{
    (void)operand;
    _registers['B'] = _registers['B'] ^ _registers['C'];
}

void Day17::out(int operand, bool& outCalled)
{
    long comboOperand = getComboOperand(operand);
    int comboOperandMod8 = comboOperand % 8;
    if (outCalled)
    {
        std::cout << comboOperandMod8;
        outCalled = false;
    }
    else
        std::cout << "," << comboOperandMod8;
    _output.push_back(comboOperandMod8);
}

void Day17::bdv(int operand)
{
    long numerator = _registers['A'];
    long comboOperand = getComboOperand(operand);
    long denominator = std::pow(2, comboOperand);

    _registers['B'] = numerator / denominator;
}

void Day17::cdv(int operand)
{
    long numerator = _registers['A'];
    long comboOperand = getComboOperand(operand);
    long denominator = std::pow(2, comboOperand);

    _registers['C'] = numerator / denominator;
}

void Day17::solvePart1()
{
    _output.clear();
    bool outCalled = true;
    for (int i = 0; i < static_cast<int>(_program.size()) - 1; i+=2)
    {
        switch (_program[i])
        {
            case 0:
                adv(_program[i + 1]);
                break;
            case 1:
                bxl(_program[i + 1]);
                break;
            case 2:
                bst(_program[i + 1]);
                break;
            case 3:
                jnz(_program[i + 1], i);
                break;
            case 4:
                bxc(_program[i + 1]);
                break;
            case 5:
                out(_program[i + 1], outCalled);
                break;
            case 6:
                bdv(_program[i + 1]);
                break;
            case 7:
                cdv(_program[i + 1]);
                break;
            default:
                throw std::runtime_error("Invalid opcode: " + std::to_string(_program[i]));
        }
    }
    if (!outCalled)
        std::cout << "\n";
}

// a general pattern is found after checking how changes in A impact output:
// for each digit in output indexed n, it changes after every 8^n iterations 
// (A increments by 1 in each iteration)
void Day17::solvePart2()
{
    long a = 1;
    while (true)
    {
        _registers['A'] = a;
        solvePart1();
        if (_output == _program)
            break ;
        if (_output.size() < _program.size())
        {
            a *= 2;
            continue ;
        }
        if (_output.size() == _program.size())
        {
            for (int i = _program.size() - 1; i >= 0; i--)
            {
                if (_output[i] != _program[i])
                {
                    a += std::pow(8, i);
                    break ;
                }
            }
        }
    }
    std::cout << "part2: " << a << "\n";
}
