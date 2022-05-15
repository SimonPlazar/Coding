//
// Created by simon on 25/03/2022.
//

#include <sstream>
#include <utility>
#include <iostream>
#include "Painting.h"

Painting::Painting(std::string title, std::string description, double price, int year, std::shared_ptr<Artist> artist,PaintingTechnique technique) :
                   Artwork(std::move(title),std::move(description), price, year, std::move(artist)), technique(technique){
}

std::string Painting::toString() const {
    std::stringstream ss;

    switch (technique) {
        case PaintingTechnique::Oil:
            ss << "Oil, ";
            break;
        case PaintingTechnique::Acrylic:
            ss << "Acrylic, ";
            break;
        case PaintingTechnique::Graphite:
            ss << "Graphite, ";
            break;
    }

    ss << Artwork::toString();

    return ss.str();
}

void Painting::print() const {
    std::cout<<toString()<<std::endl;
}


