import numpy as np
import matplotlib.pyplot as plt

def generiraj_ton_mono(cas : float, vzorcevalna_frekvenca : int, bitna_locljivost : int, frekvenca_tona : float) -> np.ndarray:
    
    t = np.arange(0, cas * vzorcevalna_frekvenca, 1) / vzorcevalna_frekvenca # vektor časovnih indeksov

    s = np.sin(2 * np.pi * frekvenca_tona * t) # vektor vzorcev signala

    s_bit = np.round((s+1)/2*(2**bitna_locljivost-1)-2**(bitna_locljivost-1))
    s_bit_norm = s_bit/2**(bitna_locljivost-1)

    if bitna_locljivost <= 8:
        tip = np.int8
    elif bitna_locljivost <= 16:
        tip = np.int16
    elif bitna_locljivost <= 32: 
        tip = np.int32
    else:
        tip = np.int64

    #s_bit_norm = s_bit_norm/2**(bitna_locljivost-1)
    s_bit_norm.astype(tip)

    return s_bit_norm


if __name__ == "__main__":
    cas = 1
    vzorcevalna_frekvenca = 567
    bitna_locljivost = 2
    frekvenca_tona = 5

    s = generiraj_ton_mono(cas, vzorcevalna_frekvenca, bitna_locljivost, frekvenca_tona)

    t = np.arange(0, cas * vzorcevalna_frekvenca, 1) / vzorcevalna_frekvenca

    # pripravi graf za risanje
    fig, ax = plt.subplots()
    
    ax.set_xlim((0, 1))
    ax.set_ylim((-1, 1))
    ax.set_ylabel('vrednost')
    ax.set_xlabel('čas (s)')
    
    # izris za vzorcen signal
    l_samp = ax.stem(t, s, linefmt='r', markerfmt='r', label='vzorčen signal')
    plt.legend(loc='upper right')