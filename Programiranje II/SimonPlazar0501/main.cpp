#include <iostream>
#include "Painting.h"
#include "Gallery.h"
#include "Sculpture.h"

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

    std::cout << galerija.toString();
    return 0;
}
