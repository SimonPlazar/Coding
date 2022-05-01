//
// Created by simon on 29/03/2022.
//

#include "VentilationSystem.h"

#include <utility>

VentilationSystem::VentilationSystem(std::string id, std::string name, int startHour, int endHour) :
                Device(std::move(id), std::move(name)),
                startHour(startHour), endHour(endHour)
{

}

std::string VentilationSystem::toString() const {
    return Device::toString() + " " + std::to_string(startHour) + " - " + std::to_string(endHour);
}
