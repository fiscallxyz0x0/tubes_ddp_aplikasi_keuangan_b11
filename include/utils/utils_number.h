/**
 * @file utils_number.h
 * @brief Header untuk fungsi utilitas format angka dan nominal
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk memformat angka ke format
 * Rupiah, persentase, dan rata-rata.
 */

#ifndef UTILS_NUMBER_H
#define UTILS_NUMBER_H

/**
 * @brief Memformat nominal ke format Rupiah dengan separator ribuan
 * @param nominal Nilai nominal yang akan diformat
 * @param result Buffer untuk menyimpan hasil (minimal 30 karakter)
 * 
 * Contoh: 1000000 -> "Rp 1.000.000"
 */
void format_rupiah(unsigned long long nominal, char *result);

/**
 * @brief Memformat persentase dengan 2 desimal
 * @param persen Nilai persentase
 * @param result Buffer untuk menyimpan hasil (minimal 15 karakter)
 * 
 * Contoh: 62.14159 -> "62.14%"
 */
void format_persentase(double persen, char *result);

/**
 * @brief Memformat nilai rata-rata dengan 2 desimal
 * @param rata Nilai rata-rata
 * @param result Buffer untuk menyimpan hasil (minimal 20 karakter)
 * 
 * Contoh: 29444.33 -> "29.444,33"
 */
void format_rata_rata(double rata, char *result);

/**
 * @brief Memformat angka dengan separator ribuan (tanpa prefix Rp)
 * @param nominal Nilai yang akan diformat
 * @param result Buffer untuk menyimpan hasil (minimal 25 karakter)
 * 
 * Contoh: 1000000 -> "1.000.000"
 */
void format_number_separator(unsigned long long nominal, char *result);

/**
 * @brief Memformat nilai saldo (bisa negatif) ke format Rupiah
 * @param saldo Nilai saldo (bisa negatif)
 * @param result Buffer untuk menyimpan hasil (minimal 30 karakter)
 * 
 * Contoh: -100000 -> "-Rp 100.000"
 */
void format_saldo(long long saldo, char *result);

/**
 * @brief Mengkonversi string angka ke unsigned long long
 * @param str String yang berisi angka
 * @param result Pointer untuk menyimpan hasil konversi
 * @return 1 jika berhasil, 0 jika gagal
 */
int str_to_ull(const char *str, unsigned long long *result);

/**
 * @brief Memeriksa apakah string hanya berisi digit
 * @param str String yang akan diperiksa
 * @return 1 jika hanya digit, 0 jika tidak
 */
int is_numeric_string(const char *str);

#endif /* UTILS_NUMBER_H */
