/**
 * @file file_analisis.h
 * @brief Header untuk operasi file analisis keuangan
 * @author Kelompok B11
 * @date 2025
 */

#ifndef FILE_ANALISIS_H
#define FILE_ANALISIS_H

#include "../types.h"

/**
 * @brief Load analisis keuangan untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika berhasil, 0 jika gagal
 */
int load_analisis_bulan(int bulan, AnalisisKeuangan *result);

/**
 * @brief Simpan analisis keuangan untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @param analisis Data analisis
 * @return 1 jika berhasil, 0 jika gagal
 */
int save_analisis_bulan(int bulan, AnalisisKeuangan *analisis);

/**
 * @brief Cek apakah file analisis untuk bulan tertentu ada
 * @param bulan Bulan (1-12)
 * @return 1 jika ada, 0 jika tidak
 */
int analisis_file_exists(int bulan);

/**
 * @brief Inisialisasi analisis default untuk bulan baru
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int init_analisis_bulan(int bulan);

#endif /* FILE_ANALISIS_H */
