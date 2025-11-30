/**
 * @file file_core.h
 * @brief Header untuk fungsi operasi file dasar
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi dasar untuk operasi file seperti
 * cek keberadaan file, buat file, buka file, dan generate nama file.
 */

#ifndef FILE_CORE_H
#define FILE_CORE_H

#include <stdio.h>

/**
 * @brief Cek apakah file ada
 * @param filename Path file yang akan dicek
 * @return 1 jika file ada, 0 jika tidak ada
 */
int file_exists(const char *filename);

/**
 * @brief Buat file baru (kosong)
 * @param filename Path file yang akan dibuat
 * @return 1 jika berhasil, 0 jika gagal
 */
int file_create(const char *filename);

/**
 * @brief Buka file untuk dibaca
 * @param filename Path file yang akan dibuka
 * @return FILE pointer jika berhasil, NULL jika gagal
 * 
 * Caller bertanggung jawab menutup file dengan fclose()
 */
FILE* file_open_read(const char *filename);

/**
 * @brief Buka file untuk ditulis (overwrite)
 * @param filename Path file yang akan dibuka
 * @return FILE pointer jika berhasil, NULL jika gagal
 * 
 * Caller bertanggung jawab menutup file dengan fclose()
 */
FILE* file_open_write(const char *filename);

/**
 * @brief Buka file untuk append (tambah di akhir)
 * @param filename Path file yang akan dibuka
 * @return FILE pointer jika berhasil, NULL jika gagal
 * 
 * Caller bertanggung jawab menutup file dengan fclose()
 */
FILE* file_open_append(const char *filename);

/**
 * @brief Generate nama file dengan suffix bulan
 * @param base Nama dasar file (misal "pos_anggaran")
 * @param bulan Nomor bulan (1-12)
 * @param result Buffer untuk menyimpan hasil
 * @param result_size Ukuran buffer result
 * 
 * Contoh: get_filename_bulan("pos", 11, result, sizeof(result)) 
 *         -> result = "data/pos_11.txt"
 */
void get_filename_bulan(const char *base, int bulan, char *result, int result_size);

/**
 * @brief Generate nama file transaksi (tanpa suffix bulan)
 * @param result Buffer untuk menyimpan hasil
 * @param result_size Ukuran buffer result
 * 
 * Transaksi disimpan dalam satu file untuk semua bulan
 */
void get_filename_transaksi(char *result, int result_size);

/**
 * @brief Memastikan direktori data ada
 * @return 1 jika berhasil (direktori ada/dibuat), 0 jika gagal
 */
int ensure_data_directory(void);

/**
 * @brief Membaca seluruh isi file ke buffer
 * @param filename Path file yang akan dibaca
 * @param buffer Buffer untuk menyimpan isi file
 * @param buffer_size Ukuran buffer
 * @return Jumlah karakter yang dibaca, 0 jika gagal atau file kosong
 */
int file_read_all(const char *filename, char *buffer, int buffer_size);

/**
 * @brief Menulis string ke file (overwrite)
 * @param filename Path file tujuan
 * @param content String yang akan ditulis
 * @return 1 jika berhasil, 0 jika gagal
 */
int file_write_all(const char *filename, const char *content);

/**
 * @brief Menambahkan baris ke akhir file
 * @param filename Path file tujuan
 * @param line Baris yang akan ditambahkan
 * @return 1 jika berhasil, 0 jika gagal
 */
int file_append_line(const char *filename, const char *line);

#endif /* FILE_CORE_H */
