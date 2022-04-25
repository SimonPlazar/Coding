//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0502_LIGHT_H
#define SIMONPLAZAR0502_LIGHT_H

#include <string>
#include "Device.h"

class Light : public Device {
private:
    bool turnedOn;

public:
    Light(std::string id, std::string name, bool turnedOn);

    std::string toString() const override;


};


#endif //SIMONPLAZAR0502_LIGHT_H
