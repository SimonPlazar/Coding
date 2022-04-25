#include <sstream>
#include "WaterIntake.h"

WaterIntake::WaterIntake() {
    day = 0;
    month = 0;
    year = 0;
    quantity = 0;
}

WaterIntake::WaterIntake(unsigned int day1, unsigned int month1, unsigned int year1, float quantity1) {
    day = day1;
    month = month1;
    year = year1;
    quantity = quantity1;
}

unsigned int WaterIntake::getDay() const {
    return day;
}

unsigned int WaterIntake::getMonth() const {
    return month;
}

unsigned int WaterIntake::getYear() const {
    return year;
}

float WaterIntake::getQuantity() const {
    return quantity;
}

void WaterIntake::setQuantity(float quantity2) {
    quantity = quantity2;
}

std::string WaterIntake::toString() const {
    std::stringstream ss;
    ss << "[" << day << "/" << month << "/" << year << "] - " << quantity << " l" << std::endl;
    return ss.str();
}

void WaterIntake::addQuantity(float quantity3) {
    quantity += quantity3;
}
