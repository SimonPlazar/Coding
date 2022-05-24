//
// Created by simon on 24/05/2022.
//

#include "NebesnoTelo.h"

#include <utility>

NebesnoTelo::NebesnoTelo(std::string ime, unsigned int masa) : ime(std::move(ime)), masa(masa) {}

std::string NebesnoTelo::toString() const {
    return ime + " " + std::to_string(masa) + "M Kg";
}
