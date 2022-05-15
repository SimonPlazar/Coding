//
// Created by simon on 29/03/2022.
//

#ifndef SIMONPLAZAR0501_SCULPTURE_H
#define SIMONPLAZAR0501_SCULPTURE_H

#include "Artwork.h"

enum class Material {
    Wood,
    Stone,
    Metal,
    Clay
};

class Sculpture : public Artwork {
private:
    double weight;
    Material material;
public:
    Sculpture(std::string title,
              std::string description,
              double price,
              int year,
              std::shared_ptr<Artist> artist,
              double weight,
              Material material);

    std::string toString() const override;

    void print() const override;
};


#endif //SIMONPLAZAR0501_SCULPTURE_H
