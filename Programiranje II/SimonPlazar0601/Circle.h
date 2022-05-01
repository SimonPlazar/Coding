//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0601_CIRCLE_H
#define SIMONPLAZAR0601_CIRCLE_H

#include <string>
#include "Shape2D.h"

class Circle : public Shape2D{
private:
    double radius;
public:
    Circle(ColorCode color, double radius);

    double getSurfaceArea() const override;

    void draw() const override;

    std::string toString() const;

    double getCircumference() const override;
};


#endif //SIMONPLAZAR0601_CIRCLE_H
