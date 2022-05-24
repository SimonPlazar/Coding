#include <iostream>
#include "Painting.h"
#include "Gallery.h"
#include "Sculpture.h"
#include "Luna.h"

bool isOlderThan2000(const std::shared_ptr<Artwork>& a){
    if(a->getYear() > 2000) return true;
    return false;
}

int main() {
    Artist artist1("Artist1_Ime", "Artist1_Opis", Date(1, 1, 123));

    Painting slika1("Title", "Desc", 2.14, 1999, std::make_shared<Artist>(artist1), PaintingTechnique::Oil);
    Painting slika2("Title2", "Desc2", 73.34, 1677, std::make_shared<Artist>(artist1), PaintingTechnique::Graphite);

    Artwork artwork1("Title3", "Desc3", 45, 3243, std::make_shared<Artist>(artist1));
    Artwork artwork2("Title4", "Desc4", 245, 343, std::make_shared<Artist>(artist1));


    Sculpture sculpture1("Title5", "Desc5", 2.14, 1999, std::make_shared<Artist>(artist1), 50.24, Material::Metal);

    Gallery galerija("Ime_Galerije");

    galerija.addArtwork(std::make_shared<Painting>(slika1));
    galerija.addArtwork(std::make_shared<Painting>(slika2));

    galerija.addArtwork(std::make_shared<Artwork>(artwork1));
    galerija.addArtwork(std::make_shared<Artwork>(artwork2));

    galerija.addArtwork(std::make_shared<Sculpture>(sculpture1));

    Artwork artwork3("Title6", "Desc6", 245, 1450, std::make_shared<Artist>(artist1));
    galerija.addArtwork(std::make_shared<Artwork>(artwork3));

    Artwork artwork4("Title7", "Desc7", 240, 1452, std::make_shared<Artist>(artist1));
    galerija.addArtwork(std::make_shared<Artwork>(artwork4));

    std::cout << galerija.toString();

    galerija.sort(ascendingYear);
    std::cout << "\n---------------------------\n";

    std::cout << galerija.toString();

    galerija.sort(descandingYear);
    std::cout << "\n---------------------------\n";

    std::cout << galerija.toString();

    galerija.sort(ascendingPrice);
    std::cout << "\n---------------------------\n";

    std::cout << galerija.toString();

    std::cout << "\n---------------------------\n";

    std::cout << galerija.find(isRenaissanceArt)->toString();

    std::cout << "\n---------------------------\n";

    PrintIfPainting paint;
    galerija.printArtworks(paint);

    std::cout << "\n---------------------------\n";

    std::cout << "\n---------------Before filter: \n";
    std::cout << galerija.toString();
    galerija.filterOut(isOlderThan2000);
    std::cout << "\n---------------After 1st filter: \n";
    std::cout << galerija.toString();

    galerija.filterOut([](const std::shared_ptr<Artwork>& a){
        if(a->getPrice() < 100) return true;
        return false;
    });

    std::cout << "\n---------------After 2nd filter: \n";
    std::cout << galerija.toString();

    std::cout << "\n---------------------------\n";

    //std::string ime, unsigned int masa, unsigned int visina, unsigned int povrsina
    Luna vaja("Ime", 1200, 1000000, 5065);
    std::cout<<vaja.toString();

    return 0;
}
