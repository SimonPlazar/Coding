//
// Created by simon on 25/04/2022.
//

#ifndef SIMONPLAZAR0801_SPARSEMATRIX2D_H
#define SIMONPLAZAR0801_SPARSEMATRIX2D_H

#include <vector>
#include "Element.h"

template<typename T>
class SparseMatrix2D {
private:
    std::vector<Element<T>> elements;
    unsigned int sizeX;
    unsigned int sizeY;
    T defaultElement;
public:
    SparseMatrix2D(unsigned int sizeX, unsigned int sizeY, T defaultElement);

    void set(unsigned int x, unsigned int y, T value);

    Element<T> at(unsigned int x, unsigned int y) const;

    unsigned int getSizeX() const;

    unsigned int getSizeY() const;

    void clearRow(unsigned int row);
};

template<typename T>
SparseMatrix2D<T>::SparseMatrix2D(unsigned int sizeX, unsigned int sizeY, T defaultElement) :
        sizeX(sizeX),
        sizeY(sizeY),
        defaultElement(defaultElement) {}

template<typename T>
void SparseMatrix2D<T>::set(unsigned int x, unsigned int y, T value) {
    if(x >= sizeX || y >= sizeY){
        std::cout<<"Izven matrice!\n";
        return;
    }

    for (int i = 0; i < elements.size(); ++i) {
        if (elements[i].getX() == x && elements[i].getY() == y) {
            elements[i].setValue(value);
            return;
        }
    }
    elements.push_back(Element<T>(x, y, value));
}

template<typename T>
Element<T> SparseMatrix2D<T>::at(unsigned int x, unsigned int y) const {
    for (int i = 0; i < elements.size(); ++i)
        if (elements[i].getX() == x && elements[i].getY() == y)
            return elements[i];
    return Element<T>(x, y, T());
}

template<typename T>
unsigned int SparseMatrix2D<T>::getSizeX() const {
    return sizeX;
}

template<typename T>
unsigned int SparseMatrix2D<T>::getSizeY() const {
    return sizeY;
}

template<typename T>
void SparseMatrix2D<T>::clearRow(unsigned int row) {
    for (int i = 0; i < elements.size(); ++i) {
        if(elements[i].getX() == row){
            elements.erase(elements.begin()+i);
            i--;
        }
    }
}


#endif //SIMONPLAZAR0801_SPARSEMATRIX2D_H
