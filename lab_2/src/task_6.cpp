// /src/task_6.cpp
#include "../include/io_utils.h"
#include "../include/fft.h"  // используем вашу реализацию БПФ из задания 2
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using cd = std::complex<double>;

// Функция для нахождения минимальной степени двойки >= n
size_t next_power_of_two(size_t n) {
    if (n <= 1) return 1;
    size_t p = 1;
    while (p < n) p <<= 1;
    return p;
}

std::vector<cd> convolve_fft(const std::vector<cd>& x, const std::vector<cd>& y) {
    size_t M = x.size();
    size_t L = y.size();
    size_t N_conv = M + L - 1;           // длина результата
    size_t N_fft = next_power_of_two(N_conv);  // длина БПФ (степень двойки)

    // Дополнение нулями до длины N_fft
    std::vector<cd> x_pad(N_fft, 0.0);
    std::vector<cd> y_pad(N_fft, 0.0);
    for (size_t i = 0; i < M; ++i) x_pad[i] = x[i];
    for (size_t i = 0; i < L; ++i) y_pad[i] = y[i];

    // Шаг 2: БПФ
    auto X_hat = fft(x_pad);
    auto Y_hat = fft(y_pad);

    // Шаг 3: Покомпонентное произведение и масштабирование
    std::vector<cd> U_hat(N_fft);
    double scale = sqrt(static_cast<double>(N_fft));
    for (size_t i = 0; i < N_fft; ++i) {
        U_hat[i] = X_hat[i] * Y_hat[i] * scale;
    }

    // Шаг 4: ОБПФ
    auto U = ifft(U_hat);

    // Шаг 5: Возвращаем первые M + L - 1 элементов
    U.resize(N_conv);
    return U;
}

int main() {
    const size_t M = 1024;
    const size_t L = 1024;

    auto x = read_signal("../data/signal_x.bin", M);
    auto y = read_signal("../data/signal_y.bin", L);

    auto u_fft = convolve_fft(x, y);

    write_signal(u_fft, "../data/task_6/convolution_fft.txt");

    std::cout << "Свёртка через БПФ сохранена в convolution_fft.txt\n";
    return 0;
}
