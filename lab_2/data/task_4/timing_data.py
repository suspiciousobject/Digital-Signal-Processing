import numpy as np
import matplotlib.pyplot as plt

# Чтение данных из файла
data = np.loadtxt("timing_data.txt", skiprows=1)
N = data[:, 0]           # длины сигналов
time_dft = data[:, 1]    # время ДПФ в мс
time_fft = data[:, 2]    # время БПФ в мс

# Построение графика в логарифмическом масштабе
plt.figure(figsize=(10, 6))
plt.loglog(N, time_dft, 'o-', label='ДПФ (O(N²))', linewidth=2, markersize=6)
plt.loglog(N, time_fft, 's-', label='БПФ (O(N log N))', linewidth=2, markersize=6)

# Оформление графика
plt.xlabel('Длина сигнала $N$')
plt.ylabel('Время выполнения, мс')
plt.title('Сравнение времени вычисления ДПФ и БПФ\n(логарифмический масштаб)')
plt.legend()
plt.grid(True, which="both", linestyle='--', alpha=0.7)
plt.tight_layout()

# Сохранение графика в файл
plt.savefig('timing_comparison.png', dpi=300, bbox_inches='tight')
