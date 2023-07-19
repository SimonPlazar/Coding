Konvolucija v frekvenčnem prostoru

Demonstrirajte razumevanje konvolucije s svojo implementacijo konvolucije v frekvenčnem prostoru, s katero "popačite" oziroma spremenite podan signal s podanim impulzom.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje elemente.

def konvolucija_fft(signal: np.ndarray, impulz: np.ndarray, rob: str) -> np.ndarray:
    pass
Fukcija za izračun konvolucije med signalom in impulzom, izračun s pomočjo pretvorbe v frekvenčni prostor z hitro transformacijo Fourier. Prejme parametre:

signal, tabela np.ndarray oblike (N, C) ali (N,), podatkovnega tipa np.float64
N je število vzorcev v signalu, C je število kanalov
impulz, tabela np.ndarray oblike (K, 1), ali (K,), podatkovnega tipa np.float64
K je število vzorcev v impulzu
rob, niz, eden izmed 'ničle', 'zrcaljen', 'krožni'
Funkcija vrne:

tabelo np.ndarray oblike (N, C) ali (N,), podatkovnega tipa np.float64
Navodila za implementacijo:

Funkcija vrne konvolucijo signala z impulznim odzivom (impulz).
Implementacija naj bo opravljena v frekvenčnem prostoru, uporabite funkcijo np.fft.fft.
Dolžina izhodnega signala naj bo enaka dolžini vhodnega signala.
Signal in impulz boste pred izračunom morali podaljšati na ustrezno enako dolžino za izračun konvolucije, kjer je to potrebno. To storite tako, da signale dopolnite z izbranimi vrednostmi roba (to nalogo opravi funkcija np.pad).
Če je kot rob podan niz 'ničle', želimo izračunati konvolucijo, kjer so vrednosti signala izven robov 0.
Če je kot rob podan niz 'zrcaljen', želimo izračunati konvolucijo, kjer se vrednosti signala zrcalijo preko robov (signal se ponovi, vendar od zadaj naprej).
Če je kot rob podan niz 'krožni', želimo izračunati konvolucijo, kjer se signal izven robov periodično ponavlja.
Impulz vedno dopolnite z vrednostmi 0.
Kadar ima signal samo en kanal je lahko podan kot enodimenzionalna tabela.
Impulz ima en kanal. Podan je lahko kot eno ali dvodimenzionalna tabela.
Izhod naj ima enako število dimenzij kot signal.
Pripravite še odsek kode, katero lahko samostojno zaženete kot demo:

if __name__ == '__main__':
    pass
pripravite signal dolžine 10 vzorcev
pripravite impulz dolžine 3 vzorcev
uporabite implementirano metodo za izračun konvolucije
demonstrirajte vse implementirane tipe robov
v matplotlib izrišite signal, impulz in rezultat
jasno označite izrise
ustrezno označite imena osi
Točkovanje:

implementacija konvolucije z robom 'ničle' (4 točk)
implementacija konvolucije z robom 'zrcaljen' (2 točk)
implementacija konvolucije z robom 'krožni' (2 točk)
implementirana podpora za več kanalov (2 točk)
implementacija demonstracije in vizualizacija (8 točk)
 

Zahtevano implementacijo oddajte v datoteki konvolucija.py.

V arhivu naloga.zip oddajte pripravljen dokument.