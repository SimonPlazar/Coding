//
// Created by simon on 25/03/2022.
//

#ifndef SIMONPLAZAR0502_SPEAKER_H
#define SIMONPLAZAR0502_SPEAKER_H

#include <string>
#include "Device.h"

class Speaker : public Device {
private:
    int power;

public:
    Speaker(std::string id, std::string name, int power);

    std::string toString() const override;
};


#endif //SIMONPLAZAR0502_SPEAKER_H
