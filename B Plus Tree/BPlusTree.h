#ifndef BPLUSTREE_H
#define BPLUSTREE_H

template<typename K, typename V>
class BPlusTree {
private:
    static const int MIN_DEGREE = 3;

    struct Node {
        bool is_leaf;
        K *keys;
        Node **children;
        Node *next;
        V *values;
        int size;
        int capacity;

        Node(bool leaf = true) : is_leaf(leaf), next(nullptr), size(0), capacity(2 * MIN_DEGREE - 1) {
            keys = new K[capacity];
            if (leaf) {
                values = new V[capacity];
                children = nullptr;
            } else {
                values = nullptr;
                children = new Node *[capacity + 1];
            }
        }

        ~Node() {
            delete[] keys;
            delete[] values;
            if (!is_leaf) {
                delete[] children;
            }
        }

        void insert_key(const K &key, int pos) {
            for (int i = size; i > pos; i--) {
                keys[i] = keys[i - 1];
            }
            keys[pos] = key;
            size++;
        }

        void insert_value(const V &value, int pos) {
            for (int i = size - 1; i > pos; i--) {
                values[i] = values[i - 1];
            }
            values[pos] = value;
        }

        void insert_child(Node *child, int pos) {
            for (int i = size + 1; i > pos; i--) {
                children[i] = children[i - 1];
            }
            children[pos] = child;
        }
    };

    Node *root;
    int height;

    Node *findLeaf(const K &key) {
        Node *current = root;
        while (!current->is_leaf) {
            int idx = 0;
            while (idx < current->size && key >= current->keys[idx]) {
                idx++;
            }
            current = current->children[idx];
        }
        return current;
    }

    void splitChild(Node *parent, int idx, Node *child) {
        Node *new_node = new Node(child->is_leaf);
        int mid = child->size / 2;

        // Copy second half
        for (int i = 0; i < child->size - mid; i++) {
            new_node->keys[i] = child->keys[mid + i];
        }
        new_node->size = child->size - mid;

        if (!child->is_leaf) {
            for (int i = 0; i <= child->size - mid; i++) {
                new_node->children[i] = child->children[mid + i];
            }
        } else {
            for (int i = 0; i < child->size - mid; i++) {
                new_node->values[i] = child->values[mid + i];
            }
            new_node->next = child->next;
            child->next = new_node;
        }

        child->size = mid;

        for (int i = parent->size; i > idx; i--) {
            parent->keys[i] = parent->keys[i - 1];
        }
        parent->keys[idx] = new_node->keys[0];

        for (int i = parent->size + 1; i > idx + 1; i--) {
            parent->children[i] = parent->children[i - 1];
        }
        parent->children[idx + 1] = new_node;
        parent->size++;
    }

    void insertNonFull(Node *node, const K &key, const V &value) {
        int idx = node->size - 1;

        if (node->is_leaf) {
            while (idx >= 0 && key < node->keys[idx]) {
                node->keys[idx + 1] = node->keys[idx];
                node->values[idx + 1] = node->values[idx];
                idx--;
            }
            idx++;
            node->keys[idx] = key;
            node->values[idx] = value;
            node->size++;
        } else {
            while (idx >= 0 && key < node->keys[idx]) {
                idx--;
            }
            idx++;

            if (node->children[idx]->size == 2 * MIN_DEGREE - 1) {
                splitChild(node, idx, node->children[idx]);
                if (key > node->keys[idx]) {
                    idx++;
                }
            }
            insertNonFull(node->children[idx], key, value);
        }
    }

public:
    BPlusTree() : root(new Node()), height(1) {
    }

    ~BPlusTree() {
        // Implement deletion of all nodes
    }

    void insert(const K &key, const V &value) {
        Node *r = root;
        if (r->size == 2 * MIN_DEGREE - 1) {
            Node *new_root = new Node(false);
            new_root->children[0] = r;
            root = new_root;
            height++;
            splitChild(new_root, 0, r);
            insertNonFull(new_root, key, value);
        } else {
            insertNonFull(r, key, value);
        }
    }

    V *find(const K &key) {
        Node *leaf = findLeaf(key);
        for (int i = 0; i < leaf->size; i++) {
            if (leaf->keys[i] == key) {
                return &leaf->values[i];
            }
        }
        return nullptr;
    }
};
#endif
