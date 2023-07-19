Fouriereva transformacija in analiza vzorčevalne frekvence

Demonstrirajte znanja Fouriereve transformacije z analizo vzorčevalne frekvence podanega signala.

Pripravite skripto Python, ki ima definirane (vsebuje) naslednje funkcije:

def analiziraj_vzorcevalno_mono(signal, dominantna_frekvenca):

    funkcija prejme 2 parametre
        funkcija prejme vektor (x, 1), v katerem se nahaja normaliziran signal za obdelavo
        dominantno frekvenco v hercih, ki pove frekvenco z največjo energijo
    funkcija vrne število
        število naj bo zaznana vzorčevalna frekvenca signala
    funkcija naj analizo opravi s pomočjo transformacije v frekvenčni prostor
        pomagajte si s formulo: Fd = (n / N) * Fvz
            Fd - dominantna frekvenca (vsebuje največ energije)
            n - indeks zaznane energije v frekvenčnem prostoru
            N - število vzorcev signala v časovnem prostoru
            Fvz - vzorčevalna frekvenca

        Opozorilo: test daje oblikovan vektor oblike (x, 1). Za pravilno izvedbo dodajte "axis" parameter funkciji fft ali pa uporabite funkcijo np.fft.fftn
    (22 točk)

Pripravite še odsek kode, katero lahko samostojno zaženete kot demo:

if __name__ == '__main__':

    import numpy as np
    generirajte testni signal
        t = np.arange(0, 1 * 250, 1) / 250
        sig = 1 * np.sin(2 * np.pi * 7 * t + 0 * np.pi)
        sig.shape = (-1, 1)
    kličite analiziraj_vzorcevalno_mono(sig, 7)
    izpišite rezultat

 

Zahtevano implementacijo oddajte v datoteki ftanaliza.py.

V arhivu naloga.zip oddajte pripravljen dokument.