//
// Created by simon on 05/04/2022.
//

#include "Triangle.h"
#include "PrintUtility.h"
#include <math.h>
#include <iostream>


Triangle::Triangle(ColorCode color, double kateta) : Shape2D(color), kateta(kateta) {
}

double Triangle::getSurfaceArea() const {
    return (kateta*kateta)/2;
}

void Triangle::draw() const {
    for (int i = 1; i <= kateta; ++i){
        PrintUtility::print(color, i);
        std::cout<<std::endl;
    }
}

std::string Triangle::toString() const {
    return "k1,2: " + std::to_string(kateta) + "hyp: " + std::to_string(getHypotenuse()) +
           "\nArea: " + std::to_string(getSurfaceArea()) +
           "\nCircumference: " + std::to_string(getCircumference());
}

double Triangle::getHypotenuse() const {
    return sqrt(kateta * kateta + kateta * kateta);
}

double Triangle::getCircumference() const {
    return 2*kateta+getHypotenuse();
}


