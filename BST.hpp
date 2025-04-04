#ifndef BST_H
#define BST_H

#include <memory>
#include <unordered_map>
#include <queue>
#include "Experience.hpp"

struct BSTNode {
    Experience exp;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(const Experience &experience) : exp(experience), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    void insert(const Experience &experience);
    void update(int id, float newTdError);
    void inOrderTraversal() const;
    const Experience* getHighestPriority() const;
    BSTNode* getNode(int id);

    // New debug functions
    void printHashMap() const;
    void printQueue() const;

private:
    std::unique_ptr<BSTNode> root;
    std::unordered_map<int, BSTNode*> idToNodeMap;
    std::queue<int> insertionOrder;
    const size_t MAX_CAPACITY = 100;

    void insertHelper(std::unique_ptr<BSTNode>& node, const Experience &experience);
    void inOrderHelper(const BSTNode* node) const;
    std::unique_ptr<BSTNode> removeHelper(std::unique_ptr<BSTNode>& node, int id);
    BSTNode* findMin(std::unique_ptr<BSTNode>& node);
    void removeOldest();  
};

#endif
