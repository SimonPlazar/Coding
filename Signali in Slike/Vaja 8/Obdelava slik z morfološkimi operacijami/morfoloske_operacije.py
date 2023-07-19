import matplotlib.pyplot as plt
import numpy as np
from scipy.ndimage import binary_erosion, binary_dilation
from PIL import Image

def open(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:
    eroded = binary_erosion(slika, jedro)
    opened = binary_dilation(eroded, jedro)
    return opened.astype(bool)

def close(slika: np.ndarray, jedro: np.ndarray) -> np.ndarray:
    dilatirana_slika = binary_dilation(slika, structure=jedro)
    rezultat = binary_erosion(dilatirana_slika, structure=jedro)
    return rezultat.astype(bool)

def hit_miss(slika: np.ndarray, jedro_hit: np.ndarray, jedro_miss: np.ndarray) -> np.ndarray:
    erodirana_hit = binary_erosion(slika, structure=jedro_hit)
    erodirana_miss = binary_erosion(np.invert(slika), structure=jedro_miss)
    rezultat = np.logical_and(erodirana_hit, erodirana_miss)
    return rezultat.astype(bool)

if __name__ == '__main__':
    # Naložimo sliko iz lokalnega direktorija
    slika = Image.open("slika.ppm")
    slika = np.array(slika)

    # Definiramo morfološko jedro
    jedro = np.ones((3, 3, 3), dtype=bool)

    # Uporabimo funkcije na sliki s podanim jedrom
    slika_open = open(slika, jedro)
    slika_close = close(slika, jedro)
    slika_hit_miss = hit_miss(slika, jedro, np.invert(jedro))

    # Prikaz slik
    plt.imshow(slika.astype(np.uint8), cmap='gray')
    plt.title("Osnovna slika")
    plt.axis('off')
    plt.show()

    plt.imshow(jedro.astype(np.uint8), cmap='gray')
    plt.title("Jedro")
    plt.axis('off')
    plt.show()

    plt.imshow(slika_open.astype(np.uint8), cmap='gray')
    plt.title("Open slika")
    plt.axis('off')
    plt.show()

    plt.imshow(slika_close.astype(np.uint8), cmap='gray')
    plt.title("Close slika")
    plt.axis('off')
    plt.show()

    plt.imshow(slika_hit_miss.astype(np.uint8), cmap='gray')
    plt.title("Hit-Miss slika")
    plt.axis('off')
    plt.show()





