//
// Created by simon on 25/04/2022.
//

#ifndef SIMONPLAZAR0801_ELEMENT_H
#define SIMONPLAZAR0801_ELEMENT_H

template<typename T>
class Element {
private:
    unsigned int x;
    unsigned int y;
    T value;
public:
    Element(unsigned int x, unsigned int y, T value);

    unsigned int getX() const;

    unsigned int getY() const;

    T getValue() const;

    void setX(unsigned int x);

    void setY(unsigned int y);

    void setValue(T value);
};

template<typename T>
Element<T>::Element(unsigned int x, unsigned int y, T value) : x(x), y(y), value(value) {
}

template<typename T>
unsigned int Element<T>::getX() const {
    return x;
}

template<typename T>
unsigned int Element<T>::getY() const {
    return y;
}

template<typename T>
T Element<T>::getValue() const {
    return value;
}

template<typename T>
void Element<T>::setX(unsigned int x) {
    Element::x = x;
}

template<typename T>
void Element<T>::setY(unsigned int y) {
    Element::y = y;
}

template<typename T>
void Element<T>::setValue(T value) {
    Element::value = value;
}

#endif //SIMONPLAZAR0801_ELEMENT_H
