// src/task4.cpp
#include "../include/dft.h"
#include "../include/fft.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <random>
#include <chrono>

using cd = std::complex<double>;

// Генерация случайного комплексного сигнала длины N
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
    std::ofstream out("../data/timing_data.txt");
    out << "N\tTime_DFT_ms\tTime_FFT_ms\n";

    for (int n = 6; n <= 12; ++n) {
        size_t N = 1 << n;  // N = 2^n

        // Генерация случайного сигнала
        auto signal = generate_signal(N);

        // Измерение времени ДПФ
        auto start = std::chrono::high_resolution_clock::now();
        auto y_dft = dft_direct(signal);
        auto end = std::chrono::high_resolution_clock::now();
        double time_dft = std::chrono::duration<double, std::milli>(end - start).count();

        // Измерение времени БПФ
        start = std::chrono::high_resolution_clock::now();
        auto y_fft = fft(signal);
        end = std::chrono::high_resolution_clock::now();
        double time_fft = std::chrono::duration<double, std::milli>(end - start).count();

        // Запись в файл
        out << N << "\t" << time_dft << "\t" << time_fft << "\n";
        std::cout << "N = " << N << ": DFT = " << time_dft << " мс, FFT = " << time_fft << " мс\n";
    }

    out.close();
    
    return 0;
}
