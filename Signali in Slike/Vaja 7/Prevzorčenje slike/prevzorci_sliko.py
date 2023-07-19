import numpy as np
import scipy.ndimage

def prevzorci_sliko(slika: np.ndarray, nova_visina: int, nova_sirina: int) -> np.ndarray:
    # Preveri, ali je slika barvna ali sivinska
    if len(slika.shape) == 3:
        barvna = True
    elif len(slika.shape) == 2:
        barvna = False

    # Izračun razmerja med originalno in novo velikostjo slike
    razmerje_visina = nova_visina / slika.shape[0]
    razmerje_sirina = nova_sirina / slika.shape[1]

    # Filtriranje višjih frekvenc z uporabo Gaussovega filtra
    if barvna:
        slika = scipy.ndimage.gaussian_filter(slika, sigma=[razmerje_visina, razmerje_sirina, 0])
    else:
        slika = scipy.ndimage.gaussian_filter(slika, sigma=[razmerje_visina, razmerje_sirina])

    # Uporaba scipy.ndimage.zoom za prevzorčenje
    if barvna:
        prevzorcena_slika = scipy.ndimage.zoom(slika, (razmerje_visina, razmerje_sirina, 1))
    else:
        prevzorcena_slika = scipy.ndimage.zoom(slika, (razmerje_visina, razmerje_sirina))

    # Pretvarjanje podatkovnega tipa na isti tip kot vhodna slika
    prevzorcena_slika = prevzorcena_slika.astype(slika.dtype)

    return prevzorcena_slika

def fft2_resample(x: np.ndarray, new_shape: tuple) -> np.ndarray:
    # Izračunamo 2D FFT in izvedemo premik frekvence 0 v središče
    fft = np.fft.fftshift(np.fft.fft2(x))
    fft_resampled = np.zeros(new_shape, dtype=complex)

    # Izračunamo minimalne dimenzije za obrezovanje ali dodajanje frekvenc
    min_x = min(x.shape[0], new_shape[0]) // 2
    min_y = min(x.shape[1], new_shape[1]) // 2

    # Obrezovanje ali dodajanje frekvenc, da dosežemo želeno velikost
    fft_resampled[new_shape[0] // 2 - min_x: new_shape[0] // 2 + min_x,
    new_shape[1] // 2 - min_y: new_shape[1] // 2 + min_y] = \
        fft[x.shape[0] // 2 - min_x: x.shape[0] // 2 + min_x, x.shape[1] // 2 - min_y: x.shape[1] // 2 + min_y]

    return np.fft.ifft2(np.fft.ifftshift(fft_resampled))

def prevzorci_sliko_fft(slika : np.ndarray, nova_visina : int, nova_sirina : int) -> np.ndarray:
    # Preveri, ali je slika barvna ali sivinska
    if slika.ndim == 3:
        # Izvajamo vzorčenje Fouriera za vsak barvni kanal posebej in shranjujemo rezultate v ustrezni kanal rezultatne slike
        rezultat = np.empty((nova_visina, nova_sirina, 3), dtype=slika.dtype)

        for i in range(3):
            rezultat[..., i] = np.abs(fft2_resample(slika[..., i], (nova_visina, nova_sirina)))
    else:
        # Če je slika enobarvna izvajamo vzorčenje Fouriera neposredno na sliki
        rezultat = np.abs(fft2_resample(slika, (nova_visina, nova_sirina)))

    return rezultat


if __name__ == '__main__':
    import matplotlib.pyplot as plt

    slika_barvna = plt.imread('slike\Mandel_zoom_11_satellite_double_spiral.jpg')

    plt.imshow(slika_barvna)
    plt.title("Originalna barvna slika")
    plt.show()

    slika_siva = plt.imread('slike\Bikesgray.jpg')
    plt.imshow(slika_siva)
    plt.title("Originalna siva slika")
    plt.show()


    plt.imshow(prevzorci_sliko(slika_barvna, 1000, 500))
    plt.title("Prevzorcena barvna slika")
    plt.show()

    plt.imshow(prevzorci_sliko(slika_siva, 1000, 500))
    plt.title("Prevzorcena siva slika")
    plt.show()


    plt.imshow(prevzorci_sliko_fft(slika_barvna, 1000, 500))
    plt.title("Prevzorcena barvna slika")
    plt.show()

    plt.imshow(prevzorci_sliko_fft(slika_siva, 1000, 500))
    plt.title("Prevzorcena siva slika")
    plt.show()