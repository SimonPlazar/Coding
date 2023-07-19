Konvolucija v časovnem prostoru

Demonstrirajte razumevanje konvolucije s svojo implementacijo konvolucije v časovnem prostoru, s katero "popačite" oziroma spremenite podan signal s podanim impulzom.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje elemente.

def konvolucija_offline(signal: np.ndarray, impulz: np.ndarray, dolzina: str) -> np.ndarray:
    pass

Funkcija za izračun konvolucije med signalom in impulzom. Prejme tri parametre:

    signal, tabela np.ndarray oblike (N, C) ali (N,), podatkovnega tipa np.float64
        N je število vzorcev v signalu, C je število kanalov
    impulz, tabela np.ndarray oblike (K, 1), ali (K,), podatkovnega tipa np.float64
        K je število vzorcev v impulzu
    dolzina, niz 'polna' ali 'veljavna'

Funkcija vrne:

    tabelo np.ndarray oblike (M, C) ali (M,), podatkovnega tipa np.float64

Navodila za implementacijo:

    Funkcija vrne konvolucijo signala z impulznim odzivom (impulz).
    Implementacija konvolucije naj bo opravljena v časovnem prostoru.
    Pri implementaciji je prepovedana uporabe funkcij knjižnice kot je np.convolve.
        Za učinkovito implementacijo uporabite numpy operacije namesto notranje zanke.
    Če je kot dolžina podan niz 'polna', naj funkcija vrne polno dolžino konvolucije.
        Izhodni signal vsebuje izračunano vrednost za vsak zamik, kjer se impulz in signal prekrivata za vsaj en vzorec.
        Kjer vrednosti impulza padejo izven vzorcev signala, jih pomnožimo z 0 (ignoriramo).
    Če je kot dolžina podan niz 'veljavna' naj funkcija vrne veljavno dolžino konvolucije.
        Izhodni signal vsebuje izračunano vrednost za vsak zamik, kjer se impulz in signal prekrivata v celoti.
    Signal ima lahko enega ali več kanalov.
        Vsak kanal naj bo neodvisno konvoluriran z impulzom.
        Implementirana podpora za več kanalov.
    Kadar ima signal samo en kanal je lahko podan kot enodimenzionalna tabela.
    Impulz ima en kanal. Podan je lahko kot eno ali dvodimenzionalna tabela.
    Izhod naj ima enako število dimenzij kot signal.

Pripravite še odsek kode, katero lahko samostojno zaženete kot demo:

if __name__ == '__main__':
    pass

    pripravite signal dolžine 20 vzorcev
    pripravite impulz dolžine 5 vzorcev
    uporabite implementirano metodo za izračun konvolucije
    v matplotlib izrišite signal, impulz in rezultat
        jasno označite izrise
        ustrezno označite imena osi

Točkovanje:

    učinkovita implementacija z numpy operacijami (5 točk)
    implementacija dolžine 'polna' (5 točk)
    implementacija dolžine 'veljavna' (5 točk)
    implementirana podpora za več kanalov (5 točk)
    implementacija demonstracije in vizualizacija (8 točk)

 

Zahtevano implementacijo oddajte v datoteki konvolucija.py.

V arhivu naloga.zip oddajte pripravljen dokument.