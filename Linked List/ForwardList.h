#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {
    }

    explicit Node(T data) : data(data), next(nullptr) {
    }

    explicit Node(Node *next) : next(next) {
    }

    Node(T data, Node *next) : data(data), next(next) {
    }
};

template<typename T>
class ForwardList {
    Node<T> *head;

public:
    ForwardList() : head(nullptr) {
    }

    ~ForwardList() {
        auto temp = head;
        while (temp) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }

    T front() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        auto temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data) {
        head = new Node<T>(data, head);
    }

    void push_back(T data) {
        if (head) {
            auto back = new Node<T>(data);
            auto temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = back;
        } else {
            head = new Node<T>(data);
        }
    }

    void pop_front() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        auto temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            auto temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
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
        auto next = temp->next;
        temp->next = new Node<T>(data, next);
    }

    void remove(const size_t index) {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        if (index == 0) {
            pop_front();
            return;
        }
        auto temp = head;
        for (size_t i = 0; i < index - 1; ++i) {
            if (!temp) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }
        if (!temp || !temp->next) {
            throw std::out_of_range("Index out of range");
        }
        auto next = temp->next->next;
        delete temp->next;
        temp->next = next;
    }

    T &operator[](const size_t index) {
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

    bool empty() {
        return !head;
    }

    size_t size() {
        size_t size = 0;
        auto temp = head;
        while (temp) {
            ++size;
            temp = temp->next;
        }
        return size;
    }

    void clear() {
        auto temp = head;
        while (temp) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }

    void sort() {
        if (!head || !head->next) {
            return;
        }
        auto current = head;
        Node<T> *sorted = nullptr;
        while (current) {
            auto next = current->next;
            if (!sorted || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                auto temp = sorted;
                while (temp->next && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    void reverse() {
        if (head && head->next) {
            Node<T> *prev = nullptr;
            auto current = head;
            auto next = head->next;
            while (current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }
    }
};

#endif
