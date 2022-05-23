//
// Created by simon on 23/05/2022.
//

#include "Student.h"
#include "InvalidFile.h"
#include "Log.h"
#include <utility>
#include <sstream>

Student::Student(unsigned int id, std::string name, std::string surname, Date dateOfBirth, Address address) :
        id(id), name(std::move(name)), surname(std::move(surname)), dateOfBirth(dateOfBirth),
        address(std::move(address)) {}

std::string Student::toString() const {
    std::stringstream ss;

    ss << id << "," << name << "," << surname << "," << dateOfBirth.toString() << "," << address.toString();

    return ss.str();
}

std::vector<std::shared_ptr<Student>> Student::LoadFromFile(const std::string &fileName) {
    std::vector<std::shared_ptr<Student>> studenti;

    std::ifstream file(fileName);

    try {
        if (!file.is_open()) throw InvalidFile(fileName);
    } catch (InvalidFile &exception) {
        Log(LogType::ERROR) << exception.what()<<"\n";
        return {};
    }

    while (!file.eof()) {
        std::vector<std::string> studentRow;
        std::string line;
        std::getline(file, line);

        std::istringstream seperatedStudent(line);

        while (seperatedStudent.good()) {
            std::string substr;
            getline(seperatedStudent, substr, ',');
            studentRow.push_back(substr);
        }

        studenti.push_back(std::make_shared<Student>(std::stoi(studentRow[0]),
                                                     studentRow[1],
                                                     studentRow[2],
                                                     Date::GetDateFromString(studentRow[3]),
                                                     Address(studentRow[4], studentRow[5], studentRow[6])
        ));
    }
    file.close();

    return studenti;
}

void Student::SaveToFile(const std::vector<std::shared_ptr<Student>> &students, const std::string &fileName) {
    std::ofstream file(fileName);

    try {
        if (!file.is_open()) throw InvalidFile(fileName);
    } catch (InvalidFile &exception) {
        Log(LogType::ERROR) << exception.what() << "\n";
        return;
    }

    for (const auto &student: students) file << student->toString() << std::endl;

    file.close();
}