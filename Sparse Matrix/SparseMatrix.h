#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

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
};


#endif
