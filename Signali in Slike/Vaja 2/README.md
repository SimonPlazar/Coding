Osnove vzorčenja

Demonstrirajte osnovna znanja vzorčenja signalov z implementacijo generatorja tonov.

Pripravite modul generiraj, ki ima definirano (vsebuje) naslednjo funkcijo:

def generiraj_ton_mono(cas : float, vzorcevalna_frekvenca : int, bitna_locljivost : int, frekvenca_tona : float) -> np.ndarray:
    pass

    funkcija prejme 4 parametre
        čas v sekundah, ki pove dolžino ustvarjenega signala
        vzorčevalno frekvenco v hercih, ki pove koliko vzorcev na sekundo je v signalu
        bitno ločljivost v bitih, ki pove maksimalno natančnost posameznega vzorca
        frekvenco tona v hercih, ki pove frekvenco ustvarjenega tona
    funkcija vrne vektor (tipa numpy ndarray oblike (x, 1))
    vrnjen vektor naj bo ustreznega tipa (int8, int16, int32, ali int64)
        izbran tip naj bo najmanjši možni tip, ki lahko vsebuje izbrano bitno ločljivost
        če je izbrana bitna ločljivost 10 je pričakovan podatkovni tip int16
    vrednosti ustvarjenih vzorcev naj bodo med
        MAX(2^bitna_ločljivost)/2 - 1
        -MAX(2^bitna_ločljivost)/2
    ton naj bo ustvarjen v obliki sinusoide
        začnite z vrednostjo 0 (ignorirajte fazo)
    (4 točke)

Pripravite še odsek kode s katerim lahko pripravljen modul poženete kot demo.

if __name__ == '__main__':
    pass

    ustvarite ton
        čas 1 sekunda
        vzorčevalna frekvenca 10 Hz
        bitna ločljivost 8 bitov
        frekvenca tona 5 Hz
    izrišite ustvarjen signal z matlotplib
        izrišite v enem oknu
        ustrezno poimenujte in označite x in y osi
            čas v sekundah
            vrednost
    (4 točke)

Oddaja mora vsebovati python modul generiraj.