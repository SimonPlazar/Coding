#include "Event.h"

#include <utility>
#include <sstream>

Event::Event(std::string title, std::string description, Person *presenter, Date date) : title(std::move(title)), description(std::move(description)), presenter(presenter), date(date){
}

void Event::addAttendee(Person *person) {
    this->attendees.push_back(person);
}

std::string Event::toString() const{
    std::stringstream ss;
    ss << title << std::endl << description << std::endl << presenter->toString() << std::endl << date.toString();
    for (auto attendee : attendees) {
        ss << std::endl;
        ss << attendee->toString();
    }
    return ss.str();
}

const std::string &Event::getTitle() const {
    return title;
}

const std::string &Event::getDescription() const {
    return description;
}

Person *Event::getPresenter() const {
    return presenter;
}

const Date &Event::getDate() const {
    return date;
}

const std::vector<Person *> &Event::getAttendees() const {
    return attendees;
}

void Event::setTitle(const std::string &x) {
    Event::title = x;
}

void Event::setDescription(const std::string &x) {
    Event::description = x;
}

void Event::setPresenter(Person *x) {
    Event::presenter = x;
}

void Event::setDate(const Date &x) {
    Event::date = x;
}

void Event::setAttendees(const std::vector<Person *> &x) {
    Event::attendees = x;
}



