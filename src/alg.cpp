// Copyright 2022 NNTU-CS
#include <vector>
#include "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    auto root = tree.getRoot();
    if (root && !root->next.empty()) {
        PMTree::walkTree(root, current, result);
    }
    return result;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num < 1 || num > tree.getPermCount()) return {};
    return getAllPerms(tree)[num - 1];
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> path, result;
    int counter = 0;
    auto root = tree.getRoot();
    if (root && num >= 1 && num <= tree.getPermCount()) {
        PMTree::findPerm(root, path, result, counter, num);
    }
    return result;
}
