#ifndef LIST_H
#define LIST_H
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {
    }

    explicit Node(T data) : data(data), next(nullptr), prev(nullptr) {
    }

    Node(Node* next, Node* prev) : next(next), prev(prev) {
    }

    Node(T data, Node* next, Node* prev) : data(data), next(next), prev(prev) {
    }
};

template<typename T>
class List {
    Node<T>* head;
    Node<T>* tail;
public:
    List() : head(nullptr), tail(nullptr) {
    }

    ~List() {
        auto temp = head;
        while (temp) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
    }

    T front() {
        return head ? head->data : T();
    }

    T back() {
        return tail ? tail->data : T();
    }

    void push_front(T data) {
        auto front = new Node<T>(data, head, nullptr);
        if (head) {
            head->prev = front;
            head = front;
        } else {
            head = tail = front;
        }
    }

    void push_back(T data) {
        auto back = new Node<T>(data, nullptr, tail);
        if (tail) {
            tail->next = back;
            tail = back;
        } else {
            tail = head = back;
        }
    }

    void pop_front() {
        if (head) {
            auto temp = head;
            head = head->next;
            delete temp;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        }
    }

    void pop_back() {
        if (tail) {
            auto temp = tail;
            tail = tail->prev;
            delete temp;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        }
    }

    void insert(T data, const size_t index) {
        if (head) {
            auto temp = head;
            for (size_t i = 0; i < index; ++i) {
                if (temp == nullptr) {
                    throw std::out_of_range("Index out of range");
                }
                temp = temp->next;
            }
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            if (temp == tail) {
                temp->next = new Node<T>(data, nullptr, temp);
                tail = temp->next;
            } else {
                auto next = temp->next;
                temp->next = new Node<T>(data, next, temp);
                next->prev = temp->next;
            }
        } else {
            push_front(data);
        }
    }
};

#endif