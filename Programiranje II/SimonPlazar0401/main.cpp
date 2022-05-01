#include <iostream>
#include "Gallery.h"

int main() {
    Gallery gallery("Galerija Florijan");

    Artist a("Davinky", "biografija1", Date(15, 4, 1452));
    Artist b("Picasso", "biografija2", Date(25, 10, 1881));

    Artwork c("naslov1", "opis1", 2.12, 2020, &a);
    Artwork d("naslov2", "opis2", 2.12, 2001, &a);
    Artwork e("naslov3", "opis3", 2.12, 2003, &b);
    Artwork f("naslov4", "opis4", 2.12, 2007, &b);
    Artwork g("naslov5", "opis5", 2.12, 2013, &b);

    gallery.addArtwork(&c);
    gallery.addArtwork(&d);
    gallery.addArtwork(&e);
    gallery.addArtwork(&f);
    gallery.addArtwork(&g);

    std::vector<Artwork *> between;

    between = gallery.getArtworksBetweenYear(2003, 2008);

    for (auto &i: between) {
        i->print();
    }

    std::cout << "----------------" << std::endl;

    gallery.removeArtwork(&f);

    std::cout << gallery.toString() << std::endl;

    std::cout << "----------------" << std::endl;

    gallery.printArtworks();

    return 0;
}
