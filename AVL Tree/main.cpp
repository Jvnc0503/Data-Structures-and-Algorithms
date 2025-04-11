#include <iostream>
#include "AVL.h"

int main() {
    AVL<int> tree;

    tree.insert(50, 60, 70);
    tree.BFS();

    tree.insert(10, 20, 30);
    tree.BFS();

    tree.insert(40, 90, 80);
    tree.BFS();
    return 0;
}
