Obdelava slik z morfološkimi operacijami
Za to nalogo si poglejte in implementirajte obdelavo slike z morfološkimi operacijami. Za implementacijo spodaj naštetih funkcij lahko poleg matematičnih operacij (seštevanje, odštevanje, ..., unija, presek, ...) uporabite vnaprej pripravljene metode širjenja in krčenja.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje funkcije:

def open(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo binarno sliko in morfološko jedro
slika je tabela oblike (H,W) in tipa numpy.bool
jedro je tabela oblike (N, M), tipa numpy.bool
funkcija vrne binarno sliko oblike (H,W) tipa numpy.bool
(8 točk)
def close(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo binarno sliko in morfološko jedro
slika je tabela oblike (H,W) in tipa numpy.bool
jedro je tabela oblike (N, M), tipa numpy.bool
funkcija vrne binarno sliko oblike (H,W) tipa numpy.bool
(8 točk)
def hit_miss(slika, jedro_hit, jedro_miss):

def hit_miss(slika: np.ndarray, jedro_hit: np.ndarray, jedro_miss: np.ndarray) -> np.ndarray:
    pass
funkcija prejmejo binarno sliko in dve jedri: jedro_hit, jedro_miss (opisano na wikipediji)
slika je tabela oblike (H,W) in tipa numpy.bool
jedro_hit je tabela oblike (N, M), tipa numpy.bool, ki mora ustrezati True vrednostim na lokaciji
jedro_miss je tabela oblike (N, M), tipa numpy.bool, ki mora ustrezati False vrednostim na lokaciji
funkcija vrne binarno sliko oblike (H,W) tipa numpy.bool
(11 točk)
 
Zahtevano implementacijo oddajte v datoteki morfoloske_operacije.py.