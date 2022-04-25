//
// Created by simon on 25/03/2022.
//

#include "Device.h"

#include <utility>

Device::Device(std::string id, std::string name) : id(std::move(id)), name(std::move(name)){
}

std::string Device::toString() const {
    return id+" "+name;
}
