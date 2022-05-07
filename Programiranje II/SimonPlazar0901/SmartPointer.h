//
// Created by simon on 07/05/2022.
//

#ifndef SIMONPLAZAR0901_SMARTPOINTER_H
#define SIMONPLAZAR0901_SMARTPOINTER_H

template<typename T>
class SmartPointer {
private:
    T *pointer;
public:
    explicit SmartPointer(T *pointer);

    ~SmartPointer();

    T &operator*() const;

    T *operator->();
};

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) : pointer(pointer) {}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    free(pointer);
}

template<typename T>
T &SmartPointer<T>::operator*() const {
    return *pointer;
}

template<typename T>
T *SmartPointer<T>::operator->() {
    return pointer;
}

#endif //SIMONPLAZAR0901_SMARTPOINTER_H
