/**
 * @file validator_string.h
 * @brief Header untuk fungsi validasi string
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk validasi panjang string,
 * string kosong, dan format string lainnya.
 */

#ifndef VALIDATOR_STRING_H
#define VALIDATOR_STRING_H

/**
 * @brief Validasi panjang nama pos anggaran
 * @param nama String nama pos yang akan divalidasi
 * @return 1 jika valid (<= 20 karakter), 0 jika tidak valid
 */
int validasi_panjang_pos(const char *nama);

/**
 * @brief Validasi panjang deskripsi transaksi
 * @param deskripsi String deskripsi yang akan divalidasi
 * @return 1 jika valid (<= 50 karakter), 0 jika tidak valid
 */
int validasi_panjang_deskripsi(const char *deskripsi);

/**
 * @brief Validasi string tidak kosong
 * @param str String yang akan divalidasi
 * @return 1 jika tidak kosong, 0 jika kosong atau NULL
 */
int validasi_tidak_kosong(const char *str);

/**
 * @brief Validasi panjang ID transaksi
 * @param id String ID yang akan divalidasi
 * @return 1 jika valid (format T0000), 0 jika tidak valid
 */
int validasi_format_id(const char *id);

/**
 * @brief Validasi string tidak mengandung karakter pipe (|)
 * @param str String yang akan divalidasi
 * @return 1 jika tidak mengandung pipe, 0 jika mengandung
 * 
 * Karakter pipe digunakan sebagai delimiter file, tidak boleh ada di data
 */
int validasi_tidak_ada_pipe(const char *str);

/**
 * @brief Validasi string hanya mengandung karakter yang diizinkan
 * @param str String yang akan divalidasi
 * @return 1 jika valid, 0 jika mengandung karakter tidak valid
 * 
 * Karakter yang diizinkan: alfanumerik, spasi, dan beberapa simbol umum
 */
int validasi_karakter_valid(const char *str);

#endif /* VALIDATOR_STRING_H */
