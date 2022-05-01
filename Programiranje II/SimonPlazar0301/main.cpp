#include <iostream>
#include "Time.h"

int main() {
    Time a(123, 13, 67), b(12, 46, 33), c(23, 33, 44), d(23, 66, 12);
    Time e = Time::parse("12:12:12");

    Time* bpt = new Time(b);
    Time* cpt = new Time(c);

    std::cout << a.toString() << std::endl;
    std::cout << b.toString12HourFormat() << std::endl;
    std::cout << c.toString12HourFormat() << std::endl;
    std::cout << d.toString() << std::endl;
    std::cout << e.toString() << std::endl;

    std::cout << Time::diffSeconds(bpt,cpt);

    delete bpt;
    delete cpt;

    return 0;
}
