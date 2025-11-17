// task8.cpp
#include "../include/io_utils.h"
#include "../include/fft.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <random>
#include <chrono>
#include <cmath>

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

// Генерация случайного сигнала
std::vector<cd> generate_signal(size_t N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 1.0);

    std::vector<cd> x(N);
    for (size_t i = 0; i < N; ++i) {
        x[i] = cd(dis(gen), dis(gen));
    }
    return x;
}

int main() {
    std::ofstream out("../data/task_8/timing_conv_data.txt");
    out << "Case\tN\tTime_Direct_ms\tTime_FFT_ms\n";

    // Случай 1: M = 512 (фиксировано), L = 2^n, n = 6..12
    const size_t M_fixed = 512;
    std::cout << "Случай 1: M = 512, L = 2^n\n";
    for (int n = 6; n <= 12; ++n) {
        size_t L = 1 << n;

        auto x = generate_signal(M_fixed);
        auto y = generate_signal(L);

        // Время прямой свертки
        auto start = std::chrono::high_resolution_clock::now();
        auto u_direct = convolve_direct(x, y);
        auto end = std::chrono::high_resolution_clock::now();
        double time_direct = std::chrono::duration<double, std::milli>(end - start).count();

        // Время свертки через БПФ
        start = std::chrono::high_resolution_clock::now();
        auto u_fft = convolve_fft(x, y);
        end = std::chrono::high_resolution_clock::now();
        double time_fft = std::chrono::duration<double, std::milli>(end - start).count();

        out << "Fixed_M" << "\t" << L << "\t" << time_direct << "\t" << time_fft << "\n";
        std::cout << "L=" << L << ": Direct=" << time_direct << "ms, FFT=" << time_fft << "ms\n";
    }

    // Случай 2: M = L = 2^n, n = 6..12
    std::cout << "\nСлучай 2: M = L = 2^n\n";
    for (int n = 6; n <= 12; ++n) {
        size_t N = 1 << n;

        auto x = generate_signal(N);
        auto y = generate_signal(N);

        // Время прямой свертки
        auto start = std::chrono::high_resolution_clock::now();
        auto u_direct = convolve_direct(x, y);
        auto end = std::chrono::high_resolution_clock::now();
        double time_direct = std::chrono::duration<double, std::milli>(end - start).count();

        // Время свертки через БПФ
        start = std::chrono::high_resolution_clock::now();
        auto u_fft = convolve_fft(x, y);
        end = std::chrono::high_resolution_clock::now();
        double time_fft = std::chrono::duration<double, std::milli>(end - start).count();

        out << "Equal_ML" << "\t" << N << "\t" << time_direct << "\t" << time_fft << "\n";
        std::cout << "N=" << N << ": Direct=" << time_direct << "ms, FFT=" << time_fft << "ms\n";
    }

    out.close();
    std::cout << "Результаты сохранены в timing_conv_data.txt\n";
    return 0;
}
