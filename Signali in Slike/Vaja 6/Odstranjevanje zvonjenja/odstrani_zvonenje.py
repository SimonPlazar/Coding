import numpy as np
from pydub import AudioSegment
from scipy.fftpack import fft
from scipy.io.wavfile import read, write
from scipy.signal import iirnotch, filtfilt, butter, sosfiltfilt

def load_mp3(file_path):
    audio = AudioSegment.from_mp3(file_path)
    audio = audio.set_channels(1)
    samples = np.array(audio.get_array_of_samples())
    return audio.frame_rate, samples

def find_frequencies(signal, rate, threshold=0.05):
    N = len(signal)
    T = 1.0 / rate

    yf = fft(signal)
    xf = np.linspace(0.0, 1.0 / (2.0 * T), N // 2)

    peaks = []
    max_val = 2.0 / N * np.abs(yf[:N // 2]).max()
    for i in range(1, N // 2 - 1):
        if (
            2.0 / N * np.abs(yf[i]) > threshold * max_val
            and yf[i - 1] < yf[i]
            and yf[i] > yf[i + 1]
        ):
            peaks.append(xf[i])

    return peaks

def butter_bandstop_filter(f_low, f_high, fs, order=5):
    nyquist = 0.5 * fs
    low = f_low / nyquist
    high = f_high / nyquist
    sos = butter(order, [low, high], btype='bandstop', analog=False, output='sos')
    return sos

def odstrani_signal(s: np.ndarray, ringing_freqs: np.ndarray, fvz: int) -> np.ndarray:
    filtered_signal = s.copy()

    for idx, freq in enumerate(ringing_freqs):
        print(f"Obdelava frekvence {idx + 1} od {len(ringing_freqs)}: {freq} Hz")
        bandwidth = freq * 0.5
        f_low = freq - bandwidth / 2
        f_high = freq + bandwidth / 2
        sos = butter_bandstop_filter(f_low, f_high, fvz)
        filtered_signal = sosfiltfilt(sos, filtered_signal)

    return filtered_signal


if __name__ == '__main__':

    rate_zvonenje, data_zvonenje = load_mp3("Old-phone-ringtone.mp3")

    ringing_freqs = find_frequencies(data_zvonenje, rate_zvonenje)

    print("Najdene frekvence zvonjenja:", ringing_freqs)

    rate_himna, data_himna = read("portugalska_himna_zvonenje.wav")

    filtered_data = odstrani_signal(data_himna, ringing_freqs, rate_himna)

    # Shranite filtrirani avdio posnetek
    write("zvonenje.wav", rate_himna, filtered_data.astype(np.int16))
