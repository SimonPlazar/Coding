#ifndef SIMONPLAZAR0402_EVENT_H
#define SIMONPLAZAR0402_EVENT_H

#include <vector>
#include <string>
#include "Person.h"
#include "Date.h"

class Event {
private:
    std::string title;
    std::string description;
    Person *presenter;
    Date date;
    std::vector<Person *> attendees;
public:
    Event(std::string title, std::string description, Person *presenter, Date date);

    void addAttendee(Person *person);

    std::string toString() const;

    const std::string &getTitle() const;

    const std::string &getDescription() const;

    Person *getPresenter() const;

    const Date &getDate() const;

    const std::vector<Person *> &getAttendees() const;

    void setTitle(const std::string &title);

    void setDescription(const std::string &description);

    void setPresenter(Person *presenter);

    void setDate(const Date &date);

    void setAttendees(const std::vector<Person *> &attendees);
};


#endif //SIMONPLAZAR0402_EVENT_H
