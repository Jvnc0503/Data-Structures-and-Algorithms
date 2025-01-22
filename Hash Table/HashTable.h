#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <random>

template <typename T1, typename T2>
struct Node {
    T1 key;
    T2 value;
    Node* next;
    explicit Node(T1 key) : key(key), value(T2()), next(nullptr) {}
    Node(T1 key, T2 value) : key(key), value(value), next(nullptr) {}
};

template <typename T1, typename T2>
class HashTable {
    Node<T1, T2>** table;
    size_t a;
    size_t b;
    const size_t p = 1000000007;    //Large prime number
    size_t size;

    size_t hash(T1 key) {
        return ((a * key + b) % p) % size;
    }

    void initialize() {
        table = new Node<T1, T2>*[size];
        for (size_t i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            Node<T1, T2>* current = table[i];
            while (current != nullptr) {
                Node<T1, T2>* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
        table = nullptr;
    }

    double loadFactor() {
        double count = 0;
        size_t maxCollision = 0;
        for (size_t i = 0; i < size; ++i) {
            size_t collision = 0;
            Node<T1, T2>* current = table[i];
            while (current != nullptr) {
                ++count;
                ++collision;
                current = current->next;
            }
            if (collision > maxCollision) {
                maxCollision = collision;
            }
        }
        return count / (size * maxCollision);
    }

public:
    HashTable() : size(100) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis1(1, p - 1);
        std::uniform_int_distribution<size_t> dis2(0, p - 1);
        a = dis1(gen);
        b = dis2(gen);
        initialize();
    }

    explicit HashTable(const size_t size) : size(size){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis1(1, p - 1);
        std::uniform_int_distribution<size_t> dis2(0, p - 1);
        a = dis1(gen);
        b = dis2(gen);
        initialize();
    }

    ~HashTable() {
        clear();
    }

    T2& operator[](T1 key) {
        size_t index = hash(key);
        Node<T1, T2>* current = table[index];
        if (current == nullptr) {
            table[index] = new Node<T1, T2>(key);
            return table[index]->value;
        }
        while (current->key != key && current->next != nullptr) {
            current = current->next;
        }
        if (current->key == key) {
            return current->value;
        }
        current->next = new Node<T1, T2>(key);
        return current->next->value;
    }
};

#endif