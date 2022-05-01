//
// Created by simon on 29/03/2022.
//

#include "Dimension.h"

Dimension::Dimension(double width, double height, double depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}

std::string Dimension::toString() const {
    return std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth);
}