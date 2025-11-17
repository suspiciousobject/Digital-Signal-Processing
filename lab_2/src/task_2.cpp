// src/task2.cpp
#include "../include/fft.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <iomanip>

using cd = std::complex<double>;

std::vector<cd> read_signal(const std::string& filename, size_t N) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть " << filename << std::endl;
        exit(1);
    }
    std::vector<cd> x(N);
    for (size_t i = 0; i < N; ++i) {
        double re, im;
        file.read(reinterpret_cast<char*>(&re), sizeof(double));
        file.read(reinterpret_cast<char*>(&im), sizeof(double));
        if (!file) {
            std::cerr << "Ошибка чтения на элементе " << i << std::endl;
            exit(1);
        }
        x[i] = cd(re, im);
    }
    return x;
}

void write_vector(const std::vector<cd>& v, const std::string& filename) {
    std::ofstream f(filename);
    f << std::fixed << std::setprecision(12);
    for (const auto& c : v) {
        f << real(c) << " " << imag(c) << "\n";
    }
}

int main() {
    const size_t N = 1024;
    auto x = read_signal("../data/input_signal.bin", N);

    auto y = fft(x);
    auto x_rec = ifft(y);

    write_vector(y, "../data/task_2/fft_result.txt");
    write_vector(x_rec, "../data/task_2/ifft_result.txt");

    return 0;
}
