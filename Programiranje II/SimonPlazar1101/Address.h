//
// Created by simon on 23/05/2022.
//

#ifndef SIMONPLAZAR1101_ADDRESS_H
#define SIMONPLAZAR1101_ADDRESS_H

#include <string>

class Address {
private:
    std::string street;
    std::string post;
    std::string country;
public:
    Address(std::string street, std::string post, std::string country);

    std::string toString() const;
};


#endif //SIMONPLAZAR1101_ADDRESS_H
