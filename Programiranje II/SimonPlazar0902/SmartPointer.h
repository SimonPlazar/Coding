//
// Created by simon on 07/05/2022.
//

#ifndef SIMONPLAZAR0901_SMARTPOINTER_H
#define SIMONPLAZAR0901_SMARTPOINTER_H

#include "ReferenceCounter.h"

template<typename T>
class SmartPointer {
private:
    T *pointer;
    ReferenceCounter *counter;
public:
    explicit SmartPointer(T *pointer);

    ~SmartPointer();

    SmartPointer(const SmartPointer &other);

    T &operator*() const;

    T *operator->();

    SmartPointer<T> &operator=(const SmartPointer<T> &other);

    int useCount() const;
};

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) : pointer(pointer), counter(new ReferenceCounter()) {
    (*counter)++;
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    if (--(*counter) == 0){
        free(pointer);
        free(counter);
    }

}

template<typename T>
T &SmartPointer<T>::operator*() const {
    return *pointer;
}

template<typename T>
T *SmartPointer<T>::operator->() {
    return pointer;
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &other) {
    //ce je isiti objekt
    if (this == &other) return *this;

    //ce idini kaze na ta objekt (izbrise ga)
    if (--(*counter) == 0) {
        free(pointer);
        free(counter);
    }

    //prekopira vrednosti
    pointer = other.pointer;
    counter = other.counter;
    (*counter)++;

    return *this;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer &other) {
    //ce je isiti objekt
    if (this == &other) return;

    //ce idini kaze na ta objekt (izbrise ga)
    if (--(*counter) == 0) {
        free(pointer);
        free(counter);
    }

    //prekopira vrednosti
    pointer = other.pointer;
    counter = other.counter;
    (*counter)++;
}

template<typename T>
int SmartPointer<T>::useCount() const {
    return counter->getCount();
}


#endif //SIMONPLAZAR0901_SMARTPOINTER_H
