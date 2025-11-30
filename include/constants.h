/**
 * @file constants.h
 * @brief Definisi konstanta global untuk Aplikasi Keuangan Mahasiswa
 * @author Kelompok B11
 * @date 2025
 * 
 * File ini mendefinisikan semua konstanta yang digunakan dalam aplikasi
 * termasuk batas ukuran, nama file, dan konfigurasi warna.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ===== BATAS UKURAN DATA ===== */
#define MAX_POS_LENGTH          20      /* Panjang maksimal nama pos */
#define MAX_DESKRIPSI_LENGTH    50      /* Panjang maksimal deskripsi */
#define MAX_ID_LENGTH           5       /* Panjang ID transaksi (T0001) */
#define MAX_TANGGAL_LENGTH      10      /* Format dd-mm-YYYY */
#define MAX_TRANSAKSI           1000    /* Maksimal transaksi per bulan */
#define MAX_POS                 50      /* Maksimal pos anggaran */
#define MAX_LINE_LENGTH         512     /* Panjang maksimal baris file */
#define MAX_PATH_LENGTH         256     /* Panjang maksimal path file */

/* ===== NAMA FILE DATA ===== */
#define FILE_POS                "pos_anggaran"      /* Nama dasar file pos */
#define FILE_TRANSAKSI          "transaksi"         /* Nama dasar file transaksi */
#define FILE_ANALISIS           "analisis_keuangan" /* Nama dasar file analisis */
#define DATA_DIR                "data/"             /* Direktori data */
#define FILE_EXTENSION          ".txt"              /* Ekstensi file */

/* ===== PREFIX FILE UNTUK FUNGSI get_filename_bulan ===== */
#define FILE_POS_PREFIX         "pos"               /* Prefix file pos */
#define FILE_ANALISIS_PREFIX    "analisis"          /* Prefix file analisis */
#define FILE_TRANSAKSI_NAME     "transaksi.txt"     /* Nama file transaksi */
#define MAX_PATH                MAX_PATH_LENGTH     /* Alias untuk MAX_PATH_LENGTH */

/* ===== KONDISI KEUANGAN TAMBAHAN ===== */
#define KONDISI_NORMAL          1                   /* Kondisi normal/default */

/* ===== KONFIGURASI WARNA (ncurses color pairs) ===== */
#define COLOR_PAIR_CYAN         1       /* Pair warna cyan untuk data */
#define COLOR_PAIR_RED          2       /* Pair warna merah untuk error */
#define COLOR_PAIR_HIGHLIGHT    3       /* Pair warna highlight menu */
#define COLOR_PAIR_GREEN        4       /* Pair warna hijau untuk sukses */
#define COLOR_PAIR_YELLOW       5       /* Pair warna kuning untuk warning */
#define COLOR_PAIR_WHITE        6       /* Pair warna putih untuk text biasa */

/* ===== JENIS TRANSAKSI ===== */
#define JENIS_PENGELUARAN       0       /* Kode untuk pengeluaran */
#define JENIS_PEMASUKAN         1       /* Kode untuk pemasukan */

/* ===== KONDISI KEUANGAN ===== */
#define KONDISI_DEFISIT         0       /* Pengeluaran > Pemasukan */
#define KONDISI_SEIMBANG        1       /* Pengeluaran = Pemasukan */
#define KONDISI_SURPLUS         2       /* Pemasukan > Pengeluaran */

/* ===== KESIMPULAN KEUANGAN ===== */
#define KESIMPULAN_HEMAT        0       /* Sisa > 25% pemasukan */
#define KESIMPULAN_SEIMBANG     1       /* Sisa 0% < x <= 25% */
#define KESIMPULAN_BOROS        2       /* Sisa -10% <= x <= 0% */
#define KESIMPULAN_TIDAK_SEHAT  3       /* Sisa < -10% */

/* ===== STATUS POS ANGGARAN ===== */
#define STATUS_TIDAK_AMAN       0       /* Realisasi > Nominal */
#define STATUS_AMAN             1       /* Realisasi <= Nominal */

/* ===== KODE RETURN ===== */
#define SUCCESS                 1       /* Operasi berhasil */
#define FAILURE                 0       /* Operasi gagal */
#define CANCEL                  -1      /* Operasi dibatalkan user */

/* ===== KONFIGURASI MENU ===== */
#define MENU_HIGHLIGHT_CHAR     '>'     /* Karakter penanda item terpilih */
#define MENU_CANCEL_KEY         'X'     /* Tombol untuk cancel */

/* ===== BULAN ===== */
#define BULAN_MIN               1       /* Januari */
#define BULAN_MAX               12      /* Desember */

/* ===== JUDUL APLIKASI ===== */
#define APP_TITLE               "APLIKASI KEUANGAN MAHASISWA"
#define APP_SUBTITLE            "-Created by Kelompok B11-"
#define APP_VERSION             "1.0"

#endif /* CONSTANTS_H */
