#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template<typename T>
class Vector {
    T *arr;
    size_t capacity_ = 1;
    size_t size_ = 0;

public:
    //Constructor
    Vector() {
        arr = new T[capacity_];
    }

    //Destructor
    ~Vector() {
        clear();
        delete[] arr;
    }

    //Copy Constructor
    Vector(const Vector &other): capacity_(other.capacity_), size_(other.size_) {
        arr = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr[i] = other.arr[i];
        }
    }

    //Move Constructor
    Vector(Vector &&other) noexcept: arr(other.arr), capacity_(other.capacity_), size_(other.size_) {
        other.arr = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    //Copy Assignment Operator
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

    //Move Assignment Operator
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

    void resize(const size_t &new_capacity) {
        capacity_ = new_capacity;
        T *temp = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            temp[i] = std::move(arr[i]);
        }
        delete[] arr;
        arr = temp;
    }

    //Copy push_back
    void push_back(const T &value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        arr[size_++] = value;
    }

    //Move push_back
    void push_back(T &&value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        arr[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size_;
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
        while (size_ > 0) {
            pop_back();
        }
        size_ = 0;
    }
};
#endif
