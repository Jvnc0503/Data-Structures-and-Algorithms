#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
#include <stack>

template<typename T>
struct Node {
    T val;
    int height;
    Node *left;
    Node *right;

    explicit Node(const T &val): val(val), height(0), left(nullptr), right(nullptr) {
    }
};

template<typename T>
class AVL {
    Node<T> *root;

    void updateHeight(Node<T> *node) const {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    int getBalance(Node<T> *node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node<T> *LL(Node<T> *A) {
        Node<T> *B = A->left;
        A->left = B->right;
        B->right = A;
        updateHeight(A);
        updateHeight(B);
        return B;
    }

    Node<T> *RR(Node<T> *A) {
    }

    Node<T> *LR(Node<T> *A) {
    }

    Node<T> *RL(Node<T> *A) {
    }

    Node<T> *balance(Node<T> *node) {
        const int balance = getBalance(node);

        if (balance == 2) {
            if (getBalance(node->left) == -1) {
                return LR(node);
            }
            return LL(node);
        }
        if (balance == -2) {
            if (getBalance(node->right) == 1) {
                return RL(node);
            }
            return RR(node);
        }
        return node;
    }

    Node<T> *insert(Node<T> *node, const T &val) {
        if (node == nullptr) {
            return new Node<T>(val);
        }
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        updateHeight(node);
        return balance(node);
    }

public:
    AVL() : root(nullptr) {
    }

    void insert(const T &val) {
        root = insert(root, val);
    }
};

#endif
