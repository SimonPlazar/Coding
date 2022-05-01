//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0602_TEACHER_H
#define SIMONPLAZAR0602_TEACHER_H

#include <vector>
#include "Person.h"

class Teacher : public Person {
private:
    std::string teacherID;
    std::vector<std::string> courses;

public:
    Teacher(std::string name, std::string surname, unsigned int age, std::string teacherID);

    void addCourse(const std::string& course);

    std::string toString() const override;

    void print() const override;
};


#endif //SIMONPLAZAR0602_TEACHER_H
