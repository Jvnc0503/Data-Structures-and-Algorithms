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
        if (head) {
            return head->data;
        }
        throw std::out_of_range("List is empty");
    }

    T back() {
        if (tail) {
            return tail->data;
        }
        throw std::out_of_range("List is empty");
    }

    void push_front(T data) {
        if (head) {
            head->prev = new Node<T>(data, head, nullptr);
            head = head->prev;
        } else {
            head = tail = new Node<T>(data);
        }
    }

    void push_back(T data) {
        if (tail) {
            tail->next = new Node<T>(data, nullptr, tail);
            tail = tail->next;
        } else {
            tail = head = new Node<T>(data);
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
        if (index == 0) {
            push_front(data);
            return;
        }

        auto temp = head;
        for (size_t i = 0; i < index - 1; ++i) {
            if (!temp) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }

        if (!temp) {
            throw std::out_of_range("Index out of range");
        }

        if (temp == tail) {
            push_back(data);
        } else {
            auto next = temp->next;
            temp->next = new Node<T>(data, next, temp);
            next->prev = temp->next;
        }
    }

    void remove(const size_t index) {
        if (!head) {
            throw std::out_of_range("List is empty");
        }

        auto temp = head;
        for (size_t i = 0; i < index; ++i) {
            if (!temp) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }
        if (!temp) {
            throw std::out_of_range("Index out of range");
        }

        auto prev = temp->prev;
        auto next = temp->next;
        delete temp;

        if (prev) {
            prev->next = next;
        } else {
            head = next;
        }

        if (next) {
            next->prev = prev;
        } else {
            tail = prev;
        }
    }

    T operator[](const size_t index) const {
        if (!head) {
            throw std::out_of_range("List is empty");
        }

        auto temp = head;
        for (size_t i = 0; i < index; ++i) {
            if (!temp) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }

        if (!temp) {
            throw std::out_of_range("Index out of range");
        }

        return temp->data;
    }
};

#endif