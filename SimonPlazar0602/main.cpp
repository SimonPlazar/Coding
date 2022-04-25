#include <iostream>
#include "School.h"
#include "Student.h"
#include "Teacher.h"

void printMenu(){
    std::cout<<"\nMenu:\n"
             <<"(1) Add student\n"
             <<"(2) Add teacher\n"
             <<"(3) Print school\n"
             <<"(4) End\n"
             <<"Choice:";
}

void addStudent(School &s){
    std::string val1;
    std::string val2;
    std::string val3;

    int val4;

    std::cout<<"Set name:";
    std::cin>>val1;

    std::cout<<"Set surname:";
    std::cin>>val2;

    std::cout<<"Set age:";
    std::cin>>val4;

    std::cout<<"Set id:";
    std::cin>>val3;

    s.addStudent(new Student(val1, val2, val4, val3));
}

void addTeacher(School &s){
    std::string val1;
    std::string val2;
    std::string val3;

    int val4;
    int choice;

    std::cout<<"Set name:";
    std::cin>>val1;

    std::cout<<"Set surname:";
    std::cin>>val2;

    std::cout<<"Set age:";
    std::cin>>val4;

    std::cout<<"Set id:";
    std::cin>>val3;

    auto teacher = new Teacher(val1, val2, val4, val3);

    do {
        std::cout<<"Do you want to add a course? (1)Yes (2)No\nChoice:";
        std::cin>>choice;

        if(choice == 1) {
            std::cout<<"Set course:";
            std::cin>>val1;
            teacher->addCourse(val1);
        }
    } while (choice == 1);

    s.addTeacher(teacher);
}

int main() {
    std::string val1;
    std::string val2;
    std::string val3;

    int choice;
    int choice2;
    int val4;

    School s("Ljudski vrt");

    do {
        printMenu();
        std::cin>>choice;
        std::cout<<std::endl;

        switch (choice) {
            case 1:
                addStudent(s);
                break;
            case 2:
                addTeacher(s);
                break;
            case 3:
                s.print();
                break;
            case 4:
                break;
            default:
                std::cout<<"Wrong choice!\n";
                break;
        }
    }while(choice != 4);

    return 0;
}
