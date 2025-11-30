/**
 * @file utils_array.h
 * @brief Header untuk fungsi utilitas operasi array dinamis
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi untuk alokasi dan dealokasi
 * array dinamis Transaksi dan PosAnggaran.
 */

#ifndef UTILS_ARRAY_H
#define UTILS_ARRAY_H

#include "../types.h"

/**
 * @brief Mengalokasikan array Transaksi
 * @param size Jumlah elemen yang akan dialokasikan
 * @return Pointer ke array Transaksi, atau NULL jika gagal
 * 
 * Caller bertanggung jawab untuk membebaskan memory dengan free_transaksi_array()
 */
Transaksi* alloc_transaksi_array(int size);

/**
 * @brief Mengalokasikan array PosAnggaran
 * @param size Jumlah elemen yang akan dialokasikan
 * @return Pointer ke array PosAnggaran, atau NULL jika gagal
 * 
 * Caller bertanggung jawab untuk membebaskan memory dengan free_pos_array()
 */
PosAnggaran* alloc_pos_array(int size);

/**
 * @brief Membebaskan memory array Transaksi
 * @param arr Pointer ke array yang akan dibebaskan
 */
void free_transaksi_array(Transaksi *arr);

/**
 * @brief Membebaskan memory array PosAnggaran
 * @param arr Pointer ke array yang akan dibebaskan
 */
void free_pos_array(PosAnggaran *arr);

/**
 * @brief Menginisialisasi struct ListTransaksi
 * @param list Pointer ke ListTransaksi yang akan diinisialisasi
 * @param initial_capacity Kapasitas awal
 * @return 1 jika berhasil, 0 jika gagal
 */
int init_list_transaksi(ListTransaksi *list, int initial_capacity);

/**
 * @brief Membebaskan memory ListTransaksi
 * @param list Pointer ke ListTransaksi yang akan dibebaskan
 */
void free_list_transaksi(ListTransaksi *list);

/**
 * @brief Menambahkan transaksi ke ListTransaksi
 * @param list Pointer ke ListTransaksi
 * @param trx Pointer ke Transaksi yang akan ditambahkan
 * @return 1 jika berhasil, 0 jika gagal
 * 
 * Fungsi ini akan memperbesar kapasitas jika diperlukan
 */
int add_to_list_transaksi(ListTransaksi *list, const Transaksi *trx);

/**
 * @brief Menginisialisasi struct ListPos
 * @param list Pointer ke ListPos yang akan diinisialisasi
 * @param initial_capacity Kapasitas awal
 * @return 1 jika berhasil, 0 jika gagal
 */
int init_list_pos(ListPos *list, int initial_capacity);

/**
 * @brief Membebaskan memory ListPos
 * @param list Pointer ke ListPos yang akan dibebaskan
 */
void free_list_pos(ListPos *list);

/**
 * @brief Menambahkan pos anggaran ke ListPos
 * @param list Pointer ke ListPos
 * @param pos Pointer ke PosAnggaran yang akan ditambahkan
 * @return 1 jika berhasil, 0 jika gagal
 * 
 * Fungsi ini akan memperbesar kapasitas jika diperlukan
 */
int add_to_list_pos(ListPos *list, const PosAnggaran *pos);

/**
 * @brief Menginisialisasi struct Transaksi ke nilai default
 * @param trx Pointer ke Transaksi yang akan diinisialisasi
 */
void init_transaksi(Transaksi *trx);

/**
 * @brief Menginisialisasi struct PosAnggaran ke nilai default
 * @param pos Pointer ke PosAnggaran yang akan diinisialisasi
 */
void init_pos_anggaran(PosAnggaran *pos);

/**
 * @brief Menginisialisasi struct AnalisisKeuangan ke nilai default
 * @param analisis Pointer ke AnalisisKeuangan yang akan diinisialisasi
 */
void init_analisis_keuangan(AnalisisKeuangan *analisis);

#endif /* UTILS_ARRAY_H */
