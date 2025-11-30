/**
 * @file pos_menu.h
 * @brief Header untuk menu pos anggaran
 * @author Kelompok B11
 * @date 2025
 */

#ifndef POS_MENU_H
#define POS_MENU_H

/**
 * @brief Tampilkan dan jalankan menu utama pos anggaran
 * @param bulan Bulan yang aktif
 * @return Kode aksi yang dipilih
 */
int menu_pos_utama(int bulan);

/**
 * @brief Tampilkan menu pilih bulan
 * @param bulan_saat_ini Bulan saat ini
 * @return Bulan yang dipilih, atau 0 jika dibatalkan
 */
int menu_pilih_bulan(int bulan_saat_ini);

/**
 * @brief Handler untuk view daftar pos dengan navigasi
 * @param bulan Bulan yang ditampilkan
 */
void handler_view_pos(int bulan);

/**
 * @brief Handler untuk tambah pos baru
 * @param bulan Bulan untuk pos baru
 */
void handler_tambah_pos(int bulan);

/**
 * @brief Handler untuk edit pos
 * @param bulan Bulan pos
 */
void handler_edit_pos(int bulan);

/**
 * @brief Handler untuk hapus pos
 * @param bulan Bulan pos
 */
void handler_hapus_pos(int bulan);

#endif /* POS_MENU_H */
