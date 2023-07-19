#import numpy
#import matplotlib
import numpy as np
import matplotlib.pyplot as plt

# premenljivke (index se začne od 0)
a = 1
B = [1, 2, 3, 4]
B[2] = 8
C = [[1, 2, 3, 4], [5, 6, 7, 8], [1, 1, 1, 1]]
C[2][1] = 7

# matematične operacije
a = 4
B = np.matrix([1, 2, 3, 4])
C = a * B

A = np.matrix([[1, 2], [3, 4]])
B = np.matrix([[4, 3], [2, 1]])
C = A*B

A = np.matrix([[1, 2, 3], [4, 5, 6]])
B = np.matrix([[1, 4], [2, 5], [3, 6]])
C = A * B

A = np.matrix([[1, 2], [3, 4]])
B = np.matrix([[1, 0], [0, 1]])
C = np.dot(A,B)

a = 4
B = np.matrix([[1, 2], [3, 4]])
C = a + B

# funkcije
A = [1, 2, 3, 4]
B = np.size(A)
C = np.max(A)
D = np.min(A)
S = np.sum(A)
P = np.prod(A)

A = np.matrix([[1, 2, 3, 4], [5, 6, 7, 8]])
N = A.ndim
By, Bx = A.shape
C = np.max(A)
D = np.min(A)

A = [1, 5, 3, 2]
B = np.sort(A)
I = np.argsort(A)

# grafi
a = 1
f = 1
t = numpy.arange(0, 10, 0.01)
A = a * numpy.sin(t * f)

plt.plot(A)
plt.show()

f = 2
A = a * numpy.sin(t * f)

plt.plot(A, 'r')
plt.show()

f = 4
A = a * numpy.sin(t * f)

plt.plot(A, 'r')
plt.plot(A * 2, 'b')
plt.show()

plt.plot(A)
plt.plot(A * 2, 'r')
plt.show()

# lastne funkcije
import minmax
v = numpy.array([1, 2, 3, 4, 5, 6, 7])
B, C = minmax.minmax(A)

# zvok
from scipy.io import wavfile
Fs, y = wavfile.read("churchbell.wav")

print(Fs)
print(y.shape)

plt.plot(y)
plt.show()


import sounddevice as sd
sd.play(y, Fs)

