/**
 * @file pos_crud.h
 * @brief Header untuk operasi CRUD pos anggaran
 * @author Kelompok B11
 * @date 2025
 * 
 * Wrapper yang mengintegrasikan file_pos dan pos_calc
 * untuk operasi pos anggaran yang lengkap.
 */

#ifndef POS_CRUD_H
#define POS_CRUD_H

#include "../types.h"
#include "../constants.h"

/**
 * @brief Tambah pos anggaran baru dengan validasi
 * @param nama Nama pos
 * @param nominal Anggaran pos
 * @param bulan Bulan (1-12)
 * @param error_msg Buffer untuk pesan error (bisa NULL)
 * @return 1 jika berhasil, 0 jika gagal
 */
int pos_tambah(const char *nama, unsigned long long nominal, int bulan, char *error_msg);

/**
 * @brief Edit pos anggaran dengan validasi
 * @param no Nomor pos yang diedit
 * @param nama_baru Nama baru (bisa NULL jika tidak diubah)
 * @param nominal_baru Anggaran baru (0 jika tidak diubah)
 * @param bulan Bulan (1-12)
 * @param error_msg Buffer untuk pesan error (bisa NULL)
 * @return 1 jika berhasil, 0 jika gagal
 */
int pos_edit(int no, const char *nama_baru, unsigned long long nominal_baru, int bulan, char *error_msg);

/**
 * @brief Hapus pos anggaran dengan validasi
 * @param no Nomor pos yang dihapus
 * @param bulan Bulan (1-12)
 * @param error_msg Buffer untuk pesan error (bisa NULL)
 * @return 1 jika berhasil, 0 jika gagal
 */
int pos_hapus(int no, int bulan, char *error_msg);

/**
 * @brief Ambil daftar pos untuk bulan dengan kalkulasi terbaru
 * @param list Array untuk menyimpan pos
 * @param max_count Kapasitas maksimal
 * @param bulan Bulan (1-12)
 * @return Jumlah pos
 */
int pos_get_list(PosAnggaran *list, int max_count, int bulan);

/**
 * @brief Ambil satu pos berdasarkan nomor dengan kalkulasi terbaru
 * @param no Nomor pos
 * @param bulan Bulan (1-12)
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika ditemukan, 0 jika tidak
 */
int pos_get_by_no(int no, int bulan, PosAnggaran *result);

/**
 * @brief Ambil daftar nama pos untuk dropdown/pilihan
 * @param names Array string untuk nama
 * @param max_count Kapasitas maksimal
 * @param bulan Bulan (1-12)
 * @return Jumlah pos
 */
int pos_get_names(char names[][MAX_POS_LENGTH + 1], int max_count, int bulan);

/**
 * @brief Cek apakah pos dengan nama tertentu sudah ada
 * @param nama Nama pos
 * @param bulan Bulan (1-12)
 * @return 1 jika ada, 0 jika tidak
 */
int pos_exists(const char *nama, int bulan);

/**
 * @brief Refresh kalkulasi semua pos untuk bulan
 * @param bulan Bulan (1-12)
 * @return 1 jika berhasil, 0 jika gagal
 */
int pos_refresh(int bulan);

#endif /* POS_CRUD_H */
