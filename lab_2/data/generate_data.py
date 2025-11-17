# data/generate_data.py

import numpy as np
np.random.seed(0)
N = 1024
x = np.random.randn(N) + 1j * np.random.randn(N)

# data/input_signal.bin
with open("data/input_signal.bin", "wb") as f:
    for val in x:
        f.write(val.real.tobytes())
        f.write(val.imag.tobytes())

# data/dft_numpy.bin
y = np.fft.fft(x) / np.sqrt(N)
with open("data/dft_numpy.bin", "wb") as f:
    for val in y:
        f.write(val.real.tobytes())
        f.write(val.imag.tobytes())
