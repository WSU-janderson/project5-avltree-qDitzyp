#include "AVLTree.h"

#include <string>

size_t AVLTree::AVLNode::numChildren() const {
    return !!left + !!right;
}

bool AVLTree::AVLNode::isLeaf() const {
    return !left && !right;
}

int AVLTree::AVLNode::getHeight() const {
    return height;
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
    if (!current) return false;
    bool removed = false;
    if (key < current->key) {
        removed = remove(current->left, key);
    } else if (key > current->key){
        removed = remove(current->right, key);
    } else {
        removed = removeNode(current);
        if (removed) {
            avlSize--;
        }
    }
    if (!removed) {
        return false;
    }
    updateHeight(current);
    balanceNode(current);
    return true;
}

bool AVLTree::remove(const std::string& key) {
    return remove(root, key);
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
            rotateRight(node->right);
        }
        rotateLeft(node);
    } else if (getBalance(node) == 2) {
        if (getBalance(node->left) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}
void AVLTree::rotateLeft(AVLNode* &node) {
    AVLNode* hook = node->right;
    node->right = hook->left;
    hook->left = node;
    node = hook;
    updateHeight(node->left);
    updateHeight(node);
}

void AVLTree::rotateRight(AVLNode* &node) {
    AVLNode* hook = node->left;
    node->left = hook->right;
    hook->right = node;
    node = hook;
    updateHeight(node->right);
    updateHeight(node);
}

bool AVLTree::insert(AVLNode*& current, const std::string& key, size_t value) {
    if (!current) {
        current = new AVLNode(key, value);
        avlSize++;
        return true;
    }
    bool inserted = false;
    if (key < current->key) {
        inserted = insert(current->left, key, value);
    } else if (key > current->key){
        inserted = insert(current->right, key, value);
    }
    if (!inserted) {
        return false;
    }
    updateHeight(current);
    balanceNode(current);
    return true;
}

bool AVLTree::insert(const std::string& key, size_t value) {
    if (contains(key) == true) return false;
    return insert(root, key, value);
}

bool AVLTree::contains(const std::string& key) const {
    if (nodeFinder(root, key,false) == nullptr) {
        return false;
    } else {
        return true;
    }
}

std::optional<size_t> AVLTree::get(const std::string& key) const {
    AVLNode* current = nodeFinder(root, key, false);
    if (!current) return std::nullopt;
    return std::make_optional(current->value);
}

size_t& AVLTree::operator[](const std::string& key) {
    return nodeFinder(root, key, false)->value;
}

void AVLTree::findRange(AVLNode* current, std::vector<size_t>& valueList, const std::string& lowKey, const std::string& highKey) const {
    if (!current) return;

    findRange(current->left, valueList, lowKey, highKey);
    if (current->key >= lowKey && current->key <= highKey) {
        valueList.push_back(current->value);
    }
    findRange(current->right, valueList, lowKey, highKey);
}

std::vector<size_t> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {
    std::vector<size_t> valueList;
    findRange(root, valueList, lowKey, highKey);
    return valueList;
}

//in alphabetical order (left, current, right)
void AVLTree::keys(AVLNode* current, std::vector<std::string>& keyList) const {
    if (!current) return;
    keys(current->left, keyList);
    keyList.push_back(current->key);
    keys(current->right, keyList);
}

std::vector<std::string> AVLTree::keys() const {
    std::vector<std::string> keyList;
    keys(root, keyList);
    return keyList;
}

size_t AVLTree::size() const {
    return this->avlSize;
}

int AVLTree::getHeight() const {
    if (!root) return -1;
    return root->height;
}

AVLTree::AVLTree(const AVLTree& other) {

}

void AVLTree destroyTree(AVLNode* current) {
    
}
void AVLTree::operator=(const AVLTree& other) {

}

AVLTree::~AVLTree() {

}

std::ostream& operator<<(ostream& os, const AVLTree & avlTree) {

}

AVLTree::AVLNode* AVLTree::nodeFinder(AVLNode* current, const std::string &key, bool cases) const {
    if (!current) return nullptr;
    if (cases == true) {
        if (current->left->key == key || current->right->key == key) {
            return current;
        } else if (key < current->key) {
            return nodeFinder(current->left, key, true);
        } else {
            return nodeFinder(current->right, key, true);
        }
    }
    if (current->key == key) {
        return current;
    } else if (key < current->key) {
        return nodeFinder(current->left, key, false);
    } else {
        return nodeFinder(current->right, key, false);
    }
}

void AVLTree::updateHeight(AVLNode *&current) {
    int leftheight = -1;
    int rightheight = -1;
    if (current->left != nullptr) {
    leftheight = current->left->height;
    }
    if (current->right != nullptr) {
        rightheight = current->right->height;
    }
    current->height = max(leftheight, rightheight) + 1;
}