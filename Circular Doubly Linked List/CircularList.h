#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}

    explicit Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    Node(Node* next, Node* prev) : next(next), prev(prev) {}

    Node(const T& data, Node* next, Node* prev) : data(data), next(next), prev(prev) {}

    ~Node() = default;
};

template <typename T>
class CircularList {
    Node<T>* head;
public:
    CircularList() : head(new Node<T>()) {
        head->next = head;
        head->prev = head;
    }

    T front() {
        if (!head->next) {
            throw std::out_of_range("List is empty");
        }
        return head->next->data;
    }

    T back() {
        if (!head->prev) {
            throw std::out_of_range("List is empty");
        }
        return head->prev->data;
    }

    void push_front(T data) {
        head->next = new Node<T>(data, head->next, head);
    }

    void push_back(T data) {
        head->prev = new Node<T>(data, head, head->prev);
    }

    T pop_front() {
        if (head->next == head) {
            throw std::out_of_range("List is empty");
        }
        T data = head->next->data;
        auto temp = head->next;
        head->next = temp->next;
        delete temp;
        head->next->prev = head;
        return data;
    }
};

#endif