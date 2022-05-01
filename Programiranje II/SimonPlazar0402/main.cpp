#include <iostream>
#include "Conference.h"
#include "Event.h"
#include "Person.h"
#include "Date.h"

int main() {
    Person osebe[10]{Person("1", "Nordskov"),
                     Person("2", "Jokinen"),
                     Person("3", "Upton"),
                     Person("4", "Slovak"),
                     Person("5", "Nordskov"),
                     Person("6", "Jokinen"),
                     Person("7", "Upton"),
                     Person("8", "Slovak"),
                     Person("9", "Nordskov"),
                     Person("10", "Jokinen")
    };

    Conference Lyoness("Lyoness", Date(1, 1, 2016), Date(29, 12, 2016));

    Event FreeMonery("Free Monery", "opis", &osebe[0], Date(19, 9, 2016));
    Event PasiveIncome("Pasive Income", "opis", &osebe[0], Date(14, 12, 2016));
    Event MultiplyAllMonery("Multiply All Monery", "opis", &osebe[0], Date(30, 4, 2016));
    Event NewEvent("new", "opis", &osebe[0], Date(30, 4, 2016));

    for (int i = 1; i < 4; ++i) {
        FreeMonery.addAttendee(&osebe[i]);
        PasiveIncome.addAttendee(&osebe[i + 3]);
        MultiplyAllMonery.addAttendee(&osebe[i + 6]);
    }

    if (!Lyoness.addEvent(FreeMonery)) std::cout << "Napaka" << std::endl;
    if (!Lyoness.addEvent(PasiveIncome)) std::cout << "Napaka" << std::endl;
    if (!Lyoness.addEvent(MultiplyAllMonery)) std::cout << "Napaka" << std::endl;
    if (!Lyoness.addEvent(NewEvent)) std::cout << "Napaka" << std::endl;

    std::cout << Lyoness.toString() << std::endl;

    std::cout << "-----------------------" << std::endl;

    std::vector<Person *> all;

    all = Lyoness.getAllAttendees();

    for (auto & i : all) {
        std::cout << i->toString()<<std::endl;
    }

    return 0;
}
