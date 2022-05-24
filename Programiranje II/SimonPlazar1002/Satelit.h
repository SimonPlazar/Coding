//
// Created by simon on 24/05/2022.
//

#ifndef SIMONPLAZAR1002_SATELIT_H
#define SIMONPLAZAR1002_SATELIT_H


#include <string>

class Satelit {
protected:
    unsigned int visina;
    unsigned int masa;

public:
    Satelit(unsigned int visina, unsigned int masa);
    virtual std::string toString() const;
};


#endif //SIMONPLAZAR1002_SATELIT_H
