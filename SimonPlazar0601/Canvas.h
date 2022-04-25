//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0601_CANVAS_H
#define SIMONPLAZAR0601_CANVAS_H


#include <vector>
#include "Shape2D.h"

class Canvas {
private:
    std::vector<Shape2D *> shapes;
public:
    void addShape(Shape2D *shape);

    void print() const;

    ~Canvas();

    void drawColor(ColorCode color) const;
};


#endif //SIMONPLAZAR0601_CANVAS_H
