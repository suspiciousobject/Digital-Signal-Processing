import numpy as np

# Параметры
M = 1024
L = 1024

np.random.seed(0)
x = np.random.randn(M) + 1j * np.random.randn(M)
y = np.random.randn(L) + 1j * np.random.randn(L)

# Вычисление эталонной свертки
u_ref = np.convolve(x, y, mode='full')

# Сохранение в бинарный файл
with open("./convolution_numpy.bin", "wb") as f:
    for val in u_ref:
        f.write(val.real.tobytes())
        f.write(val.imag.tobytes())

print("Эталонная свертка сохранена в data/convolution_numpy.bin")
