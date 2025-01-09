#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

class Day22
{
    public:
        void loadData(const std::string& fileName);
        void solvePart1();
        void solvePart2();

    private:
        std::vector<int64_t> _initialNums;

        struct BananaPrice
        {
            int price;
            int change;
            BananaPrice(int p, int c) : price(p), change(c) {}
        };

        using PriceVec = std::vector<BananaPrice>;

        int64_t mix(int64_t value, int64_t secretNum);
        int64_t prune(int64_t secretNum);
        int64_t getNext(int64_t num);
        std::vector<PriceVec> getAllPrices();
        bool isUniqueSeq(const std::vector<int>& sequence, 
                            const std::vector<std::vector<int>>& sequences);
};
