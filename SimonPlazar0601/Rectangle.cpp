//
// Created by simon on 03/04/2022.
//

#include <iostream>
#include "Rectangle.h"
#include "PrintUtility.h"

Rectangle::Rectangle(ColorCode color, double width, double height) : Shape2D(color), width(width), height(height) {
}

double Rectangle::getSurfaceArea() const {
    return width * height;
}

void Rectangle::draw() const {
    for (int i = 0; i < width; ++i) {
        PrintUtility::print(color, (unsigned int) height);
        std::cout << std::endl;
    }
}

std::string Rectangle::toString() const {
    return std::to_string(width) + " * " + std::to_string(height);
}

double Rectangle::getCircumference() const {
    return 2 * width + 2 * height;
}
