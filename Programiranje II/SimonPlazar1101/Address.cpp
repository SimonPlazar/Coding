//
// Created by simon on 23/05/2022.
//

#include "Address.h"

#include <utility>

Address::Address(std::string street, std::string post, std::string country) :
        street(std::move(street)), post(std::move(post)), country(std::move(country)) {}

std::string Address::toString() const {
    return street + "," + post + "," + country;
}

