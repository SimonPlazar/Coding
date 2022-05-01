//
// Created by simon on 29/03/2022.
//

#ifndef SIMONPLAZAR0502_VENTILATIONSYSTEM_H
#define SIMONPLAZAR0502_VENTILATIONSYSTEM_H

#include "Device.h"

class VentilationSystem : public Device{
private:
    int startHour;
    int endHour;
public:
    VentilationSystem(std::string id, std::string name, int startHour, int endHour);
    std::string toString() const override;
};


#endif //SIMONPLAZAR0502_VENTILATIONSYSTEM_H
