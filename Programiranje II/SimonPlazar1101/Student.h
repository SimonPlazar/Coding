//
// Created by simon on 23/05/2022.
//

#ifndef SIMONPLAZAR1101_STUDENT_H
#define SIMONPLAZAR1101_STUDENT_H

#include <string>
#include <memory>
#include <vector>
#include "Date.h"
#include "Address.h"

class Student {
private:
    unsigned int id;
    std::string name;
    std::string surname;
    Date dateOfBirth;
    Address address;
public:
    Student(unsigned int id,std::string name,std::string surname,Date dateOfBirth,Address address);

    std::string toString() const;

    static std::vector<std::shared_ptr<Student>> LoadFromFile(const std::string &fileName);

    static void SaveToFile(const std::vector<std::shared_ptr<Student>> &students, const std::string &fileName);
};


#endif //SIMONPLAZAR1101_STUDENT_H
