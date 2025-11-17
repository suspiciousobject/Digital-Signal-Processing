// src/task_7.cpp
#include "../include/io_utils.h"
#include "../include/fft.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <iomanip>

using cd = std::complex<double>;

// Функция прямой свертки
std::vector<cd> convolve_direct(const std::vector<cd>& x, const std::vector<cd>& y) {
    size_t M = x.size();
    size_t L = y.size();
    size_t N = M + L - 1;
    std::vector<cd> u(N, 0.0);
    for (size_t n = 0; n < N; ++n) {
        for (size_t k = 0; k <= n; ++k) {
            if (k < M && (n - k) < L) {
                u[n] += x[k] * y[n - k];
            }
        }
    }
    return u;
}

// Функция свертки через БПФ
size_t next_power_of_two(size_t n) {
    if (n <= 1) return 1;
    size_t p = 1;
    while (p < n) p <<= 1;
    return p;
}

std::vector<cd> convolve_fft(const std::vector<cd>& x, const std::vector<cd>& y) {
    size_t M = x.size();
    size_t L = y.size();
    size_t N_conv = M + L - 1;
    size_t N_fft = next_power_of_two(N_conv);

    std::vector<cd> x_pad(N_fft, 0.0);
    std::vector<cd> y_pad(N_fft, 0.0);
    for (size_t i = 0; i < M; ++i) x_pad[i] = x[i];
    for (size_t i = 0; i < L; ++i) y_pad[i] = y[i];

    auto X_hat = fft(x_pad);
    auto Y_hat = fft(y_pad);

    std::vector<cd> U_hat(N_fft);
    double scale = sqrt(static_cast<double>(N_fft));
    for (size_t i = 0; i < N_fft; ++i) {
        U_hat[i] = X_hat[i] * Y_hat[i] * scale;
    }

    auto U = ifft(U_hat);
    U.resize(N_conv);
    return U;
}

// Функция вычисления нормы разности
double max_norm(const std::vector<cd>& a, const std::vector<cd>& b) {
    double err = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double d = std::abs(a[i] - b[i]);
        if (d > err) err = d;
    }
    return err;
}

int main() {
    const size_t M = 1024;
    const size_t L = 1024;

    // Читаем сигналы
    auto x = read_signal("../data/signal_x.bin", M);
    auto y = read_signal("../data/signal_y.bin", L);

    // Вычисляем свертки
    auto u_direct = convolve_direct(x, y);
    auto u_fft = convolve_fft(x, y);

    // Читаем эталонный результат из Python
    auto u_numpy = read_signal("../data/convolution_numpy.bin", M + L - 1);

    // Вычисляем нормы разности
    double err_direct_fft = max_norm(u_direct, u_fft);
    double err_direct_numpy = max_norm(u_direct, u_numpy);

    // Выводим результаты
    std::cout << std::scientific << std::setprecision(3);
    std::cout << "||u_direct - u_fft||_max = " << err_direct_fft << "\n";
    std::cout << "||u_direct - u_numpy||_max = " << err_direct_numpy << "\n";

    return 0;
}
