import numpy as np
from scipy import signal as sig

DTMF = np.array([["1", "2", "3"], ["4", "5", "6"], ["7", "8", "9"], ["*", "0", "#"]])
FREQUENCIES = [697, 770, 852, 941, 1209, 1336, 1477]

def find_closest_index(arr, target):
    closest_index = min(range(len(arr)), key=lambda i: abs(arr[i] - target))
    return closest_index

def compute_spectrogram(signal, sampling_frequency, min_tone_duration):
    window_size = ((int)(2**(int((sampling_frequency * (min_tone_duration / 4))) - 1))).bit_length()
    f, t, TFD = sig.spectrogram(signal, sampling_frequency, window=sig.windows.hamming(window_size), nperseg=abs(window_size), noverlap=int(window_size * 0.8))
    return f, t, TFD

def filter_amplitude(spectrogram, threshold_factor):
    avg_amplitude = np.average(spectrogram) * threshold_factor
    spectrogram[spectrogram < avg_amplitude] = np.nan
    return spectrogram

def analiziraj_dtmf(signal : np.ndarray, vzorcevalna_frekvenca : int, min_cas_ton : float, min_cas_pavza : float) -> np.ndarray:
    decoded_tones = []
    tone_lengths = []
    pause_lengths = []

    f, t, TFD = compute_spectrogram(signal, vzorcevalna_frekvenca, min_cas_ton)
    closest_indices = np.array([find_closest_index(f, freq) for freq in FREQUENCIES])

    relevant_freqs = TFD[closest_indices, :]
    lower_freqs = relevant_freqs[0:4, :]
    upper_freqs = relevant_freqs[4:, :]

    time_step = t[1] - t[0]

    filtered_spectrogram = filter_amplitude(relevant_freqs.copy(), 0.75)
    filtered_spectrogram = filter_amplitude(filtered_spectrogram, 0.4)

    is_tone = False
    current_length = 0
    for i in range(t.size):
        lower_freq_index = lower_freqs[:, i].argmax()
        upper_freq_index = upper_freqs[:, i].argmax()

        if np.amax(lower_freqs[:, i]) != 0 or np.amax(upper_freqs[:, i]) != 0:
            if not is_tone:
                decoded_tones.append(DTMF[lower_freq_index, upper_freq_index])
                tone_lengths.append(0)
                pause_lengths.append(current_length * time_step)
                current_length = 0
            is_tone = True
            current_length += 1
        else:
            if is_tone:
                tone_lengths[-1] = current_length * time_step
                current_length = 0
            is_tone = False
            current_length += 1

    if is_tone:
        tone_lengths[-1] = current_length * time_step
    else:
        pause_lengths.append(current_length * time_step)

    final_tones = []
    for i in range(len(decoded_tones)):
        if i == len(decoded_tones) - 1:
            if tone_lengths[i] >= min_cas_ton:
                final_tones.append(decoded_tones[i])
        elif tone_lengths[i] >= min_cas_ton and pause_lengths[i] >= min_cas_pavza:
            final_tones.append(decoded_tones[i])

    return np.array(final_tones, dtype="<U1").reshape(-1, 1)

from scipy.io import wavfile

def preberi_analiziraj_dtmf(file_path, min_cas_ton, min_cas_pavza):
    # Preberimo zvočni zapis
    vzorcevalna_frekvenca, signal = wavfile.read(file_path)

    # Analizirajmo zvočni zapis
    prepoznani_toni = analiziraj_dtmf(signal, vzorcevalna_frekvenca, min_cas_ton, min_cas_pavza)
    print("Prepoznani DTMF toni:", prepoznani_toni)

if __name__ == '__main__':
    print("Modul za DTMF analizo!")
    #preberi_analiziraj_dtmf('./dtmf_123_min_pulse_0.2_min_pause_0.1_noise_high.wav', 0.2, 0.1)

