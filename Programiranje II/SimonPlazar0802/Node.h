//
// Created by simon on 25/04/2022.
//

#ifndef SIMONPLAZAR0802_NODE_H
#define SIMONPLAZAR0802_NODE_H

template<typename T>
class Node {
private:
    T value;
    Node *next;
public:
    Node() = default;

    explicit Node(T value);

    T getValue() const;

    Node *getNext() const;

    void setValue(T value);

    void setNext(Node *next);
};

template<typename T>
Node<T>::Node(T value) : value(value), next(nullptr){}

template<typename T>
T Node<T>::getValue() const {
    return value;
}

template<typename T>
Node<T> *Node<T>::getNext() const {
    return next;
}

template<typename T>
void Node<T>::setValue(T value) {
    Node::value = value;
}

template<typename T>
void Node<T>::setNext(Node *next) {
    Node::next = next;
}

#endif //SIMONPLAZAR0802_NODE_H
