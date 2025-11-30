/**
 * @file validator_pos.h
 * @brief Header untuk fungsi validasi pos anggaran
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk validasi keberadaan pos,
 * keunikan nama pos, dan pengambilan data pos.
 */

#ifndef VALIDATOR_POS_H
#define VALIDATOR_POS_H

#include "../types.h"

/**
 * @brief Validasi nama pos unik (belum ada di daftar)
 * @param nama Nama pos yang akan divalidasi
 * @param list Array pos anggaran yang sudah ada
 * @param count Jumlah pos dalam array
 * @return 1 jika nama unik (belum ada), 0 jika sudah ada
 */
int validasi_pos_unik(const char *nama, PosAnggaran *list, int count);

/**
 * @brief Validasi pos dengan nomor tertentu ada dalam daftar
 * @param no Nomor pos yang dicari
 * @param list Array pos anggaran
 * @param count Jumlah pos dalam array
 * @return 1 jika pos ada, 0 jika tidak ada
 */
int validasi_pos_exists(int no, PosAnggaran *list, int count);

/**
 * @brief Mendapatkan nama pos berdasarkan nomor
 * @param no Nomor pos yang dicari
 * @param list Array pos anggaran
 * @param count Jumlah pos dalam array
 * @param result Buffer untuk menyimpan nama pos (minimal 21 karakter)
 * @return 1 jika berhasil, 0 jika tidak ditemukan
 */
int get_nama_pos_by_no(int no, PosAnggaran *list, int count, char *result);

/**
 * @brief Mendapatkan index pos berdasarkan nama
 * @param nama Nama pos yang dicari
 * @param list Array pos anggaran
 * @param count Jumlah pos dalam array
 * @return Index pos (0-based) jika ditemukan, -1 jika tidak ditemukan
 */
int get_index_pos_by_nama(const char *nama, PosAnggaran *list, int count);

/**
 * @brief Validasi nama pos untuk edit (unik kecuali nama yang sedang diedit)
 * @param nama Nama pos baru
 * @param no_edit Nomor pos yang sedang diedit
 * @param list Array pos anggaran
 * @param count Jumlah pos dalam array
 * @return 1 jika valid (unik atau sama dengan pos yang diedit), 0 jika duplikat
 */
int validasi_pos_unik_edit(const char *nama, int no_edit, PosAnggaran *list, int count);

/**
 * @brief Validasi pos bisa dihapus (tidak ada transaksi terkait)
 * @param no Nomor pos yang akan dihapus
 * @param pos_list Array pos anggaran
 * @param pos_count Jumlah pos
 * @return 1 jika bisa dihapus (jumlah_transaksi == 0), 0 jika tidak
 * 
 * Pos dengan transaksi tidak bisa dihapus untuk menjaga integritas data
 */
int validasi_pos_bisa_hapus(int no, PosAnggaran *pos_list, int pos_count);

#endif /* VALIDATOR_POS_H */
