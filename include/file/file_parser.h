/**
 * @file file_parser.h
 * @brief Header untuk fungsi parsing format pipe-delimited
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk parsing baris file ke struct
 * dan memformat struct ke string pipe-delimited.
 */

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "../types.h"

/**
 * @brief Parse baris teks ke struct Transaksi
 * @param line Baris teks format: id|tanggal|jenis|pos|nominal|deskripsi
 * @param trx Pointer ke struct Transaksi untuk menyimpan hasil
 * @return 1 jika berhasil, 0 jika format invalid
 */
int parse_line_transaksi(const char *line, Transaksi *trx);

/**
 * @brief Parse baris teks ke struct PosAnggaran
 * @param line Baris teks format: no|nama|nominal|realisasi|sisa|jumlah_trx|status
 * @param pos Pointer ke struct PosAnggaran untuk menyimpan hasil
 * @return 1 jika berhasil, 0 jika format invalid
 */
int parse_line_pos(const char *line, PosAnggaran *pos);

/**
 * @brief Parse baris teks ke struct AnalisisKeuangan
 * @param line Baris teks format: pemasukan|pengeluaran|rata|persen|saldo|kondisi|kesimpulan|trx_out|trx_in
 * @param data Pointer ke struct AnalisisKeuangan untuk menyimpan hasil
 * @return 1 jika berhasil, 0 jika format invalid
 */
int parse_line_analisis(const char *line, AnalisisKeuangan *data);

/**
 * @brief Format struct Transaksi ke string pipe-delimited
 * @param trx Pointer ke struct Transaksi sumber
 * @param result Buffer untuk menyimpan hasil
 * @param result_size Ukuran buffer result
 */
void format_transaksi(const Transaksi *trx, char *result, int result_size);

/**
 * @brief Format struct PosAnggaran ke string pipe-delimited
 * @param pos Pointer ke struct PosAnggaran sumber
 * @param result Buffer untuk menyimpan hasil
 * @param result_size Ukuran buffer result
 */
void format_pos(const PosAnggaran *pos, char *result, int result_size);

/**
 * @brief Format struct AnalisisKeuangan ke string pipe-delimited
 * @param data Pointer ke struct AnalisisKeuangan sumber
 * @param result Buffer untuk menyimpan hasil
 * @param result_size Ukuran buffer result
 */
void format_analisis(const AnalisisKeuangan *data, char *result, int result_size);

/**
 * @brief Mendapatkan label jenis transaksi
 * @param jenis Kode jenis transaksi (0 atau 1)
 * @return "Pengeluaran" atau "Pemasukan"
 */
const char* get_label_jenis(int jenis);

/**
 * @brief Konversi string jenis ke kode
 * @param jenis_str String "Pemasukan" atau "Pengeluaran"
 * @return 0 untuk Pengeluaran, 1 untuk Pemasukan, -1 jika invalid
 */
int parse_jenis_transaksi(const char *jenis_str);

#endif /* FILE_PARSER_H */
