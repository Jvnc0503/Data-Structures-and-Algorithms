#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <stdexcept>
#include <vector>

template<typename T>
struct Node {
    T data;
    int pos_row;
    int pos_col;
    Node<T> *next_row = nullptr;
    Node<T> *next_col = nullptr;

    Node(const T &data, const int &pos_row, const int &pos_col) : data(data), pos_row(pos_row), pos_col(pos_col) {
    }
};

template<typename T>
class SparseMatrix {
    std::vector<Node<T> *> rows;
    std::vector<Node<T> *> cols;
    size_t n_rows;
    size_t n_cols;

public:
    SparseMatrix(const size_t &n_rows, const size_t &n_cols)
        : rows(n_rows, nullptr), cols(n_cols, nullptr), n_rows(n_rows),
          n_cols(n_cols) {
    }

    ~SparseMatrix() {
        for (size_t i = 0; i < n_rows; ++i) {
            Node<T> *current = rows[i];
            while (current) {
                const Node<T> *temp = current;
                current = current->next_row;
                delete temp;
            }
        }
    }

    Node<T> *search(const size_t &i, const size_t &j) const {
    }

    void insert(const size_t &i, const size_t &j, const T &value) {
        if (i >= n_rows || j >= n_cols) {
            throw std::out_of_range("Invalid index");
        }
    }
};


#endif
