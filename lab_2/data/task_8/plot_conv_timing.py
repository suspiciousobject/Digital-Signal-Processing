import numpy as np
import matplotlib.pyplot as plt

# Чтение данных
data = np.loadtxt("timing_conv_data.txt", skiprows=1, dtype=str)
case = data[:, 0]
N = data[:, 1].astype(int)
time_direct = data[:, 2].astype(float)
time_fft = data[:, 3].astype(float)

# Разделение на два случая
mask_fixed = case == 'Fixed_M'
mask_equal = case == 'Equal_ML'

N_fixed = N[mask_fixed]
time_direct_fixed = time_direct[mask_fixed]
time_fft_fixed = time_fft[mask_fixed]

N_equal = N[mask_equal]
time_direct_equal = time_direct[mask_equal]
time_fft_equal = time_fft[mask_equal]

# Построение графиков
fig, axes = plt.subplots(2, 1, figsize=(10, 8))

# Случай 1: M=512, L варьируется
ax1 = axes[0]
ax1.loglog(N_fixed, time_direct_fixed, 'o-', label='Прямая свертка', linewidth=2)
ax1.loglog(N_fixed, time_fft_fixed, 's-', label='БПФ', linewidth=2)
ax1.set_xlabel('Длина L')
ax1.set_ylabel('Время, мс')
ax1.set_title('Случай 1: M=512, L=2^n')
ax1.legend()
ax1.grid(True, which="both", linestyle='--')

# Случай 2: M=L=2^n
ax2 = axes[1]
ax2.loglog(N_equal, time_direct_equal, 'o-', label='Прямая свертка', linewidth=2)
ax2.loglog(N_equal, time_fft_equal, 's-', label='БПФ', linewidth=2)
ax2.set_xlabel('Длина M=L')
ax2.set_ylabel('Время, мс')
ax2.set_title('Случай 2: M=L=2^n')
ax2.legend()
ax2.grid(True, which="both", linestyle='--')

plt.tight_layout()
plt.savefig('convolution_timing_comparison.png', dpi=300, bbox_inches='tight')
print("Графики сохранены как convolution_timing_comparison.png")
plt.show()
