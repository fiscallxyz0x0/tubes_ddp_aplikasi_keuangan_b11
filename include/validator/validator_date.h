/**
 * @file validator_date.h
 * @brief Header untuk fungsi validasi tanggal
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk validasi format tanggal,
 * tanggal valid, dan ekstraksi bulan.
 */

#ifndef VALIDATOR_DATE_H
#define VALIDATOR_DATE_H

/**
 * @brief Validasi format tanggal dd-mm-YYYY
 * @param tanggal String tanggal yang akan divalidasi
 * @return 1 jika format valid, 0 jika tidak valid
 * 
 * Hanya mengecek format, bukan kevalidan tanggal
 */
int validasi_format_tanggal(const char *tanggal);

/**
 * @brief Validasi tanggal benar-benar valid (termasuk kabisat)
 * @param d Hari (1-31)
 * @param m Bulan (1-12)
 * @param y Tahun
 * @return 1 jika tanggal valid, 0 jika tidak valid
 */
int validasi_tanggal_valid(int d, int m, int y);

/**
 * @brief Validasi tanggal bukan 00-00-0000
 * @param tanggal String tanggal
 * @return 1 jika bukan tanggal nol, 0 jika tanggal nol atau invalid
 */
int validasi_bukan_nol(const char *tanggal);

/**
 * @brief Validasi tanggal lengkap (format dan kevalidan)
 * @param tanggal String tanggal format dd-mm-YYYY
 * @return 1 jika valid, 0 jika tidak valid
 * 
 * Kombinasi validasi format dan validasi tanggal valid
 */
int validasi_tanggal_lengkap(const char *tanggal);

/**
 * @brief Validasi bulan dalam range 1-12
 * @param bulan Nomor bulan
 * @return 1 jika valid, 0 jika tidak valid
 */
int validasi_bulan(int bulan);

/**
 * @brief Validasi tahun (harus > 0 dan reasonable)
 * @param tahun Tahun yang divalidasi
 * @return 1 jika valid (1900-2100), 0 jika tidak valid
 */
int validasi_tahun(int tahun);

/**
 * @brief REV-3: Validasi bulan pada tanggal sesuai dengan bulan aktif
 * @param tanggal String tanggal format dd-mm-YYYY
 * @param bulan_aktif Bulan yang sedang dipilih (1-12)
 * @return 1 jika bulan sesuai, 0 jika tidak sesuai
 */
int validasi_bulan_sesuai(const char *tanggal, int bulan_aktif);

#endif /* VALIDATOR_DATE_H */
