#ifndef SIMONPLAZAR0402_CONFERENCE_H
#define SIMONPLAZAR0402_CONFERENCE_H

#include <vector>
#include <string>
#include "Date.h"
#include "Event.h"

class Conference {
private:
    std::string title;
    Date startDate;
    Date endDate;
    std::vector<Event> events;
public:
    Conference(std::string title, Date startDate, Date endDate);
    bool addEvent(const Event& event);
    std::string toString() const;
    std::vector<Person*> getAllAttendees() const;
};


#endif //SIMONPLAZAR0402_CONFERENCE_H
