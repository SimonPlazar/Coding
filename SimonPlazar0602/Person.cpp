//
// Created by simon on 03/04/2022.
//

#include "Person.h"

#include <utility>
#include <iostream>

Person::Person(std::string name, std::string surname, unsigned int age) : name(std::move(name)), surname(std::move(surname)), age(age){
}

/*
std::string Person::toString() const {
    return name + " " + surname + " " + std::to_string(age);
}

void Person::print() const {
    std::cout<<toString();
}
*/