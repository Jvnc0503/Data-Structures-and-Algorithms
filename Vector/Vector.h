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
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

public:
    Vector() {
        arr = new T[capacity_];
    }

    ~Vector() {
        delete[] arr;
    }

    Vector(const Vector &og): capacity_(og.capacity_), size_(og.size_) {
        arr = new T[capacity_];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = og.arr[i];
        }
    }

    Vector &operator=(const Vector &other) {
        if (this != other) {
            delete[] arr;
            capacity_ = other.capacity_;
            size_ = other.size_;
            arr = new T[capacity_];
            for (size_t i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    void push_back(const T &value) {
        if (size_ == capacity_) {
            resize();
        }
        arr[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    T &operator[](const size_t &index) {
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
        size_ = 0;
    }
};
#endif
