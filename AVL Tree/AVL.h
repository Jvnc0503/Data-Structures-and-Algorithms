#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
#include <stack>

template<typename T>
struct Node {
    T val;
    short height = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(const T &val): val(val) {
    }

    ~Node() {
        delete left;
        delete right;
    }
};

template<typename T>
class AVL {
    Node<T> *root;
public:
    AVL() : root(nullptr) {}

    ~AVL() {
        delete root;
    }
};

#endif
