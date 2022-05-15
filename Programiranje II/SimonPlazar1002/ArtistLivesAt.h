//
// Created by simon on 15/05/2022.
//

#ifndef SIMONPLAZAR1002_ARTISTLIVESAT_H
#define SIMONPLAZAR1002_ARTISTLIVESAT_H

#include "Artist.h"
#include "House.h"

class ArtistLivesAt : public Artist, public House {
private:
    std::string houseType;
    int yearsOfResidency;
public:
    ArtistLivesAt(std::string houseType, int yearsOfResidency,
                  std::string name, std::string biography, Date dateOfBirth,
                  std::string naslov, double area
    );

    std::string toString() const override;

    void print() const;

};


#endif //SIMONPLAZAR1002_ARTISTLIVESAT_H
