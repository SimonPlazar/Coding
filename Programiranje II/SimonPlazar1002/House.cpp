//
// Created by simon on 15/05/2022.
//

#include "House.h"
#include <utility>
#include <iostream>

House::House(std::string naslov, double area) : naslov(std::move(naslov)), area(area) {}

std::string House::toString() const {
    return naslov + " " + std::to_string(area) + "m2";
}

void House::print() const {
    std::cout << toString();
}

