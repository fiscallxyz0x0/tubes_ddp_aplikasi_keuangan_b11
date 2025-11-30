/**
 * @file pos_calc.h
 * @brief Header untuk fungsi kalkulasi pos anggaran
 * @author Kelompok B11
 * @date 2025
 * 
 * Mengimplementasikan Real-time Calculation untuk menghitung
 * realisasi, sisa, dan status pos anggaran berdasarkan transaksi.
 */

#ifndef POS_CALC_H
#define POS_CALC_H

#include "../types.h"

/**
 * @brief Hitung realisasi pos dari transaksi
 * @param nama_pos Nama pos yang dihitung
 * @param bulan Bulan transaksi (1-12)
 * @return Total realisasi (pengeluaran) untuk pos
 */
unsigned long long hitung_realisasi_pos(const char *nama_pos, int bulan);

/**
 * @brief Hitung sisa anggaran pos
 * @param nominal Anggaran awal
 * @param realisasi Realisasi pengeluaran
 * @return Sisa anggaran (bisa negatif)
 */
long long hitung_sisa_pos(unsigned long long nominal, unsigned long long realisasi);

/**
 * @brief Tentukan status pos berdasarkan sisa
 * @param sisa Sisa anggaran
 * @return STATUS_AMAN atau STATUS_TIDAK_AMAN
 */
int tentukan_status_pos(long long sisa);

/**
 * @brief Update kalkulasi untuk satu pos
 * @param pos Pointer ke pos yang akan diupdate
 * @param bulan Bulan untuk kalkulasi
 */
void update_kalkulasi_pos(PosAnggaran *pos, int bulan);

/**
 * @brief Update kalkulasi untuk semua pos dalam bulan
 * @param bulan Bulan untuk kalkulasi
 * @return 1 jika berhasil, 0 jika gagal
 */
int update_semua_pos_bulan(int bulan);

/**
 * @brief Hitung jumlah transaksi untuk pos dalam bulan
 * @param nama_pos Nama pos
 * @param bulan Bulan (1-12)
 * @return Jumlah transaksi
 */
int hitung_jumlah_transaksi_pos(const char *nama_pos, int bulan);

/**
 * @brief Hitung total anggaran semua pos dalam bulan
 * @param bulan Bulan (1-12)
 * @return Total anggaran
 */
unsigned long long hitung_total_anggaran(int bulan);

/**
 * @brief Hitung total realisasi semua pos dalam bulan
 * @param bulan Bulan (1-12)
 * @return Total realisasi
 */
unsigned long long hitung_total_realisasi(int bulan);

#endif /* POS_CALC_H */
