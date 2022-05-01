#include <iostream>
#include "Canvas.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

int main() {
    using std::operator""s;
    system(("chcp "s + std::to_string(65001)).c_str());

    Canvas c;
    c.addShape(new Rectangle(ColorCode::Green, 2, 5));
    c.addShape(new Rectangle(ColorCode::Blue, 5, 10));

    c.addShape(new Circle(ColorCode::Green, 8));
    c.addShape(new Circle(ColorCode::Blue, 7));

    c.addShape(new Triangle(ColorCode::Red, 8));

    c.print();

    c.drawColor(ColorCode::Green);

    return 0;
}
