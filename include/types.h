/**
 * @file types.h
 * @brief Definisi struktur data dan typedef untuk Aplikasi Keuangan Mahasiswa
 * @author Kelompok B11
 * @date 2025
 * 
 * File ini mendefinisikan semua struct dan typedef yang digunakan
 * dalam aplikasi. Di-include oleh hampir semua modul lain.
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Struct untuk menyimpan komponen tanggal
 * 
 * Digunakan untuk parsing dan manipulasi tanggal
 */
typedef struct {
    int hari;                   /* Hari (1-31) */
    int bulan;                  /* Bulan (1-12) */
    int tahun;                  /* Tahun (4 digit) */
} Tanggal;

/**
 * @brief Struct untuk menyimpan data satu transaksi keuangan
 * 
 * Menyimpan informasi lengkap tentang transaksi baik pemasukan maupun pengeluaran
 */
typedef struct {
    char id[6];                 /* ID transaksi (T0001-T9999) */
    char tanggal[11];           /* Format dd-mm-YYYY */
    int jenis;                  /* 0=Pengeluaran, 1=Pemasukan */
    char pos[21];               /* Nama pos anggaran (max 20 char) */
    unsigned long long nominal; /* Nilai transaksi > 0 */
    char deskripsi[51];         /* Keterangan (max 50 char) */
} Transaksi;

/**
 * @brief Struct untuk menyimpan data pos anggaran beserta realisasinya
 * 
 * Digunakan untuk tracking budget dan pengeluaran aktual per kategori
 */
typedef struct {
    int no;                     /* Nomor urut pos */
    char nama[21];              /* Nama pos (max 20 karakter) */
    unsigned long long nominal; /* Batas anggaran */
    unsigned long long realisasi; /* Total pengeluaran aktual */
    long long sisa;             /* Sisa = nominal - realisasi */
    int jumlah_transaksi;       /* Banyak transaksi pada pos */
    int status;                 /* 1=Aman, 0=Tidak Aman */
} PosAnggaran;

/**
 * @brief Struct untuk menyimpan hasil analisis keuangan bulanan
 * 
 * Berisi semua perhitungan dan kesimpulan kondisi keuangan
 */
typedef struct {
    unsigned long long total_pemasukan;    /* Jumlah seluruh pemasukan */
    unsigned long long total_pengeluaran;  /* Jumlah seluruh pengeluaran */
    double rata_rata_pengeluaran;          /* Rata-rata per transaksi pengeluaran */
    double persentase_sisa;                /* Sisa / total pemasukan * 100 */
    long long saldo_akhir;                 /* Pemasukan - Pengeluaran */
    int kondisi_keuangan;                  /* 0=Defisit, 1=Seimbang, 2=Surplus */
    int kesimpulan;                        /* 0-3 (lihat ketentuan) */
    int total_trx_pengeluaran;             /* Jumlah transaksi pengeluaran */
    int total_trx_pemasukan;               /* Jumlah transaksi pemasukan */
} AnalisisKeuangan;

/**
 * @brief Struct untuk array dinamis transaksi
 * 
 * Digunakan untuk mengelola koleksi transaksi dengan ukuran dinamis
 */
typedef struct {
    Transaksi *data;            /* Pointer ke array transaksi */
    int count;                  /* Jumlah transaksi saat ini */
    int capacity;               /* Kapasitas maksimal array */
} ListTransaksi;

/**
 * @brief Struct untuk array dinamis pos anggaran
 * 
 * Digunakan untuk mengelola koleksi pos anggaran dengan ukuran dinamis
 */
typedef struct {
    PosAnggaran *data;          /* Pointer ke array pos anggaran */
    int count;                  /* Jumlah pos saat ini */
    int capacity;               /* Kapasitas maksimal array */
} ListPos;

#endif /* TYPES_H */
