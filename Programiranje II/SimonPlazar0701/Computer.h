//
// Created by simon on 15/04/2022.
//

#ifndef SIMONPLAZAR0701_COMPUTER_H
#define SIMONPLAZAR0701_COMPUTER_H

#include <vector>
#include <string>

class Computer {
private:
    std::vector<std::string> components;
    int power{};

public:
    Computer() = default;

    Computer(std::vector<std::string> components, int power);

    std::string toString() const;

    const std::vector<std::string> &getComponents() const;

    int getPower() const;

    void setComponents(const std::vector<std::string> &x);

    void setPower(int x);
};


#endif //SIMONPLAZAR0701_COMPUTER_H
