#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}

    explicit Node(T data) : data(data), next(nullptr), prev(nullptr) {}

    Node(Node* next, Node* prev) : next(next), prev(prev) {}

    Node(T data, Node* next, Node* prev) : data(data), next(next), prev(prev) {}
};

template <typename T>
class CircularList {
    Node<T>* head;
public:
    CircularList() : head(new Node<T>()) {
        head->next = head;
        head->prev = head;
    }
};

#endif