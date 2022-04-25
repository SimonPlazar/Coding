#include "Person.h"

#include <utility>
#include <sstream>

Person::Person(std::string firstName, std::string lastName) : firstName(std::move(firstName)), lastName(std::move(lastName)){
}

std::string Person::toString() const{
    std::stringstream ss;
    ss << this->firstName << " " << this->lastName;
    return ss.str();
}


