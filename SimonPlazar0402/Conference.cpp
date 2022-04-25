#include "Conference.h"
#include <utility>
#include <sstream>

Conference::Conference(std::string title, Date startDate, Date endDate) : title(std::move(title)), startDate(startDate),
                                                                          endDate(endDate) {
}

bool hasSameDate(const std::vector<Event> &events, const Event &event) {
    for (const auto &i: events)
        if (i.getDate().toString() == event.getDate().toString()) return true;
    return false;
}

bool Conference::addEvent(const Event &event) {
    if (hasSameDate(events, event)) return false;

    this->events.push_back(event);
    return true;
}

std::string Conference::toString() const {
    std::stringstream ss;
    ss << title << std::endl << startDate.toString() << std::endl << endDate.toString();

    for (const auto &event: events) {
        ss << std::endl;
        ss << event.toString();
    }

    return ss.str();
}

bool contains(const std::vector<Person *> &allAttendees, Person *person) {
    for (auto &allAttendee: allAttendees)
        if (allAttendee->toString() == person->toString()) return true;
    return false;
}

std::vector<Person *> Conference::getAllAttendees() const {
    std::vector<Person *> allAttendees;

    for (const auto &event: events) {
        for (auto j: event.getAttendees()) {
            if (!contains(allAttendees, j)) allAttendees.push_back(j);
        }
    }

    return allAttendees;
}

