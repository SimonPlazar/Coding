//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0601_SHAPE2D_H
#define SIMONPLAZAR0601_SHAPE2D_H

#include "ColorCode.h"

class Shape2D {
protected:
    ColorCode color;

public:
    explicit Shape2D(ColorCode color);

    virtual double getSurfaceArea() const = 0;

    virtual void draw() const = 0;

    virtual double getCircumference() const = 0;

    ColorCode getColor() const;
};


#endif //SIMONPLAZAR0601_SHAPE2D_H
