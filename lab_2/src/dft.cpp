// src/dft.cpp
#include "../include/dft.h"
#include <cmath>

std::vector<cd> dft_direct(const std::vector<cd>& x) {
    size_t N = x.size();
    std::vector<cd> y(N);
    const double PI = acos(-1.0);
    for (size_t k = 0; k < N; ++k) {
        cd sum(0.0, 0.0);
        for (size_t j = 0; j < N; ++j) {
            double angle = -2.0 * PI * static_cast<double>(k * j) / static_cast<double>(N);
            sum += x[j] * cd(cos(angle), sin(angle));
        }
        y[k] = sum / sqrt(static_cast<double>(N));
    }
    return y;
}

std::vector<cd> idft_direct(const std::vector<cd>& y) {
    size_t N = y.size();
    std::vector<cd> x(N);
    const double PI = acos(-1.0);
    for (size_t j = 0; j < N; ++j) {
        cd sum(0.0, 0.0);
        for (size_t k = 0; k < N; ++k) {
            double angle = +2.0 * PI * static_cast<double>(k * j) / static_cast<double>(N);
            sum += y[k] * cd(cos(angle), sin(angle));
        }
        x[j] = sum / sqrt(static_cast<double>(N));
    }
    return x;
}
