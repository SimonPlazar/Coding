import numpy as np
import matplotlib.pyplot as plt

def normaliziraj_vektorsko(vektor):
    return vektor / np.max(np.abs(vektor))

def konvolucija_offline(signal: np.ndarray, impulz: np.ndarray, dolzina: str) -> np.ndarray:

    #if dolzina == 'polna':
    #    dolzina = signal.shape[0] + impulz.shape[0] - 1
    #elif dolzina == 'veljavna':
    #    new = np.zeros(signal.shape[0])
    #    new[0:impulz.shape[0]] = impulz
    #    impulz = new
    #    print(impulz)
    #    
    #else:
    #    print("Dolzina mora biti 'polna' ali 'veljavna'")
    #    return 0;


    if signal.ndim == 2:
        shape = signal.shape[1]
    else:
        shape = 1

    efekt = np.zeros((signal.shape[0] + impulz.shape[0]-1, shape))
    posnetekNorm = normaliziraj_vektorsko(signal)

    for n in np.arange(efekt.shape[0]):
        #efekt[n] = np.sum(np.multiply(posnetekNorm[0:impulz.shape[0]+1], impulz[0:n-impulz.shape[0]+1]))
        for k in np.arange(max(n-impulz.shape[0]+1, 0), min(n+1, signal.shape[0])):
            if shape > 1:
                for j in np.arange(shape):
                    efekt[n, j] += posnetekNorm[k, j] * impulz[n-k]
            else:
                efekt[n] += posnetekNorm[k] * impulz[n-k]

    return normaliziraj_vektorsko(efekt).dtype(np.float64)


if __name__ == '__main__':
    x = np.array([[1,2], [3,4], [5,6], [7,8], [9,10], [11,12], [13,14], [15,16], [17,18], [19,20]])
    y = np.array([[1,1], [2,2], [3,3], [4,4], [5,5], [6,6], [7,7], [8,8], [9,9], [10,10]])
    h = np.array([1,2,1])
    z = np.array([1,2,3,4,5,6,7,8,9,10])

    konvolucija = konvolucija_offline(z, h, "veljavna")
    print(konvolucija)

    plt.plot(z, label='signal')
    plt.plot(h, label='impulz')
    plt.plot(konvolucija, label='konvolved')
    plt.xlabel('čas (s)')
    plt.ylabel('vrednost (y)')
    plt.title('Konvolucija')
    plt.legend();

    plt.show()
