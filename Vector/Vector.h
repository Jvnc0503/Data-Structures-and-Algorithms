#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template<typename T>
class Vector {
    T *arr;
    size_t capacity_;
    size_t size_;

public:
    Vector() : arr(new T[1]), capacity_(1), size_(0) {
    }

    explicit Vector(const size_t &n, const T &val = T()): capacity_(n), size_(n), arr(new T[n]) {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = val;
        }
    }

    ~Vector() {
        delete[] arr;
    }

    Vector(const Vector &other): capacity_(other.capacity_), size_(other.size_) {
        arr = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr[i] = other.arr[i];
        }
    }

    Vector(Vector &&other) noexcept
        : arr(other.arr), capacity_(other.capacity_), size_(other.size_) {
        other.arr = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            delete[] arr;
            capacity_ = other.capacity_;
            size_ = other.size_;
            arr = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.arr = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    void reserve(const size_t &new_capacity) {
        if (new_capacity > capacity_) {
            T *temp = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                temp[i] = std::move(arr[i]);
            }
            delete[] arr;
            arr = temp;
            capacity_ = new_capacity;
        }
    }

    void resize(const size_t &new_size, const T &val = T()) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = size_; i < new_size; ++i) {
            arr[i] = val;
        }
        size_ = new_size;
    }

    void push_back(const T &value) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2);
        }
        arr[size_++] = value;
    }

    void push_back(T &&value) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2);
        }
        arr[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        arr[--size_].~T();
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
        for (size_t i = 0; i < size_; ++i) {
            arr[i].~T();
        }
        size_ = 0;
    }
};
#endif
