#include "Date.h"
#include <sstream>

Date::Date() : day(0), month(0), year(0) {
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {
}

std::string Date::toString() const {
    std::stringstream ss;
    ss << day << "/" << month << "/" << year;
    return ss.str();
}

unsigned int Date::getDay() const {
    return day;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getYear() const {
    return year;
}
void Date::setDay(unsigned int x) {
    Date::day = x;
}

void Date::setMonth(unsigned int x) {
    Date::month = x;
}

void Date::setYear(unsigned int x) {
    Date::year = x;
}


