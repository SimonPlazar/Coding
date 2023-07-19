Kratko časovna Fouriereva transformacija in analiza signala DTMF

Demonstrirajte znanja Kratko časovne Fouriereve transformacije z analizo vsebine podanega signala DTMF.

Primeri posnetkov:

čist signal, vrednosti 123456789*00, minimalen čas tona 0.1 s, minimalen čas pavze 0.1 s

prekratki pulzi, vrednosti 124679, minimalen čas tona 0.1 s, minimalen čas pavze 0.1 s

malo šuma, vrednosti 123, minimalen čas tona 0.2 s, minimalen čas pavze 0.1 s

srednje šuma, vrednosti 123, minimalen čas tona 0.2 s, minimalen čas pavze 0.1 s

veliko šuma, vrednosti 123, minimalen čas tona 0.2 s, minimalen čas pavze 0.1 s

primer signala "s", katerega uporablja avtomatični test

Paket s kodo za generiranje signalov in testiranje odpornosti na šum

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje funkcije:

def analiziraj_dtmf(signal : np.ndarray, vzorcevalna_frekvenca : int, min_cas_ton : float, min_cas_pavza : float) -> np.ndarray:
    pass

    funkcija prejme 4 parametre
        funkcija prejme vektor (x, 1), v katerem se nahaja signal za dekodiranje
            pravilno ustvarjen DTMF ton ne bodo krajši kot 65ms
        vzorčevalno frekvenco signala v hercih, ki pove koliko vzorcev na sekundo je v signalu
        minimalni čas trajanja tona v sekundah, ki pove minimalni čas, kateri mora biti DTMF ton prisoten, da ga upoštevamo kot pravilnega
        minimalni čas trajanja premora za tonom v sekundah, ki pove minimalni čas "tišine", kateri mora biti prisotna, da upoštevamo zaznan DTFM ton kot pravilen
    funkcija naj vrne vektor oblike (n, 1) za n prepoznanih vrednosti
        prepoznane vrednosti vključujejo znake: *, #, 0, 1, 2, 3, 4, 5, 6, 7, 8 in 9
    (56 točk) - rezultat funkcije se točkuje glede na naslednje kriterije
        18 točk za pravilno dekodiranje v čistem in pravilno ustvarjenem signalu
        11 točk za uspešno ignoriranje nepravilno ustvarjenih tonov
        27 točk za odpornost na šum
            0-27 točk se razporedi glede na jakost šuma
                 10 db nivo signala: + 2 točke
                   5 db nivo signala: + 2 točke
                   0 db nivo signala: + 2 točke
                  -2 db nivo signala: + 3 točke
                  -4 db nivo signala: + 3 točke
                  -6 db nivo signala: + 4 točke
                  -8 db nivo signala: + 5 točke
                -10 db nivo signala: + 6 točke

Pripravite še odsek kode, katero lahko samostojno zaženete kot demo:

if __name__ == '__main__':
    pass

    print("Modul za DTMF analizo!")

Zahtevano implementacijo oddajte v datoteki dtmfanaliza.py.