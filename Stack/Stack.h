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

    Stack(const Stack &other) {
        if (!other.head) {
            head = nullptr;
            return;
        }
        head = new Node<T>(other.head->val);
        Node<T> *current = head;
        for (Node<T> *temp = other.head->next; temp != nullptr; temp = temp->next) {
            current->next = new Node<T>(temp->val);
            current = current->next;
        }
    }

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
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void display() const {
        const Node<T> *temp = head;
        while (temp != nullptr) {
            std::cout << temp->val << '\n';
            temp = temp->next;
        }
        std::cout << '\n';
    }
};

#endif
