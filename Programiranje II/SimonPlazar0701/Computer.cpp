//
// Created by simon on 15/04/2022.
//

#include <sstream>
#include <utility>
#include "Computer.h"

Computer::Computer(std::vector<std::string> components, int power) : components(std::move(components)), power(power) {
}

std::string Computer::toString() const {
    std::stringstream ss;

    ss << "Power: " << power << " W\n";

    if (components.empty()) return ss.str();

    ss << "Components:\n";
    for (const auto &component: components) {
        ss << component << ",\n";
    }

    return ss.str();
}

const std::vector<std::string> &Computer::getComponents() const {
    return components;
}

int Computer::getPower() const {
    return power;
}

void Computer::setComponents(const std::vector<std::string> &x) {
    Computer::components = x;
}

void Computer::setPower(int x) {
    Computer::power = x;
}
