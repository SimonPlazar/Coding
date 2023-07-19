import numpy as np

def analiziraj_vzorcevalno_mono(signal, dominantna_frekvenca):
    N = len(signal)
    signal_fft = np.fft.fft(signal, axis=0)
    signal_fft = np.abs(signal_fft[:N//2])
    signal_fft[0] = 0 # odstranimo DC komponento
    n = np.argmax(signal_fft) # indeks najvišje energije
    Fd = (n / N) * dominantna_frekvenca
    Fvz = Fd / n
    return Fvz

if __name__ == '__main__':
    t = np.arange(0, 1 * 250, 1) / 250
    sig = 1 * np.sin(2 * np.pi * 7 * t + 0 * np.pi)
    sig.shape = (-1, 1)
    Fvz = analiziraj_vzorcevalno_mono(sig, 7)
    print("Vzorčevalna frekvenca signala je:", Fvz)