// include/io_utils.h
#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <vector>
#include <complex>
#include <string>

using cd = std::complex<double>;

// Чтение комплексного вектора из бинарного файла
std::vector<cd> read_signal(const std::string& filename, size_t N);

// Запись комплексного вектора в текстовый файл
void write_signal(const std::vector<cd>& v, const std::string& filename);

#endif // IO_UTILS_H
