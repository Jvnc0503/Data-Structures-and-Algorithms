#ifndef BST_H
#define BST_H

template<class T>
struct Node {
    T val;
    Node *left;
    Node *right;

    Node(T value, Node *left = nullptr, Node *right = nullptr): val(value), left(left), right(right) {
    };

    ~Node() {
        delete left;
        delete right;
    };
};

class BST {
};


#endif
