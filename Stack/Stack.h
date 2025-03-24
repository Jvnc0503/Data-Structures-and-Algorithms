#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdexcept>
#include <utility>

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

    Stack(Stack &&other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    Stack &operator=(const Stack &other) {
        if (this == &other) return *this;
        clear();
        if (!other.head) {
            head = nullptr;
            return *this;
        }
        head = new Node<T>(other.head->val);
        Node<T> *current = head;
        for (Node<T> *temp = other.head->next; temp != nullptr; temp = temp->next) {
            current->next = new Node<T>(temp->val);
            current = current->next;
        }
        return *this;
    }

    Stack &operator=(Stack &&other) noexcept {
        if (this == &other) return *this;
        clear();
        head = other.head;
        other.head = nullptr;
        return *this;
    }

    ~Stack() {
        clear();
    }

    template<typename U>
    void push(U &&val) {
        head = new Node<T>(std::forward<U>(val), head);
    }

    template<typename... Ts>
    void push(Ts &&... args) {
        (push(std::forward<Ts>(args)), ...);
    }

    template<typename... Ts>
    void emplace(Ts &&... args) {
        head = new Node<T>(T(std::forward<Ts>(args)...), head);
    }

    T &top() {
        if (head == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return head->val;
    }

    const T &top() const {
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

    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Stack &stack) {
        const Node<T> *temp = stack.head;
        os << "Stack [ ";
        while (temp) {
            os << temp->val << ' ';
            temp = temp->next;
        }
        os << "]";
        return os;
    }
};

#endif
