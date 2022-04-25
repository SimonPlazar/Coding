//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0502_THERMOSTAT_H
#define SIMONPLAZAR0502_THERMOSTAT_H

#include "Device.h"
#include <limits>

enum class Rooms {
    Bathroom, Living_room, Kitchen, Office
};

class Thermostat : public Device {
private:
    double temps[4]{std::numeric_limits<double>::quiet_NaN(),
                    std::numeric_limits<double>::quiet_NaN(),
                    std::numeric_limits<double>::quiet_NaN(),
                    std::numeric_limits<double>::quiet_NaN()};

public:
    Thermostat(std::string id, std::string name);

    std::string toString() const override;

    void setTemp(Rooms room, double temp);
};


#endif //SIMONPLAZAR0502_THERMOSTAT_H
