/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;
    bool insert(const std::string& key, size_t value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);
    vector<std::string> findRange( const std::string& lowKey,
    const std::string& highKey) const;
    std::vector<std::string> keys() const;
    size_t size() const;
    size_t getHeight() const;
    AVLTree(const AVLTree& other);
    void operator=(const AVLTree& other);
    ~AVLTree();
    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);


protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        AVLNode(const std::string& key, size_t value) : key(key), value(value), height(0), left(nullptr), right(nullptr) {}
    };

public:




    private:
    AVLNode* root;
    AVLNode* nodeFinder(AVLNode* current, const std::string& key, bool cases) const;
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);
    int getBalance (AVLNode *&node);
    int avlSize;
    void updateHeight(AVLNode *&current);
    AVLNode* nodeSpaceFinder(AVLNode* current, const std::string &key) const;
    void balanceTree(AVLNode*& parentNode, AVLNode* root);
    AVLNode* findSuccessor(AVLNode* parentNode);
    bool removeSuccessor(const std::string& key);

};

#endif //AVLTREE_H
