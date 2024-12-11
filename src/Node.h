#ifndef NODE_H
#define NODE_H

#include "Ingredient.h"
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

#endif
