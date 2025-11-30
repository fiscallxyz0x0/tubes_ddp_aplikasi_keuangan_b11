/**
 * @file validator_number.h
 * @brief Header untuk fungsi validasi angka
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk validasi nominal positif,
 * nomor pos, dan parsing angka.
 */

#ifndef VALIDATOR_NUMBER_H
#define VALIDATOR_NUMBER_H

/**
 * @brief Validasi nominal harus positif (> 0)
 * @param nominal Nilai yang akan divalidasi
 * @return 1 jika valid (> 0), 0 jika tidak valid
 */
int validasi_nominal_positif(unsigned long long nominal);

/**
 * @brief Validasi nomor pos dalam range yang valid
 * @param no Nomor pos yang akan divalidasi
 * @param max Nilai maksimal yang diizinkan
 * @return 1 jika valid (1 <= no <= max), 0 jika tidak valid
 */
int validasi_no_pos(int no, int max);

/**
 * @brief Parse string ke unsigned long long dengan validasi
 * @param str String yang berisi angka
 * @param result Pointer untuk menyimpan hasil parsing
 * @return 1 jika berhasil, 0 jika gagal atau format invalid
 */
int parse_nominal(const char *str, unsigned long long *result);

/**
 * @brief Validasi pilihan menu dalam range
 * @param pilihan Pilihan yang akan divalidasi
 * @param min Nilai minimum yang diizinkan
 * @param max Nilai maksimum yang diizinkan
 * @return 1 jika valid, 0 jika tidak valid
 */
int validasi_pilihan_menu(int pilihan, int min, int max);

/**
 * @brief Validasi jenis transaksi (0 atau 1)
 * @param jenis Jenis transaksi
 * @return 1 jika valid (0=Pengeluaran atau 1=Pemasukan), 0 jika tidak
 */
int validasi_jenis_transaksi(int jenis);

#endif /* VALIDATOR_NUMBER_H */
