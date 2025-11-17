// src/task_5.cpp
#include "../include/io_utils.h"
#include <iostream>
#include <vector>
#include <complex>

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

int main() {
    const size_t M = 1024;
    const size_t L = 1024;

    auto x = read_signal("../data/signal_x.bin", M);
    auto y = read_signal("../data/signal_y.bin", L);

    auto u = convolve_direct(x, y);

    write_signal(u, "convolution_direct.txt");

    std::cout << "Свёртка сохранена в convolution_direct.txt\n";
    return 0;
}
