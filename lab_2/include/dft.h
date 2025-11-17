// include/dft.h
#ifndef DFT_H
#define DFT_H

#include <vector>
#include <complex>

using cd = std::complex<double>;

std::vector<cd> dft_direct(const std::vector<cd>& x);
std::vector<cd> idft_direct(const std::vector<cd>& y);

#endif
