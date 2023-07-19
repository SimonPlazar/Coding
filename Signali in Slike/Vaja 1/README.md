 	
Osnove vektorskega programiranja

Vzpostavite si okolje in se spoznajte z vektorskim programiranjem. V pomoč naj vam bo pripravljen seznam potrebnih paketov in odvisnosti za sistem Anakonda, katerega najdete na koncu razlage današnjih vaj.

Pripravite skripto osnove.py, ki ima definirane (vsebuje) naslednje funkcije:

def generiraj_vektor_nakljucno(stevilo_vzorcev: int) -> np.ndarray:
    pass

    parameter stevilo_vzorcev je število naključno generiranih vzorcev
    funkcija vrne vektor (tipa numpy ndarray oblike (stevilo_vzorcev, 1))
    naključna števila naj bodo enakomerno porazdeljena
    ustvarjena naključna števila naj imajo velikost med 0 in 1
    (2 točki)

def beri_zvok_mono(pot_do_datoteke: str) -> np.ndarray:
    pass

    pot_do_datoteke je pot do zvočne datoteke oblike WAV, ki jo želimo naložiti
    funkcija vrne vektor (tipa numpy ndarray oblike (x, 1))
        če je prebran zvok v stereo obliki, funkcija izračuna in vrne povprečje obeh kanalov za vsak vzorec
    vrnjena prebrana števila naj imajo velikost med 0 in 1, oziroma -1 in 1, če so predznačena
        vrnjena števila naj bodo normalizirana (deljena z maksimumom od absolutne vrednosti vseh števil)
    (2 točki)

def beri_zvok_stereo(pot_do_datoteke: str) -> np.ndarray:
    pass

    pot_do_datoteke je pot do zvočne datoteke oblike WAV, ki jo želimo naložiti
    funkcija vrne vektor (tipa numpy ndarray oblike (x, 2))
        če je prebran zvok v mono obliki podvojite prebran kanal
    vrnjena prebrana števila naj imajo velikost med 0 in 1, oziroma -1 in 1 če so predznačena
        vrnjena števila naj bodo normalizirana (deljena z maksimumom od absolutne vrednosti vseh števil)
    (2 točki)

def normaliziraj(vektor: np.ndarray) -> np.ndarray:
    pass

    funkcija prejme vektor
    funkcija opravi normalizacijo nad prejetim vektorjem
        normalizirajte v smislu deljenja z maksimumom od absolutne vrednosti vseh števil
        normalizacijo programirajte v klasični obliki (zanka for za iteracijo nad vektorjem, ...)
    vrnjen vektor naj bo iste oblike kot prejet vektor
    vrnjen vektor naj vsebuje vrednosti tipa np.float64
    (2 točki)

def normaliziraj_vektorsko(vektor: np.ndarray) -> np.ndarray:
    pass

    funkcija prejme vektor
    funkcija opravi normalizacijo nad prejetim vektorjem
        normalizirajte v smislu deljenja z maksimumom od absolutne vrednosti vseh števil
        normalizacijo programirajte v vektorski obliki (uporabite NumPy metode za izvajanje računanja nad vektorji)
    vrnjen vektor naj bo iste oblike kot prejet vektor
    vrnjen vektor naj vsebuje vrednosti tipa np.float64
    (2 točki)

def testiraj_cas_izvajanja(vektor: np.ndarray) -> np.ndarray:
    pass

    funkcija prejme vektor
    funkcija kliče funkcijo »normaliziraj« s podanim vektorjem in zabeleži čas izvajanja
        za beleženje časa izvajanja uporabite modul timeit
    funkcija kliče funkcijo »normaliziraj_vektorsko« s podanim vektorjem in zabeleži čas izvajanja
        za beleženje časa izvajanja uporabite modul timeit
    funkcija vrne vektor oblike (1, 2), kjer je prvi element čas funkcije »normaliziraj« in drugi element čas funkcije »normaliziraj_vektorsko«
        čas naj bo v enotah sekunda
    (6 točk)

Pripravite še odsek kode, katero lahko samostojno zaženete kot demo:

if __name__ == '__main__':

    ustvarite naključni vektor dolžine 1000000
    kliči funkcijo »testiraj_cas_izvajanja«
    izpiši rezultat v terminal

 

Zahtevano implementacijo oddajte v datoteki osnove.py.

V arhivu naloga.zip oddajte pripravljen dokument.