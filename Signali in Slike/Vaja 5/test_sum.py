
import unittest
import inspect
import numpy as np

import dtmf_generator
import dtmfanaliza

if __name__ == '__main__':
    for snr in [10, 5, 0, -2, -4, -6, -8, -10]:
        print(f'signal to noise ratio: {snr} dB')
        mismatches=0
        reps = 5
        for r in range(reps):
            d_vals = np.array((*'0123456789*0#',))
            d_inds = np.random.randint(0, d_vals.shape[0], 20)
            d_orig = d_vals[d_inds]

            sig, d_ref = dtmf_generator.generiraj(d_orig,
                                                    fvz=22050,
                                                    pulse_len_range=(0.2, 0.25),
                                                    pause_len_range=(0.1, 0.15),
                                                    snr_level=snr)
            d_orig.shape = [-1, 1]
            d_ref.shape = [-1, 1]
            d_res = dtmfanaliza.analiziraj_dtmf(sig,
                                                vzorcevalna_frekvenca=22050,
                                                min_cas_ton=0.200,
                                                min_cas_pavza=0.100)

            print('ref: '+''.join(d_ref.ravel()))
            print('res: '+''.join(d_res.ravel()))
            if d_res.shape==d_ref.shape and \
               (d_res==d_ref).all():
                print('   match')
            else:
                print('NO match')
                mismatches += 1

        print('')
        if mismatches >= reps/2:
            print('vec kot polovica ponovitev je bila neuspesna, '\
                 +'ne nadaljujem preizkusanje')
            break

            

            


