//
// Created by simon on 03/04/2022.
//

#include <iostream>
#include "Canvas.h"

void Canvas::addShape(Shape2D *shape) {
    shapes.push_back(shape);
}

void Canvas::print() const {
    for (auto shape: shapes) {
        shape->draw();
        std::cout << std::endl;
    }
}

Canvas::~Canvas() {
    for (auto &shape: shapes) delete shape;
}

void Canvas::drawColor(ColorCode color) const {
    for (int i = 0; i < shapes.size(); ++i) {
        if(shapes[i]->getColor() == color) {
            shapes[i]->draw();
            std::cout<< std::endl;
        }
    }
}
