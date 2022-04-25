#include <sstream>
#include "Time.h"

bool Time::isTimeValid(unsigned int hour, unsigned int minutes, unsigned int seconds) {
    if (0 <= hour && hour < maxHour && 0 <= minutes && minutes < 60 && 0 <= seconds && seconds < 60)
        return true;
    else
        return false;
}

Time::Time(int hour, int minutes, int seconds) {
    if (isTimeValid(hour, minutes, seconds)) {
        this->hour = hour;
        this->minutes = minutes;
        this->seconds = seconds;
    } else {
        this->hour = 0;
        this->minutes = 0;
        this->seconds = 0;
    }
}

std::string Time::toString() const {
    std::stringstream ss;

    if (hour < 10) {
        ss << 0;
    }
    ss << hour << ":";

    if (minutes < 10) {
        ss << 0;
    }
    ss << minutes << ":";

    if (seconds < 10) {
        ss << 0;
    }
    ss << seconds;

    return ss.str();
}

std::string Time::toString12HourFormat() const {
    std::stringstream ss;

    if (hour > noonHour) {
        unsigned int tmphour = hour - 12;

        if (tmphour < 10) {
            ss << 0;
        }
        ss << tmphour << ":";

        ss << minutes << ":" << seconds << " PM";
    } else if (hour == noonHour) {
        ss << toString() << " PM";
    } else
        ss << toString() << " AM";

    return ss.str();
}

Time Time::parse(const std::string &time) {
    //hh:mm:ss
    return {stoi(time.substr(0, 2)), stoi(time.substr(3, 2)), stoi(time.substr(6, 2))};
}

unsigned int Time::diffSeconds(const Time *time1, const Time *time2) {
    unsigned int time1total;
    unsigned int time2total;

    time1total = time1->hour*3600 + time1->minutes*60 + time1->seconds;
    time2total = time2->hour*3600 + time2->minutes*60 + time2->seconds;

    if(time1total>time2total)
        return time1total-time2total;
    else
        return time2total-time1total;
}


