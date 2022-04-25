//
// Created by simon on 03/04/2022.
//

#ifndef SIMONPLAZAR0602_PERSON_H
#define SIMONPLAZAR0602_PERSON_H


#include <string>

class Person {
protected:
    std::string name;
    std::string surname;
    unsigned int age;
public:
    Person(std::string name, std::string surname, unsigned int age);

    virtual std::string toString() const  = 0;

    virtual void print() const = 0;
};


#endif //SIMONPLAZAR0602_PERSON_H
