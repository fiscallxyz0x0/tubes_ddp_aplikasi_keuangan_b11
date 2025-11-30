/**
 * @file transaksi_display.h
 * @brief Header untuk fungsi display transaksi di TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TRANSAKSI_DISPLAY_H
#define TRANSAKSI_DISPLAY_H

#include "../types.h"

/**
 * @brief Tampilkan daftar transaksi bulan
 * @param bulan Bulan yang ditampilkan
 * @param selected Index transaksi terpilih (-1 jika tidak ada)
 * @return Baris berikutnya setelah tabel
 */
int tampilkan_daftar_transaksi(int bulan, int selected);

/**
 * @brief Tampilkan detail satu transaksi
 * @param trx Pointer ke transaksi
 * @param start_y Baris awal
 * @return Baris berikutnya setelah detail
 */
int tampilkan_detail_transaksi(Transaksi *trx, int start_y);

/**
 * @brief Tampilkan ringkasan transaksi bulan
 * @param bulan Bulan yang ditampilkan
 * @param start_y Baris awal
 * @return Baris berikutnya setelah ringkasan
 */
int tampilkan_ringkasan_transaksi(int bulan, int start_y);

/**
 * @brief Tampilkan form tambah transaksi
 * @param bulan Bulan default untuk transaksi
 * @return 1 jika berhasil tambah, 0 jika dibatalkan
 */
int tampilkan_form_tambah_transaksi(int bulan);

/**
 * @brief Tampilkan form edit transaksi
 * @param id ID transaksi yang diedit
 * @return 1 jika berhasil edit, 0 jika dibatalkan
 */
int tampilkan_form_edit_transaksi(const char *id);

/**
 * @brief Tampilkan konfirmasi hapus transaksi
 * @param id ID transaksi yang akan dihapus
 * @return 1 jika berhasil hapus, 0 jika dibatalkan
 */
int tampilkan_konfirmasi_hapus_transaksi(const char *id);

#endif /* TRANSAKSI_DISPLAY_H */
