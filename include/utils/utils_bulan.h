/**
 * @file utils_bulan.h
 * @brief Header untuk fungsi utilitas konversi nama bulan
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk konversi antara nomor bulan
 * dan nama bulan dalam Bahasa Indonesia.
 */

#ifndef UTILS_BULAN_H
#define UTILS_BULAN_H

/**
 * @brief Mendapatkan nama bulan dalam Bahasa Indonesia
 * @param bulan Nomor bulan (1-12)
 * @return Pointer ke string nama bulan (statis), atau "Invalid" jika di luar range
 * 
 * Contoh: get_nama_bulan(1) -> "Januari"
 */
const char* get_nama_bulan(int bulan);

/**
 * @brief Mendapatkan kode bulan 2 digit
 * @param bulan Nomor bulan (1-12)
 * @return Pointer ke string kode bulan (statis), atau "00" jika di luar range
 * 
 * Contoh: get_kode_bulan(1) -> "01", get_kode_bulan(12) -> "12"
 */
const char* get_kode_bulan(int bulan);

/**
 * @brief Mendapatkan nama bulan singkat (3 huruf)
 * @param bulan Nomor bulan (1-12)
 * @return Pointer ke string nama bulan singkat (statis)
 * 
 * Contoh: get_nama_bulan_singkat(1) -> "Jan"
 */
const char* get_nama_bulan_singkat(int bulan);

/**
 * @brief Mengkonversi nama bulan ke nomor bulan
 * @param nama Nama bulan (case-insensitive)
 * @return Nomor bulan (1-12), atau 0 jika tidak valid
 * 
 * Contoh: nama_ke_nomor_bulan("januari") -> 1
 */
int nama_ke_nomor_bulan(const char *nama);

/**
 * @brief Validasi nomor bulan
 * @param bulan Nomor bulan yang akan divalidasi
 * @return 1 jika valid (1-12), 0 jika tidak valid
 */
int is_valid_bulan(int bulan);

#endif /* UTILS_BULAN_H */
