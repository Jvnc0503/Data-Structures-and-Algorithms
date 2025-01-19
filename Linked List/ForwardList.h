#ifndef FORWARDLIST_H
#define FORWARDLIST_H

template<typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {
    }

    explicit Node(T data) : data(data), next(nullptr) {
    }

    explicit Node(Node* next) : next(next) {
    }

    Node(T data, Node* next) : data(data), next(next) {
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
    }

    T front() {
        return head ? head->data : T();
    }

    T back() {
        if (head) {
            auto temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            return temp->data;
        }
        return T();
    }

    void push_front(T data) {
        auto front = new Node<T>(data, head);
        head = front;
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
        if (head) {
            auto temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pop_back() {
        if (head) {
            if (head->next) {
                auto temp = head;
                while (temp->next->next) {
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
            } else {
                head = nullptr;
            }
        }
    }

    void insert(T data, size_t index) {
        if (index) {
            auto temp = head;
            for (size_t i = 0; i < index - 1; ++i) {
                temp = temp->next;
            }
            auto next = temp->next;
            temp->next = new Node<T>(data, next);
        } else {
            push_front(data);
        }
    }

    T operator[](size_t index) {
        auto temp = head;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
            if (temp == nullptr) {
                return T();
            }
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
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
    }

    void sort() {
        if (head && head->next) {
            auto current = head;
            Node<T>* sorted = nullptr;
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
        }
    }

    void reverse() {
        if (head && head->next) {
            Node<T>* prev = nullptr;
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