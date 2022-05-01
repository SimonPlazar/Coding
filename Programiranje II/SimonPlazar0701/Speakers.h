//
// Created by simon on 15/04/2022.
//

#ifndef SIMONPLAZAR0701_SPEAKERS_H
#define SIMONPLAZAR0701_SPEAKERS_H


#include <string>

class Speakers {
private:
    std::string brand;
    double driverSize{};

public:
    Speakers() = default;

    Speakers(std::string brand, double driverSize);

    std::string toString() const;

    const std::string &getBrand() const;

    double getDriverSize() const;

    void setBrand(const std::string &x);

    void setDriverSize(int x);
};


#endif //SIMONPLAZAR0701_SPEAKERS_H
