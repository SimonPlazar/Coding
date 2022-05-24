#include <sstream>
#include <algorithm>
#include "Date.h"
#include "UnparseableDateException.h"
#include "WrongDateException.h"

Date::Date() : day(0), month(0), year(0) {}

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}

std::string Date::toString() const {
    std::stringstream ss;
    ss << day << "." << month << "." << year;
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

bool goodFormat(const std::string &dateString) {
    std::string abeceda = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz ";

    if ((std::count(dateString.begin(), dateString.end(), '.') > 2) ||
        std::any_of(dateString.begin(), dateString.end(), [abeceda](char i) {
                        if (abeceda.find(i) != std::string::npos) return true;
                        else return false;
                    }
        ) || dateString.size() < 5 || dateString.find("..") != std::string::npos) {

        return false;
    }
    return true;
}


Date Date::GetDateFromString(const std::string &dateString) {
    if (goodFormat(dateString)) {
        unsigned int d = 0, m = 0, y = 0;

        std::string tmp = dateString;

        for (char &i: tmp) if (i == '.') i = ' ';

        std::stringstream(tmp) >> d >> m >> y;

        if (d > 31) throw WrongDateException(dateString);
        if (m > 12) throw WrongDateException(dateString);
        if (y > 2030) throw WrongDateException(dateString);

        return {d, m, y};
    } else {
        throw UnparseableDateException(dateString);
    }
}

void Date::print() const {
    std::cout << toString() << std::endl;
}


