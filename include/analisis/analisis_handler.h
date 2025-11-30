/**
 * @file analisis_handler.h
 * @brief Header untuk handler utama modul analisis keuangan
 * @author Kelompok B11
 * @date 2025
 */

#ifndef ANALISIS_HANDLER_H
#define ANALISIS_HANDLER_H

/**
 * @brief Jalankan modul analisis keuangan
 * @param bulan_awal Bulan awal yang dianalisis
 */
void run_analisis_module(int bulan_awal);

/**
 * @brief Menu analisis keuangan
 * @param bulan Bulan yang aktif
 * @return Kode aksi yang dipilih
 */
int menu_analisis_utama(int bulan);

#endif /* ANALISIS_HANDLER_H */
