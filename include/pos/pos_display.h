/**
 * @file pos_display.h
 * @brief Header untuk fungsi display pos anggaran di TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef POS_DISPLAY_H
#define POS_DISPLAY_H

#include "../types.h"

/**
 * @brief Tampilkan daftar pos anggaran dengan kalkulasi
 * @param bulan Bulan yang ditampilkan
 * @param selected Index pos terpilih (-1 jika tidak ada)
 * @return Baris berikutnya setelah tabel
 */
int tampilkan_daftar_pos(int bulan, int selected);

/**
 * @brief Tampilkan detail satu pos anggaran
 * @param pos Pointer ke pos yang ditampilkan
 * @param start_y Baris awal tampilan
 * @return Baris berikutnya setelah detail
 */
int tampilkan_detail_pos(PosAnggaran *pos, int start_y);

/**
 * @brief Tampilkan ringkasan pos anggaran bulan
 * @param bulan Bulan yang ditampilkan
 * @param start_y Baris awal tampilan
 * @return Baris berikutnya setelah ringkasan
 */
int tampilkan_ringkasan_pos(int bulan, int start_y);

/**
 * @brief Tampilkan form tambah pos
 * @param bulan Bulan untuk pos baru
 * @return 1 jika berhasil tambah, 0 jika dibatalkan
 */
int tampilkan_form_tambah_pos(int bulan);

/**
 * @brief Tampilkan form edit pos
 * @param no Nomor pos yang diedit
 * @param bulan Bulan pos
 * @return 1 jika berhasil edit, 0 jika dibatalkan
 */
int tampilkan_form_edit_pos(int no, int bulan);

/**
 * @brief Tampilkan konfirmasi hapus pos
 * @param no Nomor pos yang akan dihapus
 * @param bulan Bulan pos
 * @return 1 jika berhasil hapus, 0 jika dibatalkan
 */
int tampilkan_konfirmasi_hapus_pos(int no, int bulan);

/**
 * @brief Tampilkan pilihan pos untuk input transaksi
 * @param bulan Bulan pos
 * @param result Buffer untuk menyimpan nama pos terpilih
 * @return 1 jika dipilih, 0 jika dibatalkan
 */
int tampilkan_pilih_pos(int bulan, char *result);

#endif /* POS_DISPLAY_H */
