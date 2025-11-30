/**
 * @file file_pos.h
 * @brief Header untuk operasi file pos anggaran
 * @author Kelompok B11
 * @date 2025
 */

#ifndef FILE_POS_H
#define FILE_POS_H

#include "../types.h"

/**
 * @brief Load pos anggaran untuk bulan tertentu
 * @param list Array untuk menyimpan pos
 * @param max_count Kapasitas maksimal array
 * @param bulan Bulan (1-12)
 * @return Jumlah pos yang berhasil di-load
 */
int load_pos_bulan(PosAnggaran *list, int max_count, int bulan);

/**
 * @brief Simpan pos anggaran untuk bulan tertentu
 * @param list Array pos anggaran
 * @param count Jumlah pos
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int save_pos_bulan(PosAnggaran *list, int count, int bulan);

/**
 * @brief Tambah pos anggaran baru untuk bulan tertentu
 * @param pos Pointer ke pos baru
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int add_pos(PosAnggaran *pos, int bulan);

/**
 * @brief Update pos anggaran berdasarkan nomor
 * @param no Nomor pos yang akan diupdate
 * @param pos Data pos baru
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika tidak ditemukan
 */
int update_pos(int no, PosAnggaran *pos, int bulan);

/**
 * @brief Hapus pos anggaran berdasarkan nomor
 * @param no Nomor pos yang akan dihapus
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika tidak ditemukan
 */
int delete_pos(int no, int bulan);

/**
 * @brief Cari pos anggaran berdasarkan nama
 * @param nama Nama pos yang dicari
 * @param bulan Bulan (1-12)
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika ditemukan, 0 jika tidak
 */
int find_pos_by_nama(const char *nama, int bulan, PosAnggaran *result);

/**
 * @brief Cari pos anggaran berdasarkan nomor
 * @param no Nomor pos yang dicari
 * @param bulan Bulan (1-12)
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika ditemukan, 0 jika tidak
 */
int find_pos_by_no(int no, int bulan, PosAnggaran *result);

/**
 * @brief Cek apakah file pos untuk bulan tertentu ada
 * @param bulan Bulan (1-12)
 * @return 1 jika ada, 0 jika tidak
 */
int pos_file_exists(int bulan);

/**
 * @brief Inisialisasi pos default untuk bulan baru
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int init_pos_bulan(int bulan);

/**
 * @brief Copy pos dari bulan sebelumnya
 * @param bulan_tujuan Bulan tujuan (1-12)
 * @param bulan_sumber Bulan sumber (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int copy_pos_from_bulan(int bulan_tujuan, int bulan_sumber);

#endif /* FILE_POS_H */
