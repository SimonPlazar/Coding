//
// Created by simon on 10/05/2022.
//

#ifndef SIMONPLAZAR0901_STAROST_H
#define SIMONPLAZAR0901_STAROST_H


#include <sstream>
#include "Date.h"

class Starost {
private:
    Date dateOfBirth;
    int age;
public:
    Starost(Date dateOfBirth, int age);

    Starost operator--(int dummy);

    friend std::ostream &operator<<(std::ostream &out, const Starost &starost);

    const Date &getDateOfBirth() const;

    int getAge() const;
};

Starost::Starost(Date dateOfBirth, int age) : dateOfBirth(dateOfBirth), age(age) {}

Starost Starost::operator--(int dummy) {
    Starost old = *this;
    age--;
    return old;
}

std::ostream &operator<<(std::ostream &out, const Starost &starost) {
    std::stringstream ss;

    ss << starost.dateOfBirth.toString() << " " << starost.age;

    out << ss.str();

    return out;
}

const Date &Starost::getDateOfBirth() const {
    return dateOfBirth;
}

int Starost::getAge() const {
    return age;
}


#endif //SIMONPLAZAR0901_STAROST_H
