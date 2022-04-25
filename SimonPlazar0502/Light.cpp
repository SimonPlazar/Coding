//
// Created by simon on 25/03/2022.
//

#include "Light.h"

#include <utility>

Light::Light(std::string id, std::string name, bool turnedOn) : Device(std::move(id), std::move(name)),
                                                                turnedOn(turnedOn) {
}

std::string Light::toString() const {
    if (turnedOn) return id + " " + name + " ON";
    else return Device::toString() + " OFF";
}
