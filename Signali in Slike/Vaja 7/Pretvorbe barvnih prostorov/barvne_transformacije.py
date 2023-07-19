import numpy as np

def RGB_v_HSV(slika : np.ndarray) -> np.ndarray:
    slika = [[[float(j) for j in i[:3]] for i in row] for row in slika]
    for x in range(len(slika)):
        for y in range(len(slika[0])):
            R, G, B = [val / 255.0 for val in slika[x][y]]

            Cmax = max(R, G, B)
            Cmin = min(R, G, B)
            delta = Cmax - Cmin
            V = Cmax * 255

            if Cmax != 0:
                S = (delta / Cmax) * 255
            else:
                S = 0

            if delta != 0:
                if Cmax == R:
                    H = 60 * (((G - B) / delta) % 6)
                elif Cmax == G:
                    H = 60 * ((B - R) / delta + 2)
                elif Cmax == B:
                    H = 60 * ((R - G) / delta + 4)
            else:
                H = 0

            slika[x][y] = [H / 2, S, V]

    return slika

def HSV_v_RGB(slika : np.ndarray) -> np.ndarray:
    slika = [[[float(j) for j in i[:3]] for i in row] for row in slika]
    for x in range(len(slika)):
        for y in range(len(slika[0])):
            H, S, V = slika[x][y]
            H *= 2
            S /= 255
            V /= 255

            C = S * V
            H_ = H / 60
            X = C * (1 - abs(H_ % 2 - 1))
            m = V - C

            R1, G1, B1 = 0, 0, 0
            if 0 <= H_ < 1:
                R1, G1, B1 = C, X, 0
            elif 1 <= H_ < 2:
                R1, G1, B1 = X, C, 0
            elif 2 <= H_ < 3:
                R1, G1, B1 = 0, C, X
            elif 3 <= H_ < 4:
                R1, G1, B1 = 0, X, C
            elif 4 <= H_ < 5:
                R1, G1, B1 = X, 0, C
            elif 5 <= H_ < 6:
                R1, G1, B1 = C, 0, X

            slika[x][y] = [(val + m) * 255 for val in [R1, G1, B1]]

    return slika

def RGB_v_YCbCr(slika: np.ndarray) -> np.ndarray:
    # Definiraj koeficiente za pretvorbo v YCbCr
    YCbCr_from_RGB = np.array([[0.299, 0.587, 0.114],
                               [-0.168736, -0.331264, 0.5],
                               [0.5, -0.418688, -0.081312]])

    YCbCr = np.dot(slika, YCbCr_from_RGB.T)
    YCbCr[:, :, [1, 2]] += 128
    return np.uint8(YCbCr)

def YCbCr_v_RGB(slika: np.ndarray) -> np.ndarray:
    # Definiraj koeficiente za pretvorbo v RGB
    RGB_from_YCbCr = np.array([[1., 0., 1.402],
                               [1., -0.344136, -0.714136],
                               [1., 1.772, 0.]])

    RGB = slika.astype(np.float64)
    RGB[:, :, [1, 2]] -= 128
    RGB = np.dot(RGB, RGB_from_YCbCr.T)
    np.putmask(RGB, RGB > 255, 255)
    np.putmask(RGB, RGB < 0, 0)
    return np.uint8(RGB)

if __name__ == '__main__':
    import matplotlib.pyplot as plt

    # Preberemo sliko
    slika = plt.imread('slike\Mandel_zoom_11_satellite_double_spiral.jpg')

    # Prikaz originalne slike
    plt.imshow(slika)
    plt.title("Originalna slika")
    plt.show()

    # Pretvorba v HSV
    HSV = RGB_v_HSV(slika)
    RGB1 = HSV_v_RGB(HSV)

    # Prikaz pretvorjene slike
    plt.imshow(RGB1)
    plt.title("Pretvorjena slika")
    plt.show()

    # Pretvorba v YCbCr
    YCbCr = RGB_v_YCbCr(slika)
    RGB2 = YCbCr_v_RGB(YCbCr)

    # Prikaz pretvorjene slike
    plt.imshow(RGB2)
    plt.title("Pretvorjena slika")
    plt.show()

