// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

using namespace std::chrono;
uint16_t measureGetAll(PMTree& tree) {
    auto start = high_resolution_clock::now();
    getAllPerms(tree);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}
uint16_t measureGet1(PMTree& tree, int num) {
    auto start = high_resolution_clock::now();
    getPerm1(tree, num);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}
uint16_t measureGet2(PMTree& tree, int num) {
    auto start = high_resolution_clock::now();
    getPerm2(tree, num);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int n = 1; n <= 10; n++) {
        std::vector<char> symbols(n);
        for (int i = 0; i < n; i++) {
            symbols[i] = '1' + i;
        }
        PMTree tree(symbols);
        int total = tree.getPermCount();
        std::uniform_int_distribution<int> dist(1, total);
        int rand_num = dist(gen);
        uint16_t t_all = measureGetAll(tree);
        uint16_t t_get1 = measureGet1(tree, rand_num);
        uint16_t t_get2 = measureGet2(tree, rand_num);
        std::cout << n << "\t" 
                  << t_all << "\t"
                  << t_get1 << "\t" 
                  << t_get2 << "\n";
    }
    return 0;
}
