import numpy as np

def generiraj(data,
              fvz=44100,
              pulse_len_range=(0.065,0.1),
              pause_len_range=(0.065,0.1),
              fault_rate=0,
              fault_len_range=(0.005, 0.05),
              snr_level=None):
    '''
    data - enumeratable list, tuple or array
        values to be encoded with DTMF, numbers from 0 to 9
    fvz - int
        sampling frequency for the generated signal
    pulse_len_range - (float, float)
        range of possible tone pulse lengths, minimal and maximal length in s
    pause_len_range - (float, float)
        range of possible pause lengths, minimal and maximal length in s
    fault_rate - float
        rate of faults when conding. This is the fraction of data values that
        are selected to be encoded with faults. That means that the tone 
        length is shorter than expected (the length is selected from the 
        fault_len_range)
    fault_len_range - (float, float)
        range of posible fault lengths, minimal and maximal length in s
    snr_level - float
        singal to noise ratio, decibels

    Returns:
    signal - np.array, (1, x)
        DTMF signal encoded with the data

    data_new - list
        The signals encoded with the correct length.
    '''

    freq_dict = {
        '1': (697, 1209),
        '2': (697, 1336),
        '3': (697, 1477),
        '4': (770, 1209),
        '5': (770, 1336),
        '6': (770, 1477),
        '7': (852, 1209),
        '8': (852, 1336),
        '9': (852, 1477),
        '*': (941, 1209),
        '0': (941, 1336),
        '#': (941, 1477)
        }

    for v in data:
        if v not in freq_dict:
            raise Exception(f'vrednost {v} ne obstaja v tabeli frekvenc, ni mogoce kodirati')


    N = len(data)
    pulse_len = np.random.rand(N)*(pulse_len_range[1]-pulse_len_range[0])+pulse_len_range[0]
    pause_len = np.random.rand(N)*(pause_len_range[1]-pause_len_range[0])+pause_len_range[0]

    fault_count = int(N*fault_rate)
    if fault_count > 0:
        fault_inds = np.random.permutation(N)[:fault_count]
        fault_len = np.random.rand(fault_count)*(fault_len_range[1]-fault_len_range[0])+fault_len_range[0]
        pulse_len[fault_inds] = fault_len
        data_new = [v for n,v in enumerate(data) if n not in fault_inds]
    else:
        data_new = data

    toni =  []
    for n, v in enumerate(data):

        f1, f2 = freq_dict[v]

        t_pulse = pulse_len[n]
        t_pause = pause_len[n]


        ton = generiraj_ton(f1, t_pulse, fvz)
        ton += generiraj_ton(f2, t_pulse, fvz)
        ton *= 0.5

        toni += [ton]
        toni += [np.zeros(int(fvz*t_pause))]

    signal = np.concatenate(toni)

    if snr_level is not None:
        #snr_level  = 10*np.log10(np.mean(signal**2)/np.mean(noise**2))
        #10**(snr_level/10) = np.mean(signal**2)/np.mean(noise**2)
        noise_std = (np.mean(signal**2)/10**(snr_level/10))**0.5
        noise = np.random.randn(*signal.shape)*noise_std
        signal += noise

    return signal, data_new

def generiraj_ton(f, t, fvz):
    x = np.arange(int(t*fvz))/fvz
    y = np.sin(2*np.pi*f*x)

    return y


if __name__ == '__main__' and False:
    import scipy.signal

    fvz=8000
    snr_level = 0 # SNR v DB
    podatki = '123456789*0#'
    s, podatki_vpisani = generiraj(podatki, # seznam podatkov
                         fvz=fvz, # vzorcevalna frekvenca
                        pulse_len_range=(0.1, 0.3), # mozne dolzine tona
                        pause_len_range=(0.1, 0.3), # mozne dolzine premora
                        fault_rate = 0.3, # delez napak v kodiranju
                        fault_len_range=(0.01, 0.05), # mozne dolzine tona ob napaki
                        snr_level=100)#snr v decibelih

    nperseg = int(0.1*fvz/2)
    f, t, S_stft = scipy.signal.stft(s, fvz,
                                    window='boxcar',
                                    nperseg=nperseg,
                                    noverlap=3*nperseg//4)
                                    #nfft=1024)

    pyplot.pcolormesh(t, f, np.abs(S_stft))
