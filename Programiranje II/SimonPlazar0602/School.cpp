//
// Created by simon on 03/04/2022.
//

#include "School.h"
#include <utility>
#include <sstream>
#include <iostream>

School::School(std::string name) : name(std::move(name)) {
}

void School::addTeacher(Person *teacher) {
    teachers.push_back(teacher);
}

void School::addStudent(Person *student) {
    students.push_back(student);
}

std::string School::toString() const {
    std::stringstream ss;
    ss << name << "\nTeachers:\n";

    for (auto teacher: teachers) ss << teacher->toString() << std::endl;

    ss << "\nStudents:\n";

    for (auto student: students) ss << student->toString() << std::endl;

    return ss.str();
}

void School::print() const {
    std::cout << toString();
}


