#include <iostream>
#include "Artwork.h"

Artwork* getExpensive(Artwork *a, Artwork *b) {
    if (a->isExpensive(b))
        return a;
    else
        return b;
}


int main() {
    Artwork a;
    Artwork b("naslov", "opis", 2.12, 2022);

    auto *c = new Artwork();
    auto *d = new Artwork("naslov2", "opis2", 14.14, 2002);

    Artwork e;

    a.setTitle("Naslov3");
    a.setDescription("opis3");
    c->setPrice(3.14);
    c->setYear(2006);

    getExpensive(c, d)->print();

    std::cout << a.getTitle() << " " << b.getDescription() << " " << c->getPrice() << " " << d->getYear() << std::endl;

    b.print();
    std::cout << d->toString();

    e.setDescription("Zelo izviren opis");
    e.print();

    delete c;
    delete d;

    return 0;
}
