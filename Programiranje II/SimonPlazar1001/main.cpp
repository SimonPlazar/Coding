#include <iostream>
#include "Painting.h"
#include "Gallery.h"
#include "Sculpture.h"

bool ascendingYear(Artwork* i, Artwork* j){
    if(i->getYear() <= j->getYear()) return true;
    return false;
}

bool descandingYear(Artwork* i, Artwork* j){
    if(i->getYear() >= j->getYear()) return true;
    return false;
}

bool ascendingPrice(Artwork* i, Artwork* j){
    if(i->getPrice() <= j->getPrice()) return true;
    return false;
}

bool isRenaissanceArt(Artwork* a){
    if(1400 < a->getYear() && a->getYear() < 1600 ) return true;
    return false;
}

bool isOlderThan2000(Artwork* a){
    if (a->getYear()<2000) return true;
    return false;
}

int main() {
    Artist artist1("Artist1_Ime", "Artist1_Opis", Date(1, 1, 123));

    Painting slika1("Title", "Desc", 2.14, 1999, &artist1, PaintingTechnique::Oil);
    Painting slika2("Title2", "Desc2", 73.34, 1677, &artist1, PaintingTechnique::Graphite);

    Artwork artwork1("Title3", "Desc3", 45, 3243, &artist1);
    Artwork artwork2("Title4", "Desc4", 245, 343, &artist1);


    Sculpture sculpture1("Title5", "Desc5", 2.14, 1999, &artist1, 50.24, Material::Metal);

    Gallery galerija("Ime_Galerije");

    galerija.addArtwork(&slika1);
    galerija.addArtwork(&slika2);

    galerija.addArtwork(&artwork1);
    galerija.addArtwork(&artwork2);

    galerija.addArtwork(&sculpture1);

    Artwork artwork3("Title6", "Desc6", 245, 1450, &artist1);
    galerija.addArtwork(&artwork3);

    Artwork artwork4("Title7", "Desc7", 240, 1452, &artist1);
    galerija.addArtwork(&artwork4);

    std::cout << galerija.toString();

    galerija.sort(ascendingYear);
    std::cout << "\n--------ascendingYear--------\n";

    std::cout << galerija.toString();

    galerija.sort(descandingYear);
    std::cout << "\n--------descandingYear-------\n";

    std::cout << galerija.toString();

    galerija.sort(ascendingPrice);
    std::cout << "\n------ascendingPrice-------\n";

    std::cout << galerija.toString();

    std::cout << "\n-----isRenaissanceArt----\n";

    std::cout << galerija.find(isRenaissanceArt)->toString();

    std::cout << "\n---------paint-----------\n";

    PrintIfPainting paint;
    galerija.printArtworks(paint);

    std::cout << "\n---------isOlderThan2000-----\n";

   std::vector<Artwork*> tmp = galerija.findAll(isOlderThan2000);

    for (auto & i : tmp) {
        i->print();
    }

    return 0;
}
