/**
 * @file transaksi_crud.h
 * @brief Header untuk operasi CRUD transaksi dengan validasi
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TRANSAKSI_CRUD_H
#define TRANSAKSI_CRUD_H

#include "../types.h"

/**
 * @brief Tambah transaksi baru dengan validasi
 * @param tanggal Tanggal transaksi (dd-mm-YYYY)
 * @param jenis Jenis transaksi (0=Pengeluaran, 1=Pemasukan)
 * @param pos Nama pos anggaran
 * @param nominal Nilai transaksi
 * @param deskripsi Keterangan transaksi
 * @param error_msg Buffer untuk pesan error (bisa NULL)
 * @return 1 jika berhasil, 0 jika gagal
 */
int transaksi_tambah(const char *tanggal, int jenis, const char *pos,
                     unsigned long long nominal, const char *deskripsi,
                     char *error_msg);

/**
 * @brief Edit transaksi dengan validasi
 * @param id ID transaksi yang diedit
 * @param tanggal Tanggal baru (NULL jika tidak diubah)
 * @param jenis Jenis baru (-1 jika tidak diubah)
 * @param pos Pos baru (NULL jika tidak diubah)
 * @param nominal Nominal baru (0 jika tidak diubah)
 * @param deskripsi Deskripsi baru (NULL jika tidak diubah)
 * @param error_msg Buffer untuk pesan error
 * @return 1 jika berhasil, 0 jika gagal
 */
int transaksi_edit(const char *id, const char *tanggal, int jenis,
                   const char *pos, unsigned long long nominal,
                   const char *deskripsi, char *error_msg);

/**
 * @brief Hapus transaksi dengan validasi
 * @param id ID transaksi yang dihapus
 * @param error_msg Buffer untuk pesan error
 * @return 1 jika berhasil, 0 jika gagal
 */
int transaksi_hapus(const char *id, char *error_msg);

/**
 * @brief Ambil daftar transaksi untuk bulan tertentu
 * @param list Array untuk menyimpan hasil
 * @param max_count Kapasitas maksimal
 * @param bulan Bulan (1-12), 0 untuk semua bulan
 * @return Jumlah transaksi
 */
int transaksi_get_list(Transaksi *list, int max_count, int bulan);

/**
 * @brief Ambil transaksi berdasarkan ID
 * @param id ID transaksi
 * @param result Pointer untuk menyimpan hasil
 * @return 1 jika ditemukan, 0 jika tidak
 */
int transaksi_get_by_id(const char *id, Transaksi *result);

/**
 * @brief Hitung total pemasukan untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @return Total pemasukan
 */
unsigned long long transaksi_total_pemasukan(int bulan);

/**
 * @brief Hitung total pengeluaran untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @return Total pengeluaran
 */
unsigned long long transaksi_total_pengeluaran(int bulan);

/**
 * @brief Hitung jumlah transaksi untuk bulan tertentu
 * @param bulan Bulan (1-12)
 * @param jenis Jenis transaksi (-1 untuk semua)
 * @return Jumlah transaksi
 */
int transaksi_count(int bulan, int jenis);

#endif /* TRANSAKSI_CRUD_H */
