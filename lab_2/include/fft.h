// include/fft.h
#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

using cd = std::complex<double>;

std::vector<cd> fft(const std::vector<cd>& x);
std::vector<cd> ifft(const std::vector<cd>& y);

#endif
