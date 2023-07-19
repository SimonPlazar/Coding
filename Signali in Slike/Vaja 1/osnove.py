import numpy as np
from scipy.io import wavfile
import timeit as ti

def generiraj_vektor_nakljucno(stevilo_vzorcev: int) -> np.ndarray:
    return np.random.rand(stevilo_vzorcev, 1)
    

def beri_zvok_mono(pot_do_datoteke: str) -> np.ndarray:

    rate, data = wavfile.read(pot_do_datoteke)

    if(data.ndim == 1): #mono
        data = data.reshape((-1, 1))
        data = data / max(np.abs(data))

    else: #stereo
        data = np.mean(data, axis=1)
        data = data.reshape(-1, 1)
        data = data / max(np.abs(data))

    return data


def beri_zvok_stereo(pot_do_datoteke: str) -> np.ndarray:
    
    rate, data = wavfile.read(pot_do_datoteke)

    if(data.ndim == 1): #mono
        data = data / max(np.abs(data))
        #data = np.tile(data, 2)
        data = data.reshape((-1, 1))
        stereo = np.zeros([data.size,2])
        for i in range(data.size):
            stereo[i][0] = data[i]
            stereo[i][1] = data[i]
        data = stereo

    else: #stereo
        data = data.reshape((-1, 1))
        data = data / max(np.abs(data))
        data = data.reshape((-1, 2))
        
    return data


def normaliziraj(vektor: np.ndarray) -> np.ndarray:
    shape = vektor.shape
    vektor = vektor.reshape(-1,1)
    vektor = vektor.astype(np.float64)
    max = np.float64(0)
    for i in range(len(vektor)):
        if(abs(vektor[i])>max):
            max = abs(vektor[i])
    
    for i in range(len(vektor)):
        vektor[i] = vektor[i]/max

    vektor = vektor.reshape(shape)
    return vektor.astype(np.float64)
    #return (vektor / np.max(np.abs(vektor))).astype(np.float64)

def normaliziraj_vektorsko(vektor: np.ndarray) -> np.ndarray:
    return (vektor / np.max(np.abs(vektor))).astype(np.float64)

def testiraj_cas_izvajanja(vektor: np.ndarray) -> np.ndarray:
    start = ti.default_timer()
    normaliziraj(vektor)
    diff = ti.default_timer() - start

    start = ti.default_timer()
    normaliziraj_vektorsko(vektor)
    diff2 = ti.default_timer() - start 

    return np.array([[diff, diff2]])



#main function
if __name__ == "__main__":
    #print(generiraj_vektor_nakljucno(12))
    #print("mono: ", beri_zvok_mono("/home/simon/Desktop/churchbell.wav"), "\n")
    #print("stereo: ", beri_zvok_mono("/home/simon/Desktop/churchbell_stereo.wav"), "\n")
    #print("--------------------")
    #print("mono: ", beri_zvok_stereo("/home/simon/Desktop/churchbell.wav"))
    #print("stereo: ", beri_zvok_stereo("/home/simon/Desktop/churchbell_stereo.wav"))
    #print("--------------------")
    vektor = generiraj_vektor_nakljucno(1000000)
    print(vektor)
    print(testiraj_cas_izvajanja(vektor))


