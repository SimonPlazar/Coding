import numpy as np
import matplotlib.pyplot as plt

def minmax(vhod):
	# To je komentar.
	
	izhod1 = min(vhod)
	izhod2 = max(vhod)
	
	return izhod1, izhod2


if __name__ == '__main__':
	
	v = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 0])
	
	v_min, v_max = minmax(v)
	
	print('min:', v_min, 'max:', v_max)
