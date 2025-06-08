// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) : permutation_length(elements.size()) {
    if (elements.empty()) {
        root = nullptr;
        return;
    }
    root = std::make_unique<Node>('\0');
    buildTree(root.get(), elements);
}
void PMTree::buildTree(Node* parent, const std::vector<char>& elements) {
    if (elements.empty()) {
        return;
    }
    for (size_t i = 0; i < elements.size(); ++i) {
        parent->children.emplace_back(std::make_unique<Node>(elements[i]));
        std::vector<char> remaining_elements;
        for (size_t j = 0; j < elements.size(); ++j) {
            if (j != i) {
                remaining_elements.push_back(elements[j]);
            }
        }
        buildTree(parent->children.back().get(), remaining_elements);
    }
}
std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (!root) return result;
    std::vector<char> current;
    for (const auto& child : root->children) {
        traverseTree(child.get(), current, result);
    }
    return result;
}
void PMTree::traverseTree(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) const {
    current.push_back(node->value);
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            traverseTree(child.get(), current, result);
        }
    }
    current.pop_back();
}
std::vector<char> PMTree::getPerm1(int num) const {
    if (num < 1 || num > getPermutationCount()) {
        return {};
    }
    std::vector<char> result;
    std::vector<char> current;
    int counter = 0;
    for (const auto& child : root->children) {
        getPermByTraversal(child.get(), current, counter, num, result);
        if (!result.empty()) {
            break;
        }
    }
    return result;
}
void PMTree::getPermByTraversal(Node* node, std::vector<char>& current, int& counter, int target, std::vector<char>& result) const {
    current.push_back(node->value);
    
    if (node->children.empty()) {
        counter++;
        if (counter == target) {
            result = current;
        }
    } else {
        for (const auto& child : node->children) {
            if (result.empty()) {
                getPermByTraversal(child.get(), current, counter, target, result);
            } else {
                break;
            }
        }
    }
    current.pop_back();
}
std::vector<char> PMTree::getPerm2(int num) const {
    if (num < 1 || num > getPermutationCount()) {
        return {};
    }
    std::vector<char> result;
    std::vector<char> current;
    int remaining = num - 1; // Нумерация с 1
    for (const auto& child : root->children) {
        if (result.empty()) {
            getPermByNavigation(child.get(), current, target, result, remaining);
        } else {
            break;
        }
    }
    return result;
}
void PMTree::getPermByNavigation(Node* node, std::vector<char>& current, int target, std::vector<char>& result, int& remaining) const {
    current.push_back(node->value);
    
    if (node->children.empty()) {
        if (remaining == 0) {
            result = current;
        }
        remaining--;
    } else {
        for (const auto& child : node->children) {
            if (result.empty()) {
                int subtree_size = factorial(node->children.size() - 1);
                if (remaining >= subtree_size) {
                    remaining -= subtree_size;
                } else {
                    getPermByNavigation(child.get(), current, target, result, remaining);
                    break;
                }
            } else {
                break;
            }
        }
    }
    current.pop_back();
}
int PMTree::factorial(int n) const {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
size_t PMTree::getPermutationCount() const {
    if (!root) return 0;
    return factorial(permutation_length);
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPerm1(num);
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPerm2(num);
}
