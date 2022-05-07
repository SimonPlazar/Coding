#include <iostream>
#include <memory>
#include "SmartPointer.h"
#include "Date.h"

int main(){
    std::shared_ptr<Date> datum1(new Date(12, 12, 2022));
    SmartPointer<Date> datum2(new Date(11, 12, 2022));

    std::cout << datum1->toString()<<std::endl;

    std::cout << *datum2<<std::endl;

    if(*datum1==*datum2)
        std::cout << "enaka!"<<std::endl;
    else
        std::cout << "razlicna!"<<std::endl;

    if(*datum1==(*datum2)++)
        std::cout << "enaka!"<<std::endl;
    else
        std::cout << "razlicna!"<<std::endl;

    if(*datum1==++(*datum2))
        std::cout << "enaka!"<<std::endl;
    else
        std::cout << "razlicna!"<<std::endl;

    return 0;
}
