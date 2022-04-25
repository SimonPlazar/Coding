//
// Created by simon on 25/04/2022.
//

#ifndef SIMONPLAZAR0802_LINKEDLIST_H
#define SIMONPLAZAR0802_LINKEDLIST_H

#include <iostream>
#include "Node.h"

template<typename T>
class LinkedList {
private:
    Node<T> *head;
public:
    LinkedList();

    bool isEmpty() const;

    unsigned int getSize() const;

    void add(T value);

    T at(unsigned int index) const;

    Node<T>* getHead() const;

    void deleteList(Node<T>* node);

    void print() const;

    ~LinkedList();
};

template<typename T>
bool LinkedList<T>::isEmpty() const {
    if (head == nullptr) return true;
    else return false;
}

template<typename T>
unsigned int LinkedList<T>::getSize() const {
    Node<T>* current(head);

    unsigned int i;
    for (i = 0; current != nullptr; ++i) {
        current = current->getNext();
    }
    return i;
}

template<typename T>
void LinkedList<T>::add(T value) {
    Node<T>* newNode = new Node(value);

    if(head == nullptr)
        head = newNode;
    else{
        Node<T>* tmp = head;
        while (tmp->getNext() != nullptr) {
            tmp = tmp->getNext();
        }
        tmp->setNext(newNode);
    }
}

template<typename T>
T LinkedList<T>::at(unsigned int index) const {
    if(index > getSize()) return T();

    Node<T>* current(head);

    for (int i = 0; i < index; ++i) {
        current = current->getNext();
    }
    return current->getValue();
}

template<typename T>
LinkedList<T>::~LinkedList() {
    deleteList(head);
}

template<typename T>
Node<T> *LinkedList<T>::getHead() const {
    return head;
}

template<typename T>
void LinkedList<T>::deleteList(Node<T>* node) {
    if(node == nullptr) return;
    deleteList(node->getNext());
    delete node;
}

template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

template<typename T>
void LinkedList<T>::print() const {
    Node<T>* tmp = head;

    while (tmp != nullptr){
        std::cout<<tmp->getValue()<<" ";
        tmp = tmp->getNext();
    }
}

#endif //SIMONPLAZAR0802_LINKEDLIST_H
