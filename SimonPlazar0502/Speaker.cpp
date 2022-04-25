//
// Created by simon on 25/03/2022.
//

#include "Speaker.h"

Speaker::Speaker(std::string id, std::string name, int power) : Device(std::move(id), std::move(name)),
                                                                  power(power) {
}

std::string Speaker::toString() const {
    return Device::toString() + " " + std::to_string(power) + "W";
}
