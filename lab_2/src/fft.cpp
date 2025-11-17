// src/fft.cpp
#include "../include/fft.h"
#include <cmath>
#include <algorithm>

size_t bit_reverse(size_t x, size_t logN) {
    size_t rev = 0;
    for (size_t i = 0; i < logN; ++i)
        if (x & (1ULL << i)) rev |= (1ULL << (logN - 1 - i));
    return rev;
}

void bit_reverse_permutation(std::vector<cd>& x) {
    size_t N = x.size();
    if (N <= 1) return;
    size_t logN = 0;
    for (size_t t = N; t > 1; t >>= 1) ++logN;
    for (size_t i = 0; i < N; ++i) {
        size_t j = bit_reverse(i, logN);
        if (i < j) std::swap(x[i], x[j]);
    }
}

void fft_dif_core(std::vector<cd>& x, bool inverse) {
    size_t N = x.size();
    if (N <= 1) return;
    const double PI = acos(-1.0);
    size_t logN = 0;
    for (size_t t = N; t > 1; t >>= 1) ++logN;

    for (size_t s = logN; s >= 1; --s) {
        size_t m = 1 << s;
        size_t m2 = m >> 1;
        double angle_step = (inverse ? +2.0 : -2.0) * PI / static_cast<double>(m);

        for (size_t j = 0; j < m2; ++j) {
            cd w(cos(j * angle_step), sin(j * angle_step));
            for (size_t k = j; k < N; k += m) {
                cd u = x[k];
                cd v = x[k + m2];
                x[k] = u + v;
                x[k + m2] = (u - v) * w;
            }
        }
    }
}

std::vector<cd> fft(const std::vector<cd>& x_input) {
    auto x = x_input;
    fft_dif_core(x, false);
    bit_reverse_permutation(x);
    double scale = 1.0 / sqrt(static_cast<double>(x.size()));
    for (auto& v : x) v *= scale;
    return x;
}

std::vector<cd> ifft(const std::vector<cd>& y_input) {
    auto y = y_input;
    fft_dif_core(y, true);
    bit_reverse_permutation(y);
    double scale = 1.0 / sqrt(static_cast<double>(y.size()));
    for (auto& v : y) v *= scale;
    return y;
}
