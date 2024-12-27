#include "Day07.hpp"

void Day07::printData()
{
    for (const auto& [testValue, nums] : _data)
    {
        std::cout << testValue << ": ";
        for (const auto num : nums)
            std::cout << num << " ";
        std::cout << "\n";
    }
}

bool Day07::loadData(const std::string& fileName)
{
    std::fstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << fileName << "\n";
        return false;
    }

    std::string line;
    std::vector<std::string> data;
    while (std::getline(file, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos)
        {
            std::cerr << "Invalid line: " << line << "\n";
            return false;
        }
        uint64_t testValue = std::stoll(line.substr(0, colonPos));

        std::string secondPart = line.substr(colonPos + 1);
        std::stringstream ss(secondPart);
        std::vector<uint64_t> nums;
        uint64_t num;
        while (ss >> num)
            nums.push_back(num); 
        _data.push_back(std::make_pair(testValue, nums));
    }
    return true;
}

int Day07::countDigits(uint64_t num)
{
    int counter = 0;
    while (true)
    {
        num /= 10;
        counter++;
        if (num == 0)
            break;
    }
    return counter;
}

bool Day07::evaluateExpression(const std::vector<uint64_t>& nums, 
                                const std::vector<char>& ops, 
                                uint64_t testValue)
{
    uint64_t res = nums[0];
    for (size_t i = 0; i < ops.size(); i++)
    {
        if (ops[i] == '+')
            res += nums[i + 1];
        else if (ops[i] == '*')
            res *= nums[i + 1];
        else if (ops[i] == 'c')
            res = res * pow(10, countDigits(nums[i + 1])) + nums[i + 1];
    }
    return res == testValue;
}

void Day07::generateOpsAndCheckValidity(const std::vector<uint64_t>& nums, 
                        const std::vector<char>& ops, 
                        std::vector<char>& currOps, size_t index, 
                        uint64_t testValue, bool& isValid)
{
    if (isValid)
        return ;
    if (index == nums.size() - 1)
    {
        if (evaluateExpression(nums, currOps, testValue))
            isValid = true;
        return ;
    }

    for (char op : ops)
    {
        currOps.push_back(op);
        generateOpsAndCheckValidity(nums, ops, currOps, index + 1, 
                                    testValue, isValid);
        currOps.pop_back();
    }
}

void Day07::solvePart1()
{
    std::vector<char> ops = {'+', '*'};
    std::vector<char> currOps;
    bool isValid;
    uint64_t res = 0;

    for (const auto& [testValue, nums] : _data)
    {
        isValid = false;
        generateOpsAndCheckValidity(nums, ops, currOps, 0, testValue, isValid);

        if (isValid)
            res += testValue;
    }
    std::cout << "part1: " << res << "\n";
}

void Day07::solvePart2()
{
    std::vector<char> ops = {'+', '*', 'c'}; // 'c' is for concatenation
    std::vector<char> currOps;
    bool isValid;
    uint64_t res = 0;

    for (const auto& [testValue, nums] : _data)
    {
        isValid = false;
        generateOpsAndCheckValidity(nums, ops, currOps, 0, testValue, isValid);

        if (isValid)
            res += testValue;
    }
    std::cout << "part2: " << res << "\n";
}
