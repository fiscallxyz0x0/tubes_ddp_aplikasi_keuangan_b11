/**
 * @file utils_date.h
 * @brief Header untuk fungsi utilitas parsing dan manipulasi tanggal
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk parsing, validasi, dan manipulasi
 * tanggal dalam format dd-mm-YYYY.
 */

#ifndef UTILS_DATE_H
#define UTILS_DATE_H

#include "../types.h"

/**
 * @brief Parse string tanggal ke komponen hari, bulan, tahun
 * @param str String tanggal format dd-mm-YYYY
 * @param d Pointer untuk menyimpan hari
 * @param m Pointer untuk menyimpan bulan
 * @param y Pointer untuk menyimpan tahun
 * @return 1 jika berhasil parse, 0 jika format invalid
 */
int parse_tanggal(const char *str, int *d, int *m, int *y);

/**
 * @brief Parse string tanggal ke struct Tanggal
 * @param str String tanggal format dd-mm-YYYY
 * @param tgl Pointer ke struct Tanggal untuk menyimpan hasil
 * @return 1 jika berhasil parse, 0 jika format invalid
 */
int parse_tanggal_struct(const char *str, Tanggal *tgl);

/**
 * @brief Format komponen tanggal ke string dd-mm-YYYY
 * @param d Hari (1-31)
 * @param m Bulan (1-12)
 * @param y Tahun (misal 2025)
 * @param result Buffer untuk menyimpan hasil (minimal 11 karakter)
 */
void format_tanggal(int d, int m, int y, char *result);

/**
 * @brief Mendapatkan bulan saat ini dari sistem
 * @return Bulan saat ini (1-12)
 */
int get_current_month(void);

/**
 * @brief Mendapatkan tahun saat ini dari sistem
 * @return Tahun saat ini
 */
int get_current_year(void);

/**
 * @brief Mendapatkan hari saat ini dari sistem
 * @return Hari saat ini (1-31)
 */
int get_current_day(void);

/**
 * @brief Memeriksa apakah tahun adalah tahun kabisat
 * @param year Tahun yang akan diperiksa
 * @return 1 jika tahun kabisat, 0 jika bukan
 */
int is_leap_year(int year);

/**
 * @brief Mendapatkan jumlah hari dalam bulan tertentu
 * @param month Bulan (1-12)
 * @param year Tahun (untuk pengecekan kabisat)
 * @return Jumlah hari dalam bulan
 */
int get_days_in_month(int month, int year);

/**
 * @brief Mengekstrak bulan dari string tanggal
 * @param tanggal String tanggal format dd-mm-YYYY
 * @return Nomor bulan (1-12), atau 0 jika gagal
 */
int ekstrak_bulan(const char *tanggal);

/**
 * @brief Mengekstrak tahun dari string tanggal
 * @param tanggal String tanggal format dd-mm-YYYY
 * @return Tahun, atau 0 jika gagal
 */
int ekstrak_tahun(const char *tanggal);

/**
 * @brief Mendapatkan tanggal hari ini dalam format dd-mm-YYYY
 * @param result Buffer untuk menyimpan hasil (minimal 11 karakter)
 */
void get_today_string(char *result);

#endif /* UTILS_DATE_H */
