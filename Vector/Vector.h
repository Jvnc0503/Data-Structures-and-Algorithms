#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template<typename T>
class Vector {
    T *arr;
    size_t capacity_;
    size_t size_;

    void init_default() {
        arr = nullptr;
        capacity_ = 0;
        size_ = 0;
    }

public:
    Vector() : arr(new T[1]), capacity_(1), size_(0) {
    }

    explicit Vector(const size_t &n, const T &val = T()): arr(new T[n]), capacity_(n), size_(n) {
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
        other.init_default();
    }

    Vector(const std::initializer_list<T> &init) : arr(new T[init.size()]), capacity_(init.size()), size_(init.size()) {
        size_t i = 0;
        for (const T &val: init) {
            arr[i++] = val;
        }
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
            other.init_default();
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
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                arr[i] = val;
            }
        } else if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                arr[i].~T();
            }
        }
        size_ = new_size;
    }

    template<typename U>
    void push_back(U &&value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        arr[size_++] = std::forward<U>(value);
    }

    template<typename... Ts>
    void push_back(Ts &&... args) {
        (..., push_back(std::forward<Ts>(args)));
    }

    template<typename... Ts>
    void emplace_back(Ts &&... args) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new(arr + size_) T(std::forward<Ts>(args)...);
        ++size_;
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

    void shrink_to_fit() {
        if (size_ < capacity_) {
            T *temp = new T[size_];
            for (size_t i = 0; i < size_; ++i) {
                temp[i] = std::move(arr[i]);
            }
            delete[] arr;
            arr = temp;
            capacity_ = size_;
        }
    }
};
#endif
