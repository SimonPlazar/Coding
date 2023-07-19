import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import iirnotch, lfilter, filtfilt, sawtooth, square

def odstrani_kvadratni_signal(s: np.ndarray, f: float, fvz: int) -> np.ndarray:
    nyquist = 0.5 * fvz
    harmonics = np.arange(1, fvz // (2 * f), 2) * f
    filtered_signal = s.copy()

    for h_freq in harmonics:
        bandwidth = h_freq * 0.1
        Q = h_freq / bandwidth
        b, a = iirnotch(h_freq, Q, fvz)
        filtered_signal = filtfilt(b, a, filtered_signal)

    return filtered_signal

if __name__ == '__main__':
    fvz = 1000
    t = np.arange(0, 2, 1 / fvz)
    sig = np.sin(2 * np.pi * t)
    #duty=(sig + 1)/2
    s_kvadratni = square(2 * np.pi * 30 * t)
    s_zagasti = sawtooth(2 * np.pi * 15 * t)
    s_vhodni = s_kvadratni + s_zagasti
    s_filtrirani = odstrani_kvadratni_signal(s_vhodni, 30, fvz)

    plt.figure()
    plt.subplot(4, 1, 1)
    plt.plot(t, s_kvadratni)
    plt.title('Kvadratni signal')
    plt.xlabel('Čas [s]')
    plt.ylabel('Amplituda')

    plt.subplot(4, 1, 2)
    plt.plot(t, s_zagasti)
    plt.title('Kvadratni signal')
    plt.xlabel('Čas [s]')
    plt.ylabel('Amplituda')

    plt.subplot(4, 1, 3)
    plt.plot(t, s_vhodni)
    plt.title('Vhodni signal')
    plt.xlabel('Čas [s]')
    plt.ylabel('Amplituda')

    plt.subplot(4, 1, 4)
    plt.plot(t, s_zagasti, label='Žagasti signal')
    plt.plot(t, s_filtrirani, label='Filtrirani signal')
    plt.legend()
    plt.title('Žagasti in filtrirani signal')
    plt.xlabel('Čas [s]')
    plt.ylabel('Amplituda')

    plt.tight_layout()
    plt.show()