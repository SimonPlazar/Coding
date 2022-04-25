//
// Created by simon on 15/04/2022.
//

#include <sstream>
#include <utility>
#include "Speakers.h"

Speakers::Speakers(std::string brand, double driverSize) : brand(std::move(brand)), driverSize(driverSize) {
}

std::string Speakers::toString() const {
    std::stringstream ss;

    ss << "Brand: " << brand << std::endl;

    ss << "Driver size: " << driverSize << " inch\n";

    return ss.str();
}

const std::string &Speakers::getBrand() const {
    return brand;
}

double Speakers::getDriverSize() const {
    return driverSize;
}

void Speakers::setBrand(const std::string &x) {
    Speakers::brand = x;
}

void Speakers::setDriverSize(int x) {
    Speakers::driverSize = x;
}
