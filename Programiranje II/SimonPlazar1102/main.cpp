#include <iostream>
#include "Date.h"
#include "Student.h"

int main() {
    Date::GetDateFromString(Date(12,10,2022).toString()).print();
    Date::GetDateFromString("12.1o.2022").print();

    Date::GetDateFromString(Date(44,13,2022).toString()).print();
    Date::GetDateFromString("12.10/2022").print();

    std::vector<std::shared_ptr<Student>> studenti = Student::LoadFromFile("students.csv");

    for (auto & student : studenti) {
        std::cout << student->toString() << std::endl;
    }

    Student::SaveToFile(studenti, "output.txt");

    Student::SaveToFile(Student::LoadFromFile("2students.csv"), "output2.txt");

    return 0;
}
