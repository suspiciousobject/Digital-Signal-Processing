import numpy as np

# Параметры
M = 1024
L = 1024

np.random.seed(0)
x = np.random.randn(M) + 1j * np.random.randn(M)
y = np.random.randn(L) + 1j * np.random.randn(L)

# Сохранение в бинарный файл
with open("signal_x.bin", "wb") as f:
    for val in x:
        f.write(val.real.tobytes())
        f.write(val.imag.tobytes())

with open("signal_y.bin", "wb") as f:
    for val in y:
        f.write(val.real.tobytes())
        f.write(val.imag.tobytes())

print("Файлы signal_x.bin и signal_y.bin созданы.")
