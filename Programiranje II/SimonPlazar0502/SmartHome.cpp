//
// Created by simon on 25/03/2022.
//

#include "SmartHome.h"
#include <iostream>
#include <utility>
#include <sstream>

SmartHome::SmartHome(std::string name) : name(std::move(name)){
}

SmartHome::~SmartHome() {
    for (auto & device : devices) delete device;
}

void SmartHome::addDevice(Device *device) {
    devices.push_back(device);
}

std::string SmartHome::toString() const {
    std::stringstream ss;
    ss << this->name;
    for (auto & device : devices) {
        ss<<std::endl;
        ss<<device->toString();
    }

    return ss.str();
}

