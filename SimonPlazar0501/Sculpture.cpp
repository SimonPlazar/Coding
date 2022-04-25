//
// Created by simon on 29/03/2022.
//

#include <sstream>
#include <iostream>
#include "Sculpture.h"

Sculpture::Sculpture(std::string title, std::string description, double price,
                     int year, Artist *artist, double weight, Material material) :
        Artwork(std::move(title), std::move(description), price, year, artist),
        weight(weight),
        material(material) {

}

std::string Sculpture::toString() const {
    std::stringstream ss;

    ss << "[";

    switch (material) {
        case Material::Wood:
            ss << "Wood, ";
            break;
        case Material::Stone:
            ss << "Stone, ";
            break;
        case Material::Metal:
            ss << "Metal, ";
            break;
        case Material::Clay:
            ss << "Clay, ";
            break;
    }

    ss << weight << "kg, ";

    ss << Artwork::toString();

    return ss.str();
}

void Sculpture::print() const {
    std::cout <<toString();
}
