//
// Created by simon on 03/04/2022.
//

#include "Teacher.h"

#include <utility>
#include <sstream>
#include <iostream>

Teacher::Teacher(std::string name, std::string surname, unsigned int age, std::string teacherID) :
        Person(std::move(name), std::move(surname), age),
        teacherID(std::move(teacherID)) {
}

void Teacher::addCourse(const std::string &course) {
    courses.push_back(course);
}

std::string Teacher::toString() const {
    std::stringstream ss;
    ss << name << " " << surname << " " << age << " " << teacherID << "\nCourses:\n";
    for (const auto & course : courses) {
        ss << course << std::endl;
    }
    return ss.str();
}

void Teacher::print() const {
    std::cout<<toString();
}
