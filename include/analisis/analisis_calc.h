/**
 * @file analisis_calc.h
 * @brief Header untuk fungsi kalkulasi analisis keuangan
 * @author Kelompok B11
 * @date 2025
 */

#ifndef ANALISIS_CALC_H
#define ANALISIS_CALC_H

#include "../types.h"

/**
 * @brief Hitung analisis keuangan lengkap untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @param result Pointer untuk menyimpan hasil analisis
 * @return 1 jika berhasil, 0 jika gagal
 */
int hitung_analisis_bulan(int bulan, AnalisisKeuangan *result);

/**
 * @brief Tentukan kondisi keuangan berdasarkan saldo
 * @param pemasukan Total pemasukan
 * @param pengeluaran Total pengeluaran
 * @return KONDISI_DEFISIT, KONDISI_SEIMBANG, atau KONDISI_SURPLUS
 */
int tentukan_kondisi_keuangan(unsigned long long pemasukan, 
                               unsigned long long pengeluaran);

/**
 * @brief Tentukan kesimpulan berdasarkan persentase sisa
 * @param persentase_sisa Persentase sisa dari pemasukan
 * @return KESIMPULAN_HEMAT, KESIMPULAN_SEIMBANG, KESIMPULAN_BOROS, 
 *         atau KESIMPULAN_TIDAK_SEHAT
 */
int tentukan_kesimpulan(double persentase_sisa);

/**
 * @brief Dapatkan label kondisi keuangan
 * @param kondisi Kode kondisi
 * @return String label kondisi
 */
const char* get_label_kondisi(int kondisi);

/**
 * @brief Dapatkan label kesimpulan
 * @param kesimpulan Kode kesimpulan
 * @return String label kesimpulan
 */
const char* get_label_kesimpulan(int kesimpulan);

/**
 * @brief Dapatkan deskripsi kesimpulan yang lebih lengkap
 * @param kesimpulan Kode kesimpulan
 * @return String deskripsi kesimpulan
 */
const char* get_deskripsi_kesimpulan(int kesimpulan);

/**
 * @brief Refresh analisis untuk bulan (hitung ulang dan simpan)
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int refresh_analisis_bulan(int bulan);

#endif /* ANALISIS_CALC_H */
