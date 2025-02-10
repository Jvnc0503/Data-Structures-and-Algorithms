#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>

template<typename T>
struct Node {
    T val;
    short balance = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(const T &val): val(val) {
    }
};

template<typename T>
class AVL {
    Node<T> *root;

    Node<T> *LL(Node<T> *A) {
        Node<T> *B = A->left;
        A->left = B->right;
        B->right = A;
        return B;
    }

    Node<T> *RR(Node<T> *A) {
        Node<T> *B = A->right;
        A->right = B->left;
        B->left = A;
        return B;
    }

    Node<T> *LR(Node<T> *A) {
        Node<T> *B = A->left;
        Node<T> *C = B->right;
        B->right = C->left;
        C->left = B;
        A->left = C->right;
        C->right = A;
        return C;
    }

    Node<T> *RL(Node<T> *A) {
        Node<T> *B = A->right;
        Node<T> *C = B->left;
        B->left = C->right;
        C->right = B;
        A->right = C->left;
        C->left = A;
        return C;
    }

    void insertAux(Node<T> *p, const T &val) {
        if (val == p->val) {
            throw std::runtime_error("Duplicate value");
        }
        if (val < p->val) {
            if (p->left == nullptr) {
                p->left = new Node<T>(val);
                ++p->balance;
                return;
            }
            if (p->balance == 0) {
                p->balance = 1;
            } else if (p->balance == 2) {
                if (p->left->balance == 1) {
                    p = LL(p);
                    p->balance = p->right->balance = 0;
                } else {
                    p = LR(p);
                    if (p->balance == 1) {
                        p->left->balance = 0;
                        p->right->balance = -1;
                    } else if (p->balance == -1) {
                        p->left->balance = 1;
                        p->right->balance = 0;
                    } else {
                        p->left->balance = p->right->balance = 0;
                    }
                    p->balance = 0;
                }
            }
        } else {
            if (p->right == nullptr) {
                p->right = new Node<T>(val);
                --p->balance;
                return;
            }
            if (p->balance == 0) {
                p->balance = -1;
            } else if (p->balance == -2) {
                if (p->right == -1) {
                    p = RR(p);
                    p->balance = p->left->balance = 0;
                } else {
                    p = RL(p);
                    if (p->balance == 1) {
                        p->left->balance = 0;
                        p->right->balance = -1;
                    } else if (p->balance == -1) {
                        p->left->balance = 1;
                        p->right->balance = 0;
                    } else {
                        p->left->balance = p->right->balance = 0;
                    }
                    p->balance = 0;
                }
            }
        }
    }

public:
    AVL(): root(nullptr) {
    }

    void insert(const T &val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
        insertAux(root, val);
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
};

#endif
