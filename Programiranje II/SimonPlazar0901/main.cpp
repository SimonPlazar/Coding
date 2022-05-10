#include <iostream>
#include <memory>
#include "SmartPointer.h"
#include "Date.h"
#include "Starost.h"

int main() {
    std::shared_ptr<Date> datum1(new Date(12, 12, 2022));
    SmartPointer<Date> datum2(new Date(11, 12, 2022));

    std::cout << datum1->toString() << std::endl;
    std::cout << *datum2 << std::endl;

    //12 != 11
    if (*datum1 == *datum2)
        std::cout << "enaka!" << std::endl;
    else
        std::cout << "razlicna!" << std::endl;

    //12 = 12
    if (*datum1 == ++(*datum2))
        std::cout << "enaka!" << std::endl;
    else
        std::cout << "razlicna!" << std::endl;

    //12 = 12 -> 13
    if (*datum1 == (*datum2)++)
        std::cout << "enaka!" << std::endl;
    else
        std::cout << "razlicna!" << std::endl;

    std::cout << datum1->toString() << std::endl;
    std::cout << *datum2 << std::endl;

    std::shared_ptr<Starost> starost1(new Starost(Date(1, 1, 2022), 12));
    SmartPointer<Starost> starost2(new Starost(Date(2, 2, 2022), 13));

    std::cout << std::endl << *starost1 << std::endl;
    std::cout << *starost2 << std::endl;

    (*starost2)--;

    std::cout << *starost2 << std::endl;

    return 0;
}
