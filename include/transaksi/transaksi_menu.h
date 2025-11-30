/**
 * @file transaksi_menu.h
 * @brief Header untuk menu transaksi
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TRANSAKSI_MENU_H
#define TRANSAKSI_MENU_H

/**
 * @brief Tampilkan menu utama transaksi
 * @param bulan Bulan yang aktif
 * @return Kode aksi yang dipilih
 */
int menu_transaksi_utama(int bulan);

/**
 * @brief Handler untuk view daftar transaksi
 * @param bulan Bulan yang ditampilkan
 */
void handler_view_transaksi(int bulan);

/**
 * @brief Handler untuk tambah transaksi
 * @param bulan Bulan untuk transaksi baru
 */
void handler_tambah_transaksi(int bulan);

/**
 * @brief Handler untuk edit transaksi
 * @param bulan Bulan transaksi
 */
void handler_edit_transaksi(int bulan);

/**
 * @brief Handler untuk hapus transaksi
 * @param bulan Bulan transaksi
 */
void handler_hapus_transaksi(int bulan);

#endif /* TRANSAKSI_MENU_H */
