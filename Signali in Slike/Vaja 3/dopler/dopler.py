import numpy as np
#import sounddevice as sd
import matplotlib.pyplot as plt
#from time import sleep

def generiraj_ton_mono(cas : float, vzorcevalna_frekvenca : int, frekvenca_tona : float) -> np.ndarray:
    
    t = np.arange(0, cas * vzorcevalna_frekvenca, 1) / vzorcevalna_frekvenca # vektor časovnih indeksov

    s = np.sin(2 * np.pi * frekvenca_tona * t) # vektor vzorcev signala

    return s

def interpolation_linear(signal, times, fs): # https://www.fridh.nl/2015/02/01/auralization-doppler-effect/
    k_r = np.arange(0, len(signal), 1)        # Create vector of indices
    k = k_r - times * fs                      # Create vector of warped indices 
    kf = np.floor(k).astype(int)              # Floor the warped indices. Convert to integers so we can use them as indices.
    R = ( (1.0-k+kf) * signal[kf] + (k-kf) * signal[kf+1] ) * (kf >= 0) #+ 0.0 * (kf<0)
    return R

def dopler_efekt_mono(vzorec : np.ndarray, vektor_fvz : int, oddaljenost : float, hitrost : float) -> np.ndarray:
    dolzina = ((oddaljenost * 2) / hitrost) # celotna dolzina zvoka

    dolzina_vzorca = len(vzorec) / vektor_fvz # dolzina vzorca

    if(dolzina_vzorca < dolzina):
        #podaljsamo
        while (dolzina_vzorca < dolzina):
            vzorec = np.concatenate((vzorec, vzorec))
            dolzina_vzorca = len(vzorec) / vektor_fvz

    stevlo_vzorcev = int(dolzina * vektor_fvz) # stevilo vzorcev, ki jih potrebujemo
    vzorec = vzorec[:stevlo_vzorcev]

    t = np.arange(stevlo_vzorcev) / vektor_fvz # nov vektor časovnih indeksov

    # https://www.fridh.nl/2015/02/01/auralization-doppler-effect/
    x = t * hitrost
    x -= x.max()/2.0
    y = np.zeros(stevlo_vzorcev)
    z = 100.0 * np.ones(stevlo_vzorcev)

    position_source = np.vstack((x,y,z)).T
    position_receiver = np.zeros(3)

    distance = np.linalg.norm((position_source - position_receiver), axis=-1)
    soundspeed = 343.0
    delay = distance / soundspeed

    delayed_linear = interpolation_linear(vzorec, delay, vektor_fvz)

    return delayed_linear

if __name__ == '__main__':
    signal = generiraj_ton_mono(1, 44100, 5000)

    DopplerSignal = dopler_efekt_mono(signal, 44100, 100, 25)

    #sd.play(DopplerSignal, 44100)
