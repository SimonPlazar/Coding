import matplotlib.pyplot as plt
import scipy.ndimage as ndi
import numpy as np
from scipy import signal

def conv_2d_library(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:

    R = signal.convolve2d(slika[:, :, 0], jedro, "same")
    G = signal.convolve2d(slika[:, :, 1], jedro, "same")
    B = signal.convolve2d(slika[:, :, 2], jedro, "same")

    return np.dstack([R, G, B])

def conv_2d(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:
    # Dimenzije
    H, W, _ = slika.shape
    N, M = jedro.shape

    # Izračun središče jedra
    C_N, C_M = N // 2, M // 2

    # Priprava vhodne slike
    tmp = np.pad(slika, ((C_N, C_M), (C_N, C_M), (0, 0)), mode='constant')

    # Pripravljenje izhodne slike
    izhod = np.zeros((H, W, 3), dtype=np.float32)

    # Izvedi konvolucijo
    for i in range(H):
        for j in range(W):
            izhod[i, j] = (tmp[i:i + N, j:j + M] * jedro).sum(axis=(0, 1))

    return izhod


def RGB_glajenje(slika: np.ndarray, faktor: float) -> np.ndarray:
    # preveri, če so dimenzije pravilne
    assert len(slika.shape) == 3, "Napačne dimenzije vhodnih podatkov."
    assert slika.shape[2] == 3, "Slika mora biti oblike (H, W, 3)."

    # ustvari prazno sliko za rezultat
    result = np.zeros_like(slika, dtype=np.float32)

    # za vsak kanal RGB izvedi glajenje
    for c in range(3):
        result[..., c] = ndi.gaussian_filter(slika[..., c], sigma=faktor)

    # pretvori nazaj v uint8 in vrni
    return (result + 0.5).astype(np.uint8)

def RGB_ostrenje(slika: np.ndarray, faktor_glajenja: float, faktor_ostrenja: float) -> np.ndarray:
    # preveri, če so dimenzije pravilne
    assert len(slika.shape) == 3, "Napačne dimenzije vhodnih podatkov."
    assert slika.shape[2] == 3, "Slika mora biti oblike (H, W, 3)."

    # pretvori sliko v float32 za izračune
    slika = slika.astype(np.float32)

    # ustvari prazno sliko za rezultat
    result = np.zeros_like(slika, dtype=np.float32)

    # za vsak kanal RGB izvedi ostrenje
    for c in range(3):
        # zgladi sliko
        blurred = ndi.gaussian_filter(slika[..., c], sigma=faktor_glajenja)

        # ustvari masko
        mask = slika[..., c] - blurred

        # dodaj masko na originalno sliko za ostrenje
        result[..., c] = slika[..., c] + (faktor_ostrenja * mask)

    # omeji vrednosti na interval [0, 255] in pretvori nazaj v uint8
    result = np.clip(result, 0, 255).astype(np.uint8)

    return result

if __name__ == '__main__':
    # Naloži sliko
    slika = plt.imread('slika.jpg')

    # Izberi faktor za glajenje in ostrenje
    faktor_glajenja = 3.0
    faktor_ostrenja = 1.5

    # Izvedi glajenje in ostrenje
    glajena_slika = RGB_glajenje(slika, faktor_glajenja)
    ostrena_slika = RGB_ostrenje(slika, faktor_glajenja, faktor_ostrenja)

    # Prikaz slik
    plt.imshow(slika)
    plt.title("Osnovna slika")
    plt.show()

    plt.imshow(glajena_slika)
    plt.title("Glajena slika")
    plt.show()

    plt.imshow(ostrena_slika)
    plt.title("Ostrena slika")
    plt.show()

    jedro = np.array([[1, 1, 1], [1, 1, 1], [1, 1, 1]]) / 9

    knjiznica = conv_2d_library(slika, jedro)

    plt.imshow(knjiznica)
    plt.title("Konvolucija s knjižnico")
    plt.show()

    moje = conv_2d(slika, jedro)

    plt.imshow(moje)
    plt.title("Konvolucija z lastno implementacijo")
    plt.show()

