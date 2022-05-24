//
// Created by simon on 24/05/2022.
//

#include "Satelit.h"

Satelit::Satelit(unsigned int visina, unsigned int masa) : visina(visina), masa(masa) {}

std::string Satelit::toString() const {
    return std::to_string(visina) + " " + std::to_string(masa)+ "M Kg";
}
