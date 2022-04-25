//
// Created by simon on 05/04/2022.
//

#ifndef SIMONPLAZAR0601_TRIANGLE_H
#define SIMONPLAZAR0601_TRIANGLE_H

#include <string>
#include "Shape2D.h"

class Triangle : public Shape2D{
private:
    double kateta;
public:
    explicit Triangle(ColorCode color, double kateta);

    double getSurfaceArea() const override;

    void draw() const override;

    std::string toString() const;

    double getHypotenuse() const;

    double getCircumference() const override;
};


#endif //SIMONPLAZAR0601_TRIANGLE_H
