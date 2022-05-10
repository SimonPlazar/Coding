#include <iostream>
#include <memory>
#include "SmartPointer.h"
#include "Date.h"

int main(){
    SmartPointer<Date> date1(new Date(1, 1, 2020));
    SmartPointer<Date> date2(new Date(1, 1, 2019));
    date2 = date1 = date1 = date1 = date1 = date1;
    date2 = date2;
    date2 = date2;
    std::cout << "reference count: " << date2.useCount() << std::endl;

    {
        SmartPointer<Date> date3(new Date(1, 1, 2020));
        date3 = date2;
        std::cout << "reference count: " << date2.useCount() << std::endl;
    }

    std::cout << "reference count: " << date2.useCount() << std::endl;

    return 0;
}
