//
// Created by simon on 15/05/2022.
//

#ifndef SIMONPLAZAR1002_HOUSE_H
#define SIMONPLAZAR1002_HOUSE_H

#include <string>

class House {
protected:
    std::string naslov;
    double area;
public:
    House(std::string naslov, double area);

    virtual std::string toString() const;

    virtual void print() const;
};


#endif //SIMONPLAZAR1002_HOUSE_H
