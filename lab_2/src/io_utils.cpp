// src/io_utils.cpp
#include "../include/io_utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>

std::vector<cd> read_signal(const std::string& filename, size_t N) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        exit(1);
    }
    std::vector<cd> x(N);
    for (size_t i = 0; i < N; ++i) {
        double re, im;
        file.read(reinterpret_cast<char*>(&re), sizeof(double));
        file.read(reinterpret_cast<char*>(&im), sizeof(double));
        if (!file) {
            std::cerr << "Ошибка чтения на элементе " << i << " в файле " << filename << std::endl;
            exit(1);
        }
        x[i] = cd(re, im);
    }
    file.close();
    return x;
}

void write_signal(const std::vector<cd>& v, const std::string& filename) {
    std::ofstream f(filename);
    if (!f) {
        std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
        exit(1);
    }
    f << std::fixed << std::setprecision(12);
    for (const auto& c : v) {
        f << real(c) << " " << imag(c) << "\n";
    }
    f.close();
}
