#ifndef SIMONPLAZAR0301_TIME_H
#define SIMONPLAZAR0301_TIME_H

#include <string>

class Time {
private:
    unsigned int hour, minutes, seconds;
    static const int maxHour = 24;
    static const int noonHour = 12;
public:
    Time(int hour, int minutes, int seconds);

    static bool isTimeValid(unsigned int hour, unsigned int minutes, unsigned int seconds);

    std::string toString() const;

    std::string toString12HourFormat() const;

    static Time parse(const std::string &time);

    static unsigned int diffSeconds(const Time* time1, const Time* time2) ;
};

#endif //SIMONPLAZAR0301_TIME_H
