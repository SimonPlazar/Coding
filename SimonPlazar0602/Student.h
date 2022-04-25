//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0602_STUDENT_H
#define SIMONPLAZAR0602_STUDENT_H

#include <vector>
#include "Person.h"

class Student : public Person{
private:
    std::string studentID;
public:
    Student(std::string name, std::string surname, unsigned int age, std::string studentID);

    std::string toString() const override;

    void print() const override;
};


#endif //SIMONPLAZAR0602_STUDENT_H
