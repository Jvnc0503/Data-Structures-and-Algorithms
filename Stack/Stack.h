#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T val;
    Node *next = nullptr;

    explicit Node(const T &data) : val(data) {
    }

    Node(const T &data, Node *next) : val(data), next(next) {
    }
};

template<typename T>
class Stack {
    Node<T> *head = nullptr;

public:
    Stack() = default;

    ~Stack() {
        clear();
    }

    void push(const T &val) {
        head = new Node<T>(val, head);
    }

    T top() const {
        if (head == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return head->val;
    }

    void pop() {
        if (head == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        const Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    void clear() {
        while (head != nullptr) {
            const Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void display() const {
        Node<T> *temp = head;
        while (temp != nullptr) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif
