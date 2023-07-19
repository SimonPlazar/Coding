Pretvorbe barvnih prostorov
Za to nalogo si poglejte formule za pretvorbo med različnimi barvnimi prostori in implementirajte funkcije, ki bodo te pretvorbe opravile. Implementirajte transformacije med RGB in HSV (wikipedia opis), YCbCr (wikipedia opis).

Implementacije morate pripraviti sami in ne uporabiti pripravljenih funkcij knjižnic.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje funkcije:

def RGB_v_HSV(slika : np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo barvno sliko
slika je tabela oblike (H, W, 3), tipa numpy.uint8
funkcija vrnejo barvno sliko, pretvorjeno v drug barvni prostor
HSV
kanal HUE ima vrednosti od 0 do 180 (stopinje/2)
vrednosti shranjujete v numpy.uint8, tako da skalirajte dobljene vrednosti na območje 0-180
kanal VALUE ima vrednosti od 0 do 255 (procenti/100*255)
vrednosti shranjujete v numpy.uint8, tako da skalirajte dobljene vrednosti na območje 0-255
(6 točk)
def HSV_v_RGB(slika : np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo barvno sliko
slika je tabela oblike (H, W, 3), tipa numpy.uint8
funkcija vrnejo barvno sliko, pretvorjeno v drug barvni prostor
RGB
(6 točk)
def RGB_v_YCbCr(slika : np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo barvno sliko
slika je tabela oblike (H, W, 3), tipa numpy.uint8
funkcija vrnejo barvno sliko, pretvorjeno v drug barvni prostor
YCbCr
za pretvorbo uporabite koeficiente uporabljene v JPEG formatu
(6 točk)
def YCbCr_v_RGB(slika : np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo barvno sliko
slika je tabela oblike (H, W, 3), tipa numpy.uint8
funkcija vrnejo barvno sliko, pretvorjeno v drug barvni prostor
RGB
(6 točk)
Zahtevano implementacijo oddajte v datoteki barvne_transformacije.py.