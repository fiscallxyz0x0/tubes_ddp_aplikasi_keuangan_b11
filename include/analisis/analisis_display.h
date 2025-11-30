/**
 * @file analisis_display.h
 * @brief Header untuk fungsi display analisis keuangan di TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef ANALISIS_DISPLAY_H
#define ANALISIS_DISPLAY_H

#include "../types.h"

/**
 * @brief Tampilkan analisis keuangan lengkap untuk bulan
 * @param bulan Bulan (1-12)
 */
void tampilkan_analisis_bulan(int bulan);

/**
 * @brief Tampilkan ringkasan kondisi keuangan
 * @param analisis Pointer ke data analisis
 * @param start_y Baris awal
 * @return Baris berikutnya
 */
int tampilkan_ringkasan_kondisi(AnalisisKeuangan *analisis, int start_y);

/**
 * @brief Tampilkan grafik sederhana perbandingan pemasukan/pengeluaran
 * @param analisis Pointer ke data analisis
 * @param start_y Baris awal
 * @return Baris berikutnya
 */
int tampilkan_grafik_sederhana(AnalisisKeuangan *analisis, int start_y);

/**
 * @brief Tampilkan saran berdasarkan kesimpulan
 * @param kesimpulan Kode kesimpulan
 * @param start_y Baris awal
 * @return Baris berikutnya
 */
int tampilkan_saran(int kesimpulan, int start_y);

#endif /* ANALISIS_DISPLAY_H */
