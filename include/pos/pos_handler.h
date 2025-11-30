/**
 * @file pos_handler.h
 * @brief Header untuk handler utama pos anggaran
 * @author Kelompok B11
 * @date 2025
 * 
 * Entry point untuk modul pos anggaran yang mengintegrasikan
 * semua fungsi CRUD, display, dan menu.
 */

#ifndef POS_HANDLER_H
#define POS_HANDLER_H

/**
 * @brief Jalankan modul pos anggaran
 * @param bulan_awal Bulan awal yang ditampilkan (1-12)
 * 
 * Entry point utama untuk modul pos anggaran.
 * Menampilkan menu dan menangani semua operasi pos.
 */
void run_pos_module(int bulan_awal);

/**
 * @brief Inisialisasi data pos untuk bulan baru
 * @param bulan Bulan yang akan diinisialisasi
 * @return 1 jika berhasil, 0 jika gagal
 * 
 * Akan membuat file pos kosong jika belum ada,
 * atau menawarkan copy dari bulan sebelumnya.
 */
int init_pos_for_bulan(int bulan);

/**
 * @brief Sinkronisasi kalkulasi pos dengan transaksi
 * @param bulan Bulan yang akan disinkronisasi
 * @return 1 jika berhasil, 0 jika gagal
 * 
 * Mengupdate realisasi, sisa, dan status semua pos
 * berdasarkan transaksi di bulan tersebut.
 */
int sync_pos_transaksi(int bulan);

#endif /* POS_HANDLER_H */
