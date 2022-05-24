#include <iostream>
#include "Date.h"
#include "Student.h"
#include "InvalidFile.h"
#include "Log.h"

int main() {
    std::vector<std::shared_ptr<Student>> studenti;

    try {
        studenti = Student::LoadFromFile("students.csv");
    } catch (InvalidFile &exception) {
        Log(LogType::ERROR) << exception.what()<<"\n";
        studenti = {};
    }


    for (auto & student : studenti) {
        std::cout << student->toString() << std::endl;
    }

    try {
        Student::SaveToFile(studenti, "output.txt");
        Student::SaveToFile(Student::LoadFromFile("2students.csv"), "output2.txt");
    } catch (InvalidFile &exception) {
        Log(LogType::ERROR) << exception.what()<<"\n";
        studenti = {};
    }

    return 0;
}
