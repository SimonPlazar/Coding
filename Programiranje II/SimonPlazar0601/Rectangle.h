//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0601_RECTANGLE_H
#define SIMONPLAZAR0601_RECTANGLE_H

#include <string>
#include "Shape2D.h"
#include "ColorCode.h"

class Rectangle : public Shape2D {
private:
    double width;
    double height;
public:
    Rectangle(ColorCode color, double width, double height);

    double getSurfaceArea() const override;

    void draw() const override;

    std::string toString() const;

    double getCircumference() const override;
};


#endif //SIMONPLAZAR0601_RECTANGLE_H
