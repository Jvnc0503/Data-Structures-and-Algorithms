
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T val;
    Node *next = nullptr;
    Node *prev = nullptr;

    explicit Node(const T &val): val(val) {
    }

    Node(const T &val, Node *next, Node *prev): val(val), next(next), prev(prev) {
    }
};

template<typename T>
class Queue {
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

public:
    Queue() = default;

    ~Queue() {
        clear();
    }

    void push(const T &val) {
        if (head == nullptr) {
            head = tail = new Node<T>(val);
        } else {
            tail = new Node<T>(val, nullptr, tail);
        }
    }

    void pop() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        const Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T front() const {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return head->val;
    }

    T rear() const {
        if (tail == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return tail->val;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (head != nullptr) {
            const Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void display() const {
        Node<T> *temp = head;
        while (temp != nullptr) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << '\n';
    }
};

#endif
