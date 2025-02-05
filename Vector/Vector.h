#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template<typename T>
class Vector {
    T *arr;
    size_t capacity_ = 1;
    size_t size_ = 0;

    void resize() {
        capacity_ *= 2;
        T *temp = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            temp[i] = std::move(arr[i]);
        }
        delete[] arr;
        arr = temp;
    }

public:
    Vector() {
        arr = new T[capacity_];
    }

    ~Vector() {
        clear();
        delete[] arr;
    }

    Vector(const Vector &other): capacity_(other.capacity_), size_(other.size_) {
        arr = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr[i] = other.arr[i];
        }
    }

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            T *temp = new T[other.capacity_];
            for (size_t i = 0; i < other.size_; ++i) {
                temp[i] = other.arr[i];
            }
            delete[] arr;
            arr = temp;
            capacity_ = other.capacity_;
            size_ = other.size_;
        }
        return *this;
    }

    void push_back(const T &value) {
        if (size_ == capacity_) {
            resize();
        }
        arr[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            arr[--size_].~T();
        }
    }

    T &operator[](const size_t &index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    const T &operator[](const size_t &index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        while (size > 0) {
            pop_back();
        }
        size = 0;
    }
};
#endif
