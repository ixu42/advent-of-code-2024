#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int calculate_dist(std::vector<int>& first, std::vector<int>& second)
{
    int sum_of_diff = 0;
    for (unsigned int i = 0; i < first.size(); i++)
    {
        int current_diff = std::abs(first[i] - second[i]);
        sum_of_diff += current_diff;
    }
    return sum_of_diff;
}

int calculate_similarity_score(std::vector<int>& first, std::vector<int>& second)
{
    int num;
    int similarity_score;
    for (unsigned int i = 0; i < first.size(); i++)
    {
        num = first[i];
        int counter = 0;
        for (unsigned int j = 0; j < second.size(); j++)
        {
            if (num == second[j])
                counter++;
        }
        similarity_score += num * counter;
    }
    return similarity_score;
}

int main()
{
    // load data into 2 vectors
    std::ifstream file("input/day01.txt");
    std::vector<int> first_colume;
    std::vector<int> second_colume;
    int num;
    while (file >> num)
    {
        first_colume.push_back(num);
        file >> num;
        second_colume.push_back(num);
    }

    // sort both vectors in ascending order
    std::sort(first_colume.begin(), first_colume.end());
    std::sort(second_colume.begin(), second_colume.end());

    // PART 1
    int sum_of_diff = calculate_dist(first_colume, second_colume);
    std::cout << "sum_of_diff: " << sum_of_diff << "\n";

    // PART 2
    int similarity_score = calculate_similarity_score(first_colume, second_colume);
    std::cout << "similarity_score: " << similarity_score << "\n";
}
