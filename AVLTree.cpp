#include "AVLTree.h"

#include <string>

size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}
int AVLTree::getBalance(AVLNode *&node) {
    int balance;
    if (node->left != nullptr && node->right != nullptr) {
        balance = node->left->height - node->right->height;
    } else if (node->left == nullptr) {
        balance = (-1) - node->right->height;
    } else {
        balance = node->left->height - (-1);
    }
    return balance;
}

void AVLTree::balanceNode(AVLNode *&node) {

    if (getBalance(node) < 2 && getBalance(node) > -2) {
        return;
    } else if (getBalance(node) == -2){
        if (getBalance(node->right) == 1) {

        }
    } else if (getBalance(node) == 2) {
        if (getBalance(node->left) == -1) {

        }
    }
}

bool AVLTree::insert(const std::string& key, size_t value) {

}

bool AVLTree::remove(const std::string& key) {
    AVLNode* nodeToRemove = nodeFinder(root, key);
    if (!nodeToRemove) {
        return false;
    } else {

    }
}

bool AVLTree::contains(const std::string& key) const {
    if (nodeFinder(root, key) == nullptr) {
        return false;
    } else {
        return true;
    }
}

std::optional<size_t> AVLTree::get(const std::string& key) const {
    return nodeFinder(root, key)->value;
}

size_t& AVLTree::operator[](const std::string& key) {
    return nodeFinder(root, key)->value;
}

vector<std::string> AVLTree::findRange( const std::string& lowKey, const std::string& highKey) const {

}
std::vector<std::string> AVLTree::keys() const {

}

size_t AVLTree::size() const {

}

size_t AVLTree::getHeight() const {

}

AVLTree::AVLTree(const AVLTree& other) {

}

void AVLTree::operator=(const AVLTree& other) {

}

AVLTree::~AVLTree() {

}

std::ostream& operator<<(ostream& os, const AVLTree & avlTree) {

}

AVLTree::AVLNode* AVLTree::nodeFinder(AVLNode* current, const std::string &key) const {
    if (!current) return nullptr;
    if (current->key == key) {
        return current;
    } else if (key < current->key) {
        return nodeFinder(current->left, key);
    } else {
        return nodeFinder(current->right, key);
    }
}
