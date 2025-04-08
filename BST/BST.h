#ifndef BST_H
#define BST_H
#include <algorithm>

template<typename T>
struct Node {
    T val;
    Node *left;
    Node *right;

    explicit Node(T value, Node *left = nullptr, Node *right = nullptr): val(value), left(left), right(right) {
    }

    ~Node() {
        delete left;
        delete right;
    }
};

template<typename T>
class BST {
    Node<T> *root;

    bool insert(Node<T> *&node, const T &value) {
        if (node == nullptr) {
            node = new Node<T>(value);
            return true;
        }
        if (value < node->val) {
            return insert(node->left, value);
        }
        if (value > node->val) {
            return insert(node->right, value);
        }
        return false;
    }

    bool search(Node<T> *node, const T &value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->val) {
            return search(node->left, value);
        }
        if (value > node->val) {
            return search(node->right, value);
        }
        return true;
    }

    Node<T> *&findMin(Node<T> *&node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }

    Node<T> *&findMax(Node<T> *&node) {
        if (node->right == nullptr) {
            return node;
        }
        return findMax(node->right);
    }

    bool remove(Node<T> *&node, const T &value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->val) {
            return remove(node->left, value);
        }
        if (value > node->val) {
            return remove(node->right, value);
        }

        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node<T> *temp = node;
            node = node->right;
            temp->right = nullptr;
            delete temp;
        } else if (node->right == nullptr) {
            Node<T> *temp = node;
            node = node->left;
            temp->left = nullptr;
            delete temp;
        } else {
            Node<T> *successor = findMin(node->right);
            node->val = successor->val;
            Node<T> *temp = successor;
            successor = successor->right;
            temp->right = nullptr;
            delete temp;
        }
        return true;
    }

    size_t height(Node<T> *node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

public:
    BST() : root(nullptr) {
    }

    ~BST() {
        delete root;
    }

    bool insert(const T &value) {
        return insert(root, value);
    }

    bool search(const T &value) {
        return search(root, value);
    }

    bool remove(const T &value) {
        return remove(root, value);
    }

    size_t height() {
        return height(root);
    }

    T findMin() {
        return findMin(root)->val;
    }

    T findMax() {
        return findMax(root)->val;
    }
};


#endif
