Prevzorčenje slike
V tej nalogi pripravite metode za prevzorčenje slike.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje funkcije:

def prevzorci_sliko(slika : np.ndarray,  nova_visina : int, nova_sirina : int) -> np.ndarray:
    pass
funkcije prejme 3 obvezne in 1 opcijski parameter
slika je tabela oblike (H, W, 3) za barvno sliko ali (H, W) za sivinsko
nova_visina in nova_sirina sta zeljena višina in širina vrnjene slike v pikslih
funkcija vrne sliko oblike (nova_visina, nova_sirina, 3) istega podatkovnega tipa kot vhodna slika
(16 točk)
Samo prevzorčenje lahko implementirate z metodo  scipy.ndimage.zoom ali scipy.ndimage.map_coordinates. Funkciji ne poskrbita za ustrezno filtriranje višjih frekvenc (Niquistov teorem!), pred prevzorčenjem morate zato sami poskrbeti za ustrezno filtriranje. Prevzorčenje morate implementirajte v domeni slike (brez frevenčne transformacije).

def prevzorci_sliko_fft(slika : np.ndarray,  nova_visina : int, nova_sirina : int) -> np.ndarray:
    pass
funkcije prejme 3 obvezne in 1 opcijski parameter
slika je tabela oblike (H, W, 3) za barvno sliko ali (H, W) za sivinsko
nova_visina in nova_sirina sta zeljena višina in širina vrnjene slike v pikslih
funkcija vrne sliko oblike (nova_visina, nova_sirina, 3) istega podatkovnega tipa kot vhodna slika
(8 točk)
Sliko pretvorite v frekvenčno domeno s funkcijo numpy.fft.fft2, tam dodajte ali odstranite visoke frekvence, da boste dobili ustrezne dimenzije in pretvorite sliko nazaj v prostor slike z ifft2. Prevzorčenje oziroma interpolacija v frekvenčni domeni deluje zelo podobno kot za 1D signale. Če želimo povečati število vzorcev potem dodamo 0 za visoke frekvence, če želimo zmanjšati število vzorcev potem odstranimo visoke frekvence (ohraniti moramo zrcalni izgled v frekvenčnem prostoru!). Razlika je le ta, da tokrat to delamo v 2 dimenzijah.

Pred oddajo je smiselno rešitev preizkusiti na pravih slikah.

Zahtevano implementacijo oddajte v datoteki prevzorci_sliko.py.