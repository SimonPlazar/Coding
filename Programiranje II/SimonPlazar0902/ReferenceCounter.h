//
// Created by simon on 07/05/2022.
//

#ifndef SIMONPLAZAR0902_REFERENCECOUNTER_H
#define SIMONPLAZAR0902_REFERENCECOUNTER_H

class ReferenceCounter {
private:
    int count = 0;
public:
    int &operator--();

    int operator++(int dummy);

    int getCount() const;
};

int &ReferenceCounter::operator--() {
    return --count;
}

int ReferenceCounter::operator++(int dummy) {
    return count++;
}

int ReferenceCounter::getCount() const {
    return count;
}

#endif //SIMONPLAZAR0902_REFERENCECOUNTER_H
