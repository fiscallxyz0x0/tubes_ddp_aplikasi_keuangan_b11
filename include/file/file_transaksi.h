/**
 * @file file_transaksi.h
 * @brief Header untuk operasi file transaksi
 * @author Kelompok B11
 * @date 2025
 */

#ifndef FILE_TRANSAKSI_H
#define FILE_TRANSAKSI_H

#include "../types.h"

/**
 * @brief Load semua transaksi dari file
 * @param list Array untuk menyimpan transaksi
 * @param max_count Kapasitas maksimal array
 * @return Jumlah transaksi yang berhasil di-load
 */
int load_transaksi(Transaksi *list, int max_count);

/**
 * @brief Load transaksi berdasarkan bulan
 * @param list Array untuk menyimpan transaksi
 * @param max_count Kapasitas maksimal array
 * @param bulan Bulan yang difilter (1-12)
 * @return Jumlah transaksi yang berhasil di-load
 */
int load_transaksi_bulan(Transaksi *list, int max_count, int bulan);

/**
 * @brief Simpan semua transaksi ke file
 * @param list Array transaksi
 * @param count Jumlah transaksi
 * @return 1 jika berhasil, 0 jika gagal
 */
int save_transaksi(Transaksi *list, int count);

/**
 * @brief Tambah transaksi baru
 * @param trx Pointer ke transaksi baru
 * @return 1 jika berhasil, 0 jika gagal
 */
int add_transaksi(Transaksi *trx);

/**
 * @brief Update transaksi berdasarkan ID
 * @param id ID transaksi yang akan diupdate
 * @param trx Data transaksi baru
 * @return 1 jika berhasil, 0 jika tidak ditemukan
 */
int update_transaksi(const char *id, Transaksi *trx);

/**
 * @brief Hapus transaksi berdasarkan ID
 * @param id ID transaksi yang akan dihapus
 * @return 1 jika berhasil, 0 jika tidak ditemukan
 */
int delete_transaksi(const char *id);

/**
 * @brief Cari transaksi berdasarkan ID
 * @param id ID transaksi yang dicari
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika ditemukan, 0 jika tidak
 */
int find_transaksi_by_id(const char *id, Transaksi *result);

/**
 * @brief Generate ID transaksi baru
 * @param buffer Buffer untuk menyimpan ID (minimal 6 karakter)
 */
void generate_transaksi_id(char *buffer);

/**
 * @brief Hitung jumlah transaksi untuk pos tertentu
 * @param nama_pos Nama pos yang dihitung
 * @return Jumlah transaksi
 */
int count_transaksi_by_pos(const char *nama_pos);

#endif /* FILE_TRANSAKSI_H */
