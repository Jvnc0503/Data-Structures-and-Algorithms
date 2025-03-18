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
        if (this == &other) {
            return;
        }
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

    template<typename... Ts>
    explicit Stack(Ts... args) {
        (push(std::forward<Ts>(args)), ...);
    }

    Stack(Stack &&other) noexcept {
        head = other.head;
        other.head = nullptr;
    }

    ~Stack() {
        clear();
    }

    void push(const T &val) {
        head = new Node<T>(val, head);
    }

    template<typename... Ts>
    void push(Ts... args) {
        (push(std::forward<Ts>(args)), ...);
    }

    template<typename... Ts>
    void emplace(T &&args) {
        head = new Node<T>(T(std::forward<Ts>(args)), head);
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
