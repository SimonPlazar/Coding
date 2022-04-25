//
// Created by simon on 03/04/2022.
//

#include "Circle.h"
#include "PrintUtility.h"
#include <cmath>
#include <iostream>

Circle::Circle(ColorCode color, double radius) : Shape2D(color), radius(radius) {
}

double Circle::getSurfaceArea() const {
    return M_PI * radius * radius;
}

void Circle::draw() const {
    const int r = (int) radius;

    const int width = r;
    const int length = r;

    for (int y = width; y >= -width; y -= 2) {
        for (int x = -length; x <= length; x++) {
            if ((int) sqrt(pow(x, 2) + pow(y, 2)) == r) PrintUtility::print(color,"*");
            else std::cout << " ";
        }
        std::cout << "\n";
    }
}

std::string Circle::toString() const {
    return "r: " + std::to_string(radius) + "\narea: " + std::to_string(getSurfaceArea());
}

double Circle::getCircumference() const {
    return 2*M_PI*radius;
}
