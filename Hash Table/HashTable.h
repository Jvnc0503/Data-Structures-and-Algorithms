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
    const size_t p = 1000000007;
    size_t size;
    size_t elements;

    size_t hash(const T1& key) {
        return ((a * key + b) % p) % size;
    }

    size_t hash(const std::string &key) {
        return hash(std::hash<std::string>{}(key));
    }

    void initialize() {
        table = new Node<T1, T2>*[size];
        for (size_t i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    double loadFactor() {
        if (size) {
            return static_cast<double>(elements) / size;
        }
        return 0;
    }

    void rehash() {
        const size_t oldSize = size;
        size *= 2;
        Node<T1, T2>** oldTable = table;
        initialize();
        elements = 0;

        for (size_t i = 0; i < oldSize; ++i) {
            Node<T1, T2>* current = oldTable[i];
            while (current != nullptr) {
                (*this)[current->key] = current->value;
                Node<T1, T2>* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] oldTable;
    }

public:
    HashTable() : size(100), elements(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis1(1, p - 1);
        std::uniform_int_distribution<size_t> dis2(0, p - 1);
        a = dis1(gen);
        b = dis2(gen);
        initialize();
    }

    explicit HashTable(const size_t size) : size(size), elements(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis1(1, p - 1);
        std::uniform_int_distribution<size_t> dis2(0, p - 1);
        a = dis1(gen);
        b = dis2(gen);
        initialize();
    }

    ~HashTable() {
        erase();
    }

    void erase() {
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

    bool empty() {
        return elements == 0;
    }

    T2& operator[](const T1& key) {
        if (loadFactor() > 0.75) {
            rehash();
        }
        size_t index = hash(key);
        Node<T1, T2>* current = table[index];
        if (current == nullptr) {
            table[index] = new Node<T1, T2>(key);
            ++elements;
            return table[index]->value;
        }
        while (current->key != key && current->next != nullptr) {
            current = current->next;
        }
        if (current->key == key) {
            return current->value;
        }
        current->next = new Node<T1, T2>(key);
        ++elements;
        return current->next->value;
    }

    bool isPresent(const T1& key) {
        Node<T1, T2> current = table[hash(key)];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

#endif