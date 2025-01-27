#ifndef AVL_H
#define AVL_H

template<typename T>
struct Node {
    T val;
    int bal;
    Node *left;
    Node *right;

    Node(): val(0), bal(0), left(nullptr), right(nullptr) {
    }

    explicit Node(T val): val(val), bal(0), left(nullptr), right(nullptr) {
    }
};

template<typename T>
class AVL {
    Node<T> *root;

    void LR(Node<T> *&pA) {
        auto pB = pA->left;
        auto pC = pB->right;
        pB->right = pC->left;
        pC->left = pB;
        pA->left = pC->left;
        pC->right = pA;
        pA = pC;
    }

public:
    AVL(): root(nullptr) {
    }
};

#endif
