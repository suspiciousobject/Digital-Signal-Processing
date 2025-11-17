// src/task3.cpp
#include "../include/dft.h"
#include "../include/fft.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>
#include <iomanip>

using cd = std::complex<double>;

std::vector<cd> read_vector(const std::string& filename, size_t N) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть " << filename << std::endl;
        exit(1);
    }
    std::vector<cd> v(N);
    for (size_t i = 0; i < N; ++i) {
        double re, im;
        file.read(reinterpret_cast<char*>(&re), sizeof(double));
        file.read(reinterpret_cast<char*>(&im), sizeof(double));
        if (!file) {
            std::cerr << "Ошибка чтения на элементе " << i << std::endl;
            exit(1);
        }
        v[i] = cd(re, im);
    }
    return v;
}

double max_norm(const std::vector<cd>& a, const std::vector<cd>& b) {
    double err = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double d = std::abs(a[i] - b[i]);
        if (d > err) err = d;
    }
    return err;
}

int main() {
    const size_t N = 1024;

    auto X = read_vector("../data/input_signal.bin", N);

    // ДПФ/ОДПФ
    auto Y_dft = dft_direct(X);
    auto X_dft_rec = idft_direct(Y_dft);

    // БПФ/ОБПФ
    auto Y_fft = fft(X);
    auto X_fft_rec = ifft(Y_fft);

    // Сравнение с numpy
    auto Y_numpy = read_vector("../data/dft_numpy.bin", N);

    // Вывод ошибок
    std::cout << std::scientific << std::setprecision(3);
    std::cout << "1. ||X - ОДПФ(ДПФ(X))||_max = " << max_norm(X, X_dft_rec) << "\n";
    std::cout << "2. ||X - ОБПФ(БПФ(X))||_max = " << max_norm(X, X_fft_rec) << "\n";
    std::cout << "3. ||ДПФ(X) - БПФ(X)||_max   = " << max_norm(Y_dft, Y_fft) << "\n";
    std::cout << "4. ||ДПФ(X) - numpy.fft||_max = " << max_norm(Y_dft, Y_numpy) << "\n";

    return 0;
}
