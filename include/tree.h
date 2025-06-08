// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <algorithm>

struct Node {
    char val;
    std::vector<std::shared_ptr<Node>> next;
    explicit Node(char v) : val(v) {}
};
class PMTree {
 private:
    std::shared_ptr<Node> head;
    int total_perms;
    void makeBranches(std::shared_ptr<Node> parent,
                     std::vector<char> available) {
        if (available.empty()) return;
        for (size_t i = 0; i < available.size(); i++) {
            auto child = std::make_shared<Node>(available[i]);
            parent->next.push_back(child);
            std::vector<char> new_available;
            for (size_t j = 0; j < available.size(); j++) {
                if (j != i) new_available.push_back(available[j]);
            }
            makeBranches(child, new_available);
        }
    }
    static void walkTree(const std::shared_ptr<Node>& node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& output) {
        if (!node->next.empty()) {
            for (const auto& n : node->next) {
                current.push_back(n->val);
                walkTree(n, current, output);
                current.pop_back();
            }
        } else if (!current.empty()) {
            output.push_back(current);
        }
    }
    static int calcSubtreeSize(const std::shared_ptr<Node>& node) {
        if (node->next.empty()) return 1;
        int size = 0;
        for (const auto& n : node->next) {
            size += calcSubtreeSize(n);
        }
        return size;
    }
    static bool findPerm(const std::shared_ptr<Node>& node,
                        std::vector<char>& path,
                        std::vector<char>& result,
                        int& counter,
                        int target) {
        if (!node->next.empty()) {
            for (const auto& n : node->next) {
                path.push_back(n->val);
                int subtree_size = calcSubtreeSize(n);
                if (counter + subtree_size >= target) {
                    if (findPerm(n, path, result, counter, target)) {
                        return true;
                    }
                } else {
                    counter += subtree_size;
                }
                path.pop_back();
            }
        } else if (!path.empty()) {
            if (++counter == target) {
                result = path;
                return true;
            }
        }
        return false;
    }
public:
    explicit PMTree(const std::vector<char>& symbols)
        : head(std::make_shared<Node>('\0')), total_perms(0) {
        if (symbols.empty()) return;
        total_perms = 1;
        for (int i = 2; i <= static_cast<int>(symbols.size()); i++) {
            total_perms *= i;
        }
        std::vector<char> sorted = symbols;
        std::sort(sorted.begin(), sorted.end());
        makeBranches(head, sorted);
    }
    std::shared_ptr<Node> getRoot() const { return head; }
    int getPermCount() const { return total_perms; }
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
