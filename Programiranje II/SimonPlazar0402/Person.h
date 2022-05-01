#ifndef SIMONPLAZAR0402_PERSON_H
#define SIMONPLAZAR0402_PERSON_H


#include <string>

class Person {
private:
    std::string firstName;
    std::string lastName;
public:
    Person(std::string firstName, std::string lastName);
    std::string toString() const;
};


#endif //SIMONPLAZAR0402_PERSON_H
