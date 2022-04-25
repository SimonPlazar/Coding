//
// Created by simon on 03/04/2022.
//

#include "Student.h"

#include <utility>
#include <sstream>
#include <iostream>

Student::Student(std::string name, std::string surname, unsigned int age, std::string studentID) :
        Person(std::move(name), std::move(surname), age),
        studentID(std::move(studentID)) {
}

std::string Student::toString() const {
    std::stringstream ss;
    ss << name << " " << surname << " " << age << " " << studentID;
    return ss.str();
}

void Student::print() const {
    std::cout << toString();
}
