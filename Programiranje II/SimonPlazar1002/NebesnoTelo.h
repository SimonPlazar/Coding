//
// Created by simon on 24/05/2022.
//

#ifndef SIMONPLAZAR1002_NEBESNOTELO_H
#define SIMONPLAZAR1002_NEBESNOTELO_H

#include <string>

class NebesnoTelo {
protected:
    std::string ime;
    unsigned int masa;

public:
    NebesnoTelo(std::string ime, unsigned int masa);
    virtual std::string toString() const;
};


#endif //SIMONPLAZAR1002_NEBESNOTELO_H
