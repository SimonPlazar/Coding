#include <iostream>
#include "Date.h"
#include "Student.h"
#include "UnparseableDateException.h"
#include "WrongDateException.h"

int main() {
    try {
        Date::GetDateFromString(Date(10,10,2022).toString()).print();
        Date::GetDateFromString("12.1o.2022").print();
        Date::GetDateFromString("33.12.2022").print();
    }catch (UnparseableDateException &exception) {
        std::cout<<exception.what()<<std::endl;
    } catch (WrongDateException &exception){
        std::cout<<exception.what()<<std::endl;
    }


    std::vector<std::shared_ptr<Student>> studenti = Student::LoadFromFile("students.csv");

    for (auto & student : studenti) {
        std::cout << student->toString() << std::endl;
    }

    Student::SaveToFile(studenti, "output.txt");

    Student::SaveToFile(Student::LoadFromFile("students.csv"), "output2.txt");

    return 0;
}
