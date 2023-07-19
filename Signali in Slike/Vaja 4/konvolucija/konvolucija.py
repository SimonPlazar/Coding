import numpy as np
import matplotlib.pyplot as plt

def konvolucija_fft(signal: np.ndarray, impulz: np.ndarray, rob: str) -> np.ndarray:
    N = len(signal)
    K = len(impulz)

    impulz_padded = np.pad(impulz, (0, N-K), mode='constant', constant_values=0)

    # Padding the signal and impulse response according to the specified edge handling
    if rob == 'ničle':
        signal_padded = np.pad(signal, (0, K-1), mode='constant', constant_values=0)
        impulz_padded = np.pad(impulz, (0, N-1), mode='constant', constant_values=0)
    elif rob == 'zrcaljen':
        signal_padded = np.pad(signal, (K-1, K-1), mode='reflect')
        impulz_padded = np.pad(impulz, (N-1, N-1), mode='reflect')
    elif rob == 'krožni':
        signal_padded = np.pad(signal, (K-1, K-1), mode='wrap')
        impulz_padded = np.pad(impulz, (N-1, N-1), mode='wrap')

    # Calculating the convolution in frequency domain
    signal_fft = np.fft.fft(signal_padded)
    impulz_fft = np.fft.fft(impulz_padded)
    output_fft = signal_fft * impulz_fft
    output = np.fft.ifft(output_fft)[:N].real

    # Reshaping the output to match the dimensions of the input signal
    if signal.ndim > 1:
        output = output.reshape((N, signal.shape[1]))

    return output


if __name__ == '__main__':
    # Creating a demo signal and impulse response
    signal = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    impulz = np.array([0.5, 1, 0.5])

    # Performing the convolution with different edge handling methods
    output1 = konvolucija_fft(signal, impulz, 'ničle')
    output2 = konvolucija_fft(signal, impulz, 'zrcaljen')
    output3 = konvolucija_fft(signal, impulz, 'krožni')

    # Plotting the signal, impulse response
    plt.subplot(2, 2, 1)
    plt.plot(signal)
    plt.title('Signal')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')

    plt.subplot(2, 2, 2)
    plt.stem(impulz)
    plt.title('Impulse Response')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')

    plt.tight_layout()
    plt.show()

    # Plotting the convolution results
    plt.subplot(2, 2, 1)
    plt.plot(output1)
    plt.title('Convolution (Zero Padding)')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')

    plt.subplot(2, 2, 2)
    plt.plot(output2)
    plt.title('Convolution (Mirror Padding)')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')

    plt.subplot(2, 2, 3)
    plt.plot(output3)
    plt.title('Convolution (Circular Padding)')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')

    plt.tight_layout()
    plt.show()