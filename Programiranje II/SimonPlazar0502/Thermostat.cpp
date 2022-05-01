//
// Created by simon on 25/03/2022.
//

#include "Thermostat.h"

#include <utility>
#include <sstream>
#include <cmath>
#include <iomanip>

Thermostat::Thermostat(std::string id, std::string name) : Device(std::move(id), std::move(name)) {
}

std::string Thermostat::toString() const {
    std::stringstream ss;

    ss << Device::toString();
    for (int i = 0; i < 4 ; ++i) {
        if(!std::isnan(temps[i])){
            ss << std::endl;
            switch (i) {
                case 0:
                    ss<< "Bathroom: ";
                    break;
                case 1:
                    ss<< "Living room: ";
                    break;
                case 2:
                    ss<< "Kitchen: ";
                    break;
                case 3:
                    ss<< "Office: ";
                    break;
                default:
                    break;
            }
            ss << std::fixed << std::setprecision(2) << temps[i];
        }
    }

    return ss.str();
}

void Thermostat::setTemp(Rooms room, double temp) {
    temps[static_cast<int>(room)] = temp;
}

