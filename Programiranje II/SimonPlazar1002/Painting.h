//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0501_PAINTING_H
#define SIMONPLAZAR0501_PAINTING_H

#include "Artwork.h"

enum class PaintingTechnique{Oil, Acrylic, Graphite};

class Painting : public Artwork{
private:
    PaintingTechnique technique;

public:
    Painting(std::string title, std::string description, double price, int year, std::shared_ptr<Artist> artist, PaintingTechnique technique);
    std::string toString() const override;
    void print() const override;
};


#endif //SIMONPLAZAR0501_PAINTING_H
