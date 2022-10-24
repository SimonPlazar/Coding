2022: Naloga 10.1 (obvezna)

Uporabite in razširite nalogo 5.1 po spodnjih navodilih.

Razširite nalogo tako, da v glavnem programu podprete spodnje klice metode sort, ki s pomočjo funkcije kot parameter sortira umetnine v galeriji na različne načine:

gallery.sort(ascendingYear);
cout << gallery.toString() << std::endl;
gallery.sort(descendingYear);
cout << gallery.toString() << std::endl;
gallery.sort(ascendingPrice);
cout << gallery.toString() << std::endl;
V ta namen zapišite naslednje:

Dodajte metodo sort v razred Gallery:
void sort(bool (*c)(Artwork*, Artwork*));

Metoda sort uredi vector artworks v razredu Gallery, tako kot zahteva funkcija, ki jo prejme kot parameter.

Za potrebe metode sort implementirajte še:
bool ascendingYear(Artwork* i, Artwork* j);
bool descandingYear(Artwork* i, Artwork* j);
bool ascendingPrice(Artwork* i, Artwork* j);
Funkcije implementirajte zunaj razreda Gallery.

V glavnem programu podprite naslednjo vrstico kode, ki poišče prvo umetnino, ki je iz renesančnega obdobja.

cout << gallery.find(isRenaissanceArt)->toString();

Potrebujemo naslednje:

Dodajte metodo find v razred Gallery:
Artwork* find(bool (*c)(Artwork*));

Metoda find vrne prvi element vector-ja artworks v razredu Gallery, ki ustreza pogoju. Za implementacijo uporabite funkcijo find_if iz knjižnice algorithms: http://www.cplusplus.com/reference/algorithm/find_if/. Tretji parameter funkcije find_if je parameter metode find (glej zgoraj).

Za potrebe metode find v glavnem programu implementirajte še:

bool isRenaissanceArt(Artwork* a);
Funkcija preveri, ali je letnica umetnine med 1400 in 1600.

V glavnem programu podprite naslednji vrstici kode, ki izpiše vse Painting umetnine iz galerije:

PrintIfPainting paint;
gallery.printArtworks(paint);
Potrebujemo naslednje:

Dodajte metodo printArtworks v razred Gallery:
void printArtworks(PrintIfPainting i);

Metoda printArtworks izpiše vse umetnine v razredu Gallery, tako kot zahteva funkcijski tip PrintIfPainting, ki jo prejme kot parameter. Za implementacijo uporabite funkcijo for_each iz knjižnice algorithms: http://www.cplusplus.com/reference/algorithm/for_each/. Tretji parameter funkcije for_each je parameter metode printArtworks (glej zgoraj).

Za potrebe funkcije for_each implementirajte razred PrintIfPainting ter prekrijte operator:
void operator()(Artwork* e);

V zgornji metodi boste potrebovali rezervirano besedo dynamic_cast ( primer: https://en.cppreference.com/w/cpp/language/dynamic_cast).

V glavnem programu demonstrirajte uporabo kazalcev na funkcije in funkcijske tipe.

