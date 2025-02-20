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
    size_t n_rows;
    size_t n_cols;
    std::vector<Node<T> *> rows;
    std::vector<Node<T> *> cols;

public:
    SparseMatrix(const size_t &r, const size_t &c): n_rows(r), n_cols(c), rows(r, nullptr), cols(c, nullptr) {
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

    size_t numRows() const {
        return n_rows;
    }

    size_t numCols() const {
        return n_cols;
    }

    Node<T> *search(const size_t &i, const size_t &j) const {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            return nullptr;
        }
        Node<T> *rowHead = rows[i];
        while (rowHead && rowHead->pos_col < j) {
            rowHead = rowHead->next_col;
        }
        if (rowHead && rowHead->pos_col == j) {
            return rowHead;
        }
        return nullptr;
    }

    void insert(const size_t &i, const size_t &j, const T &value) {
        if (i >= n_rows || j >= n_cols) {
            throw std::out_of_range("Invalid index");
        }
    }
};


#endif
