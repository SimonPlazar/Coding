//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0502_SMARTHOME_H
#define SIMONPLAZAR0502_SMARTHOME_H

#include <string>
#include <vector>
#include "Device.h"

class SmartHome {
private:
    std::string name;
    std::vector<Device *> devices;
public:
    explicit SmartHome(std::string name);

    ~SmartHome();

    void addDevice(Device *device);

    std::string toString() const;

};


#endif //SIMONPLAZAR0502_SMARTHOME_H
