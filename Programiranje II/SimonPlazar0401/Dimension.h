//
// Created by simon on 29/03/2022.
//

#ifndef SIMONPLAZAR0401_DIMENSION_H
#define SIMONPLAZAR0401_DIMENSION_H


#include <string>

class Dimension {
private:
    double width;
    double height;
    double depth;
public:
    Dimension(double width, double height, double depth);
    std::string toString() const;
};


#endif //SIMONPLAZAR0401_DIMENSION_H
