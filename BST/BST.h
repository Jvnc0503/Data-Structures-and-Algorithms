#ifndef BST_H
#define BST_H

template<typename T>
struct Node {
    T val;
    Node *left;
    Node *right;

    Node(T value, Node *left = nullptr, Node *right = nullptr): val(value), left(left), right(right) {
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

    Node *&findMin(Node<T> *&node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }

    bool remove(Node<T> *&node, const T &value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->val) {
            return remove(node->left, value);
        } else if (value > node->val) {
            return remove(node->right, value);
        } else {
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
};


#endif
