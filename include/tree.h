// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
private:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        Node(char val) : value(val) {}
    };
    std::unique_ptr<Node> root;
    size_t permutation_length;
    void buildTree(Node* parent, const std::vector<char>& elements);
    void traverseTree(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) const;
    void getPermByTraversal(Node* node, std::vector<char>& current, int& counter, int target, std::vector<char>& result) const;
    void getPermByNavigation(Node* node, std::vector<char>& current, int target, std::vector<char>& result, int& remaining) const;
    int factorial(int n) const;

public:
    explicit PMTree(const std::vector<char>& elements);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;
    size_t getPermutationCount() const;
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
