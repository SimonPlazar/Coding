//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0602_SCHOOL_H
#define SIMONPLAZAR0602_SCHOOL_H


#include <vector>
#include "Person.h"

class School {
private:
    std::string name;
    std::vector<Person*> teachers;
    std::vector<Person*> students;
public:
    explicit School(std::string name);

    void addTeacher(Person* teacher);

    void addStudent(Person* students);

    std::string toString() const;

    void print() const;
};



#endif //SIMONPLAZAR0602_SCHOOL_H

/*
abstract class organism
    size
    eats
inherited class animal
    name
    food...
inherited class plant
    name
    food
    lifespan..

class habitat
    name
    place
    multiple organisms

*/