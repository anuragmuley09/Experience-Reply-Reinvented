#include "BST.hpp"
#include "Logger.hpp"
#include <stdexcept>
#include <unordered_map>

BST::BST() : root(nullptr) {}

void BST::insert(const Experience &experience) {
    // Evict if capacity is full
    if (insertionOrder.size() >= MAX_CAPACITY) {
        removeOldest();  // Eviction logic
    }

    insertHelper(root, experience);
    idToNodeMap[experience.id] = root.get();
    insertionOrder.push(experience.id);  //     Track insertion order
}

void BST::insertHelper(std::unique_ptr<BSTNode>& node, const Experience &experience) {
    if (!node) {
        node = std::make_unique<BSTNode>(experience);
        idToNodeMap[experience.id] = node.get();
        Logger::log("Inserted experience id " + std::to_string(experience.id) +
                    " with TD error " + std::to_string(experience.tdError));
        return;
    }
    if (experience.tdError < node->exp.tdError) {
        insertHelper(node->left, experience);
    } else {
        insertHelper(node->right, experience);
    }
}

BSTNode* BST::getNode(int id) {
    return idToNodeMap.count(id) ? idToNodeMap[id] : nullptr;
}

void BST::update(int id, float newTdError) {
    BSTNode* node = getNode(id);
    if (!node) {
        Logger::log("Update failed: Experience id " + std::to_string(id) + " not found.");
        return;
    }

    if (node->exp.tdError == newTdError) {
        Logger::log("Update skipped: TD error remains the same.");
        return;
    }

    Logger::log("Updating experience id " + std::to_string(id) +
                " from TD error " + std::to_string(node->exp.tdError) +
                " to " + std::to_string(newTdError));

    removeHelper(root, id);
    idToNodeMap.erase(id);

    Experience updatedExp = node->exp;
    updatedExp.tdError = newTdError;
    insert(updatedExp);
}

BSTNode* BST::findMin(std::unique_ptr<BSTNode>& node) {
    if (!node) return nullptr;
    if (!node->left) return node.get();
    return findMin(node->left);
}

std::unique_ptr<BSTNode> BST::removeHelper(std::unique_ptr<BSTNode>& node, int id) {
    if (!node) return nullptr;

    if (id < node->exp.id) {
        node->left = removeHelper(node->left, id);
    } else if (id > node->exp.id) {
        node->right = removeHelper(node->right, id);
    } else {
        if (!node->left) return std::move(node->right);
        if (!node->right) return std::move(node->left);

        BSTNode* minNode = findMin(node->right);
        node->exp = minNode->exp;
        node->right = removeHelper(node->right, minNode->exp.id);
    }
    return std::move(node);
}

/**
 * const:
 * these functions do not modify the internal state of the object 
 * — i.e., they don’t change any member variables of the class.
 */
void BST::inOrderTraversal() const {
    Logger::log("BST In-Order Traversal Start");
    inOrderHelper(root.get());
    Logger::log("BST In-Order Traversal End");
}

void BST::inOrderHelper(const BSTNode* node) const {
    if (!node) return;
    inOrderHelper(node->left.get());
    Logger::log("Experience id: " + std::to_string(node->exp.id) +
                ", TD error: " + std::to_string(node->exp.tdError));
    inOrderHelper(node->right.get());
}

const Experience* BST::getHighestPriority() const {
    if (!root) return nullptr;
    const BSTNode* current = root.get();
    while (current->right) {
        current = current->right.get();
    }
    return &current->exp;
}

// FIFO Removal Logic
void BST::removeOldest() {
    if (insertionOrder.empty()) return;

    int oldestId = insertionOrder.front();
    insertionOrder.pop();

    if (idToNodeMap.count(oldestId)) {
        Logger::log("Evicting oldest experience id: " + std::to_string(oldestId));
        removeHelper(root, oldestId);
        idToNodeMap.erase(oldestId);
    }
}

void BST::printHashMap() const {
    Logger::log("----------- HashMap Contents (idToNodeMap):");
    for (const auto& pair : idToNodeMap) {
        Logger::log("ID: " + std::to_string(pair.first) +
                    ", TD Error: " + std::to_string(pair.second->exp.tdError));
    }
}

void BST::printQueue() const {
    Logger::log("----------- Queue Contents (insertionOrder):");
    std::queue<int> copy = insertionOrder; // Copy to preserve original queue

    while (!copy.empty()) {
        Logger::log("Inserted ID: " + std::to_string(copy.front()));
        copy.pop();
    }
}
