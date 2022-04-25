//
// Created by simon on 17/03/2022.
//

#ifndef SIMONPLAZAR0401_DATE_H
#define SIMONPLAZAR0401_DATE_H

#include <string>

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
public:
    Date();

    Date(unsigned int day, unsigned int month, unsigned int year);

    void setDay(unsigned int x);

    void setMonth(unsigned int x);

    void setYear(unsigned int x);

    unsigned int getDay() const;

    unsigned int getMonth() const;

    unsigned int getYear() const;

    std::string toString() const;
};


#endif //SIMONPLAZAR0401_DATE_H
