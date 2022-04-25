//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0502_DEVICE_H
#define SIMONPLAZAR0502_DEVICE_H

#include <string>

class Device {
protected:
    std::string id;
    std::string name;
public:
    Device(std::string id, std::string name);

    virtual std::string toString() const;
};


#endif //SIMONPLAZAR0502_DEVICE_H
