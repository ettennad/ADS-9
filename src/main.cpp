// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>
#include "tree.h"

void printPermutations(const std::vector<char>& elements) {
    PMTree tree(elements);
    auto perms = getAllPerms(tree);
    std::cout << "All permutations for [";
    for (char c : elements) {
        std::cout << c << " ";
    }
    std::cout << "]:\n";
    for (const auto& perm : perms) {
        for (char c : perm) {
            std::cout << c;
        }
        std::cout << " ";
    }
    std::cout << "\n\n";
}
void testPermutations() {
    std::vector<char> test1 = {'1', '2', '3'};
    printPermutations(test1);
    std::vector<char> test2 = {'a', 'b'};
    printPermutations(test2);
    PMTree tree(test1);
    for (int i = 1; i <= 6; ++i) {
        auto perm1 = getPerm1(tree, i);
        auto perm2 = getPerm2(tree, i);
        std::cout << "Permutation #" << i << ":\n";
        std::cout << "getPerm1: ";
        for (char c : perm1) std::cout << c;
        std::cout << "\n";
        std::cout << "getPerm2: ";
        for (char c : perm2) std::cout << c;
        std::cout << "\n\n";
    }
}
void runExperiment() {
    std::ofstream dataFile("experiment_data.csv");
    dataFile << "n,getAllPerms,getPerm1,getPerm2\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int n = 1; n <= 10; ++n) {
        // Создаем вектор символов от '1' до 'n'
        std::vector<char> elements(n);
        for (int i = 0; i < n; ++i) {
            elements[i] = '1' + i;
        }
        PMTree tree(elements);
        int totalPerms = tree.getPermutationCount();
        std::uniform_int_distribution<> distr(1, totalPerms);
        int randomPermNum = distr(gen);
        auto start = std::chrono::high_resolution_clock::now();
        auto allPerms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        auto allPermsTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        auto perm1 = getPerm1(tree, randomPermNum);
        end = std::chrono::high_resolution_clock::now();
        auto perm1Time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        auto perm2 = getPerm2(tree, randomPermNum);
        end = std::chrono::high_resolution_clock::now();
        auto perm2Time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        dataFile << n << "," << allPermsTime << "," << perm1Time << "," << perm2Time << "\n";
        std::cout << "n = " << n << ": " 
                  << "getAllPerms = " << allPermsTime << " μs, "
                  << "getPerm1 = " << perm1Time << " μs, "
                  << "getPerm2 = " << perm2Time << " μs\n";
    }
    dataFile.close();
    std::cout << "Experiment data saved to experiment_data.csv\n";
}
int main() {
    std::cout << "=== Testing permutation generation ===\n";
    testPermutations();
    std::cout << "=== Running performance experiment ===\n";
    runExperiment();
    return 0;
}
