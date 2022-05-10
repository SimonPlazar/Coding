#include <sstream>
#include "Date.h"

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

std::ostream &operator<<(std::ostream &out, const Date &date) {
    out << date.toString();
    return out;
}

bool Date::operator==(const Date &other) const {
    if (day == other.day && month == other.month && year == other.year)
        return true;
    else
        return false;
}

Date &Date::operator++() {
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day + 1 > months[month]) {
        //gre v naslednji mesec
        day = 1;
        if (month == 12) {
            //gre v naslednjo leto
            month = 1;
            year++;
        } else {
            month++;
        }
    } else {
        //ne gre v naslednji mesec
        day++;
    }

    return *this;
}

Date Date::operator++(int dummy) {
    Date old = *this;

    ++(*this);

    return old;
}


