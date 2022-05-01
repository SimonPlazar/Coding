//
// Created by simon on 03/04/2022.
//

#include "Shape2D.h"

Shape2D::Shape2D(ColorCode color) : color(color){
}

ColorCode Shape2D::getColor() const {
    return color;
}
