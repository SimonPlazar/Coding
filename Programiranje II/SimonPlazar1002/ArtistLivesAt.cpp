//
// Created by simon on 15/05/2022.
//

#include "ArtistLivesAt.h"
#include <utility>
#include <iostream>
#include <sstream>

ArtistLivesAt::ArtistLivesAt(std::string houseType, int yearsOfResidency, std::string name, std::string biography,
                             Date dateOfBirth, std::string naslov, double area) :
        houseType(std::move(houseType)), yearsOfResidency(yearsOfResidency),
        Artist(std::move(name), std::move(biography), dateOfBirth),
        House(std::move(naslov), area) {}

std::string ArtistLivesAt::toString() const {
    std::stringstream ss;

    ss << name << " has been living at the " << houseType << " on " << naslov << " for " << yearsOfResidency << " years";

    return ss.str();
}

void ArtistLivesAt::print() const {
    std::cout << toString() << std::endl;
}


