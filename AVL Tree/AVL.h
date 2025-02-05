#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>

template<typename T>
struct Node {
    T val;
    short balance = 0;
    Node *left;
    Node *right;

    explicit Node(T val = 0, Node *left = nullptr, Node *right = nullptr): val(val), left(left), right(right) {
    }
};

template<typename T>
class AVL {
    Node<T> *root;

    void LL(Node<T> *&pA) {
        auto pB = pA->left;
        pA->left = pB->right;
        pB->right = pA;
        pA = pB;
    }

    void RR(Node<T> *&pA) {
        auto pB = pA->right;
        pA->right = pB->left;
        pB->left = pA;
        pA = pB;
    }

    void LR(Node<T> *&pA) {
        auto pB = pA->left;
        auto pC = pB->right;
        pB->right = pC->left;
        pC->left = pB;
        pA->left = pC->left;
        pC->right = pA;
        pA = pC;
    }

    void RL(Node<T> *&pA) {
        auto pB = pA->right;
        auto pC = pB->left;
        pB->left = pC->right;
        pC->right = pB;
        pA->right = pC->left;
        pC->left = pA;
        pA = pC;
    }

    void DFS(Node<T> *p) {
        if (p == nullptr) {
            return;
        }
        DFS(p->left);
        std::cout << p->val << ' ';
        DFS(p->right);
    }

    void BFS(Node<T> *p) {
        std::queue<Node<T> *> q;
        q.push(p);
        while (!q.empty()) {
            auto temp = q.front();
            q.pop();
            std::cout << temp->val << ' ';
            if (temp->left != nullptr) {
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                q.push(temp->right);
            }
        }
    }

public:
    AVL(): root(nullptr) {
    }

    void insert(T val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
    }
};

#endif
