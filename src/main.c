/*
 * =============================================================================
 * File        : main.c
 * Deskripsi   : File utama program Aplikasi Keuangan Mahasiswa
 * Author      : Hafiz Fauzan Syafrudin
 * Version     : v1.0
 * Tanggal     : 3 Desember 2025
 * =============================================================================
 *
 * TUJUAN MODUL:
 * Modul ini merupakan titik masuk (entry point) aplikasi keuangan mahasiswa.
 * Bertanggung jawab untuk:
 * - Inisialisasi sistem (locale, direktori data, TUI)
 * - Menampilkan splash screen pembuka
 * - Menjalankan loop utama menu aplikasi
 * - Mengkoordinasikan navigasi antar modul (transaksi, pos, analisis)
 * - Menangani pembersihan saat aplikasi ditutup
 *
 * MODUL YANG DIBUTUHKAN (DEPENDENCIES):
 * - stdio.h     : Untuk output error ke stderr
 * - stdlib.h    : Untuk fungsi umum C
 * - locale.h    : Untuk dukungan karakter Unicode
 * - string.h    : Untuk manipulasi string
 * - file.h      : Untuk memastikan direktori data ada
 * - tui.h       : Untuk antarmuka pengguna
 * - pos.h       : Untuk modul pos anggaran
 * - transaksi.h : Untuk modul transaksi
 * - analisis.h  : Untuk modul analisis keuangan
 * - utils.h     : Untuk fungsi utilitas
 *
 * CATATAN:
 * Program ini menggunakan ncurses untuk tampilan TUI interaktif.
 * Bulan aktif disimpan secara global untuk koordinasi antar modul.
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "file.h"
#include "tui.h"
#include "pos.h"
#include "transaksi.h"
#include "analisis.h"
#include "utils.h"

/* ===== KONSTANTA LOKAL ===== */
/* Aksi Menu */
#define ACT_TRANSAKSI   1
#define ACT_POS         2
#define ACT_ANALISIS    3
#define ACT_BULAN       4
#define ACT_BANTUAN     5
#define ACT_TENTANG     6
#define ACT_KELUAR      0

/* ===== VARIABEL GLOBAL LOKAL ===== */
static int bulan_aktif = 0;

/* ===== DEKLARASI FUNGSI LOKAL ===== */
static void tampilkan_splash_screen(void);
static int menu_utama(void);
static int pilih_bulan_global(int bulan_saat_ini);
static void tampilkan_tentang(void);
static void tampilkan_bantuan(void);

/* ===== FUNGSI UTAMA ===== */

/*
 * -----------------------------------------------------------------------------
 * Nama Fungsi    : main
 * -----------------------------------------------------------------------------
 * Deskripsi      : Fungsi utama aplikasi - titik masuk program. Melakukan
 *                  inisialisasi sistem, menampilkan splash screen, dan
 *                  menjalankan loop utama menu aplikasi.
 *
 * Mengembalikan  : int - 0 jika aplikasi berjalan dan ditutup dengan sukses,
 *                  1 jika terjadi error saat inisialisasi
 *
 * Modul Pemanggil: Sistem operasi (entry point program)
 * Modul Dipanggil: pastikan_direktori_data, tui_inisialisasi, tui_inisialisasi_warna,
 *                  dapatkan_bulan_saat_ini, tampilkan_splash_screen, menu_utama,
 *                  jalankan_modul_transaksi, jalankan_modul_pos, jalankan_modul_analisis,
 *                  pilih_bulan_global, tampilkan_bantuan, tampilkan_tentang,
 *                  tampilkan_konfirmasi, tui_bersihkan
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input: Tidak ada
 *
 * Parameter Output: Tidak ada (status dikembalikan via return)
 * -----------------------------------------------------------------------------
 */
int main(void) {
    /* Atur locale untuk mendukung karakter khusus */
    setlocale(LC_ALL, "");

    /* Pastikan direktori data ada */
    if (!pastikan_direktori_data()) {
        fprintf(stderr, "Error: Tidak dapat membuat direktori data.\n");
        return 1;
    }

    /* Inisialisasi TUI */
    tui_inisialisasi();
    tui_inisialisasi_warna();

    /* Atur bulan aktif ke bulan saat ini */
    bulan_aktif = dapatkan_bulan_saat_ini();

    /* Tampilkan splash screen */
    tampilkan_splash_screen();

    /* Loop Utama */
    int berjalan = 1;
    while (berjalan) {
        int aksi = menu_utama();

        switch (aksi) {
            case ACT_TRANSAKSI:
                jalankan_modul_transaksi(bulan_aktif);
                break;

            case ACT_POS:
                jalankan_modul_pos(bulan_aktif);
                break;

            case ACT_ANALISIS:
                jalankan_modul_analisis(bulan_aktif);
                break;

            case ACT_BULAN:
                bulan_aktif = pilih_bulan_global(bulan_aktif);
                break;

            case ACT_BANTUAN:
                tampilkan_bantuan();
                break;

            case ACT_TENTANG:
                tampilkan_tentang();
                break;

            case ACT_KELUAR:
            case CANCEL:
                if (tampilkan_konfirmasi("Keluar dari aplikasi?")) {
                    berjalan = 0;
                }
                break;
        }
    }

    /* Pembersihan */
    tui_bersihkan();

    return 0;
}

/* ===== IMPLEMENTASI FUNGSI LOKAL ===== */

/*
 * -----------------------------------------------------------------------------
 * Nama Prosedur  : tampilkan_splash_screen
 * -----------------------------------------------------------------------------
 * Deskripsi      : Menampilkan layar pembuka (splash screen) aplikasi dengan
 *                  banner ASCII art, informasi pembuat, dan versi aplikasi.
 *
 * Perubahan State: Menampilkan konten ke layar terminal
 *
 * I.S (Initial State)  : TUI sudah terinisialisasi, layar mungkin berisi konten
 * F.S (Final State)    : Splash screen ditampilkan, program menunggu input user
 *
 * Modul Pemanggil: main (main.c)
 * Modul Dipanggil: tui_hapus_layar, tui_ambil_tinggi, tui_ambil_lebar,
 *                  tui_aktifkan_warna, tui_aktifkan_tebal, tui_cetak,
 *                  tui_cetak_tengah, tui_segarkan, tui_ambil_karakter
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input: Tidak ada
 *
 * Parameter Output: Tidak ada (output ke layar)
 * -----------------------------------------------------------------------------
 */
static void tampilkan_splash_screen(void) {
    tui_hapus_layar();

    int center_y = tui_ambil_tinggi() / 2 - 5;
    int center_x = tui_ambil_lebar() / 2;

    /* Logo/Spanduk */
    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_aktifkan_tebal();

    const char *banner[] = {
        "╔═══════════════════════════════════════════════════╗",
        "║                                                   ║",
        "║           APLIKASI KEUANGAN MAHASISWA             ║",
        "║                                                   ║",
        "║           Kelola Keuangan dengan Mudah            ║",
        "║                                                   ║",
        "╚═══════════════════════════════════════════════════╝"
    };

    int banner_width = 53;
    int start_x = center_x - banner_width / 2;

    for (int i = 0; i < 7; i++) {
        tui_cetak(center_y + i, start_x, banner[i]);
    }

    tui_nonaktifkan_tebal();
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);

    /* Subjudul */
    tui_aktifkan_warna(COLOR_PAIR_YELLOW);
    tui_cetak_tengah(center_y + 8, "- Dibuat oleh Kelompok B11 -");
    tui_nonaktifkan_warna(COLOR_PAIR_YELLOW);

    /* Versi */
    tui_cetak_tengah(center_y + 10, "Versi 2.0");

    /* Prompt */
    tui_aktifkan_warna(COLOR_PAIR_GREEN);
    tui_cetak_tengah(center_y + 13, "Tekan sembarang tombol untuk melanjutkan...");
    tui_nonaktifkan_warna(COLOR_PAIR_GREEN);

    tui_segarkan();
    tui_ambil_karakter();
}

/*
 * -----------------------------------------------------------------------------
 * Nama Fungsi    : menu_utama
 * -----------------------------------------------------------------------------
 * Deskripsi      : Menampilkan dan menangani navigasi menu utama aplikasi.
 *                  Menu terdiri dari pilihan: Transaksi, Pos Anggaran, Analisis,
 *                  Ganti Bulan, Bantuan, Tentang, dan Keluar.
 *
 * Mengembalikan  : int - Kode aksi yang dipilih pengguna (ACT_TRANSAKSI,
 *                  ACT_POS, ACT_ANALISIS, ACT_BULAN, ACT_BANTUAN,
 *                  ACT_TENTANG, ACT_KELUAR, atau CANCEL)
 *
 * Modul Pemanggil: main (main.c)
 * Modul Dipanggil: dapatkan_nama_bulan, menu_inisialisasi, menu_tambah_item,
 *                  menu_navigasi
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input: Tidak ada (menggunakan variabel global bulan_aktif)
 *
 * Parameter Output: Tidak ada (nilai dikembalikan via return)
 * -----------------------------------------------------------------------------
 */
static int menu_utama(void) {
    char judul[80];
    snprintf(judul, sizeof(judul), "MENU UTAMA - Bulan: %s", dapatkan_nama_bulan(bulan_aktif));

    Menu menu;
    menu_inisialisasi(&menu, judul);

    menu_tambah_item(&menu, "Kelola Transaksi", ACT_TRANSAKSI);
    menu_tambah_item(&menu, "Kelola Pos Anggaran", ACT_POS);
    menu_tambah_item(&menu, "Analisis Keuangan", ACT_ANALISIS);
    menu_tambah_item(&menu, "Ganti Bulan", ACT_BULAN);
    menu_tambah_item(&menu, "Bantuan", ACT_BANTUAN);
    menu_tambah_item(&menu, "Tentang", ACT_TENTANG);
    menu_tambah_item(&menu, "Keluar", ACT_KELUAR);

    return menu_navigasi(&menu);
}

/*
 * -----------------------------------------------------------------------------
 * Nama Fungsi    : pilih_bulan_global
 * -----------------------------------------------------------------------------
 * Deskripsi      : Wrapper function untuk menampilkan menu pemilihan bulan
 *                  dan mengembalikan bulan yang dipilih pengguna.
 *
 * Mengembalikan  : int - Nomor bulan yang dipilih (1-12), atau bulan saat ini
 *                  jika pengguna membatalkan
 *
 * Modul Pemanggil: main (main.c)
 * Modul Dipanggil: menu_pilih_bulan (pos.c)
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input:
 *   - bulan_saat_ini (int) : Bulan yang sedang aktif saat ini
 *
 * Parameter Output: Tidak ada (nilai dikembalikan via return)
 * -----------------------------------------------------------------------------
 */
static int pilih_bulan_global(int bulan_saat_ini) {
    return menu_pilih_bulan(bulan_saat_ini);
}

/*
 * -----------------------------------------------------------------------------
 * Nama Prosedur  : tampilkan_tentang
 * -----------------------------------------------------------------------------
 * Deskripsi      : Menampilkan halaman informasi tentang aplikasi, termasuk
 *                  versi, pembuat, mata kuliah, dan daftar fitur utama.
 *
 * Perubahan State: Menampilkan konten ke layar terminal
 *
 * I.S (Initial State)  : TUI sudah terinisialisasi, berada di menu utama
 * F.S (Final State)    : Halaman tentang ditampilkan, menunggu input user
 *                        untuk kembali ke menu
 *
 * Modul Pemanggil: main (main.c)
 * Modul Dipanggil: tui_hapus_layar, tampilkan_header, tui_aktifkan_warna,
 *                  tui_cetak, tui_gambar_garis_horizontal, tampilkan_footer,
 *                  tui_segarkan, tui_ambil_karakter
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input: Tidak ada
 *
 * Parameter Output: Tidak ada (output ke layar)
 * -----------------------------------------------------------------------------
 */
static void tampilkan_tentang(void) {
    tui_hapus_layar();
    tampilkan_header("TENTANG APLIKASI");

    int y = 5;

    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_aktifkan_tebal();
    tui_cetak(y++, 2, "APLIKASI KEUANGAN MAHASISWA");
    tui_nonaktifkan_tebal();
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);

    tui_cetak(y++, 2, "Versi 1.0");
    y++;

    tui_gambar_garis_horizontal(y++, 2, 50, '-');

    tui_cetak(y++, 2, "Dibuat oleh: Kelompok B11");
    tui_cetak(y++, 2, "Mata Kuliah: Dasar Pemrograman");
    tui_cetak(y++, 2, "Tahun: 2025");
    y++;

    tui_gambar_garis_horizontal(y++, 2, 50, '-');

    tui_aktifkan_tebal();
    tui_cetak(y++, 2, "Fitur Utama:");
    tui_nonaktifkan_tebal();

    tui_cetak(y++, 4, "* Pencatatan transaksi pemasukan & pengeluaran");
    tui_cetak(y++, 4, "* Pengelolaan pos anggaran bulanan");
    tui_cetak(y++, 4, "* Analisis kondisi keuangan otomatis");
    tui_cetak(y++, 4, "* Grafik perbandingan pemasukan/pengeluaran");
    tui_cetak(y++, 4, "* Saran pengelolaan keuangan");
    y++;

    tui_gambar_garis_horizontal(y++, 2, 50, '-');

    tui_aktifkan_warna(COLOR_PAIR_YELLOW);
    tui_cetak(y++, 2, "Terima kasih telah menggunakan aplikasi ini!");
    tui_nonaktifkan_warna(COLOR_PAIR_YELLOW);

    tampilkan_footer("Tekan sembarang tombol untuk kembali");
    tui_segarkan();
    tui_ambil_karakter();
}

/*
 * -----------------------------------------------------------------------------
 * Nama Prosedur  : tampilkan_bantuan
 * -----------------------------------------------------------------------------
 * Deskripsi      : Menampilkan halaman bantuan penggunaan aplikasi dengan
 *                  panduan navigasi keyboard dan penjelasan setiap menu.
 *
 * Perubahan State: Menampilkan konten ke layar terminal
 *
 * I.S (Initial State)  : TUI sudah terinisialisasi, berada di menu utama
 * F.S (Final State)    : Halaman bantuan ditampilkan, menunggu input user
 *                        untuk kembali ke menu
 *
 * Modul Pemanggil: main (main.c)
 * Modul Dipanggil: tui_hapus_layar, tampilkan_header, tui_aktifkan_warna,
 *                  tui_cetak, tampilkan_footer, tui_segarkan, tui_ambil_karakter
 *
 * Author/PIC     : Hafiz Fauzan Syafrudin
 * Version        : v1.0 (3 Desember 2025)
 * -----------------------------------------------------------------------------
 * Parameter Input: Tidak ada
 *
 * Parameter Output: Tidak ada (output ke layar)
 * -----------------------------------------------------------------------------
 */
static void tampilkan_bantuan(void) {
    tui_hapus_layar();
    tampilkan_header("BANTUAN PENGGUNAAN");

    int y = 5;

    tui_aktifkan_tebal();
    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_cetak(y++, 2, "NAVIGASI:");
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);
    tui_nonaktifkan_tebal();

    tui_cetak(y++, 4, "ATAS/BAWAH atau k/j  : Pindah pilihan menu");
    tui_cetak(y++, 4, "ENTER                : Pilih/Konfirmasi");
    tui_cetak(y++, 4, "ESC                  : Kembali/Batal");
    tui_cetak(y++, 4, "1-9                  : Pilih langsung item menu");
    y++;

    tui_aktifkan_tebal();
    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_cetak(y++, 2, "MENU TRANSAKSI:");
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);
    tui_nonaktifkan_tebal();

    tui_cetak(y++, 4, "* Tambah transaksi pemasukan atau pengeluaran");
    tui_cetak(y++, 4, "* Edit data transaksi yang sudah ada");
    tui_cetak(y++, 4, "* Hapus transaksi");
    tui_cetak(y++, 4, "* Lihat daftar dan detail transaksi");
    y++;

    tui_aktifkan_tebal();
    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_cetak(y++, 2, "MENU POS ANGGARAN:");
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);
    tui_nonaktifkan_tebal();

    tui_cetak(y++, 4, "* Buat pos anggaran baru dengan batas nominal");
    tui_cetak(y++, 4, "* Edit nama atau nominal pos");
    tui_cetak(y++, 4, "* Hapus pos (hanya jika tidak ada transaksi)");
    tui_cetak(y++, 4, "* Lihat realisasi dan sisa anggaran");
    y++;

    tui_aktifkan_tebal();
    tui_aktifkan_warna(COLOR_PAIR_CYAN);
    tui_cetak(y++, 2, "MENU ANALISIS:");
    tui_nonaktifkan_warna(COLOR_PAIR_CYAN);
    tui_nonaktifkan_tebal();

    tui_cetak(y++, 4, "* Lihat ringkasan keuangan bulanan");
    tui_cetak(y++, 4, "* Grafik perbandingan pemasukan/pengeluaran");
    tui_cetak(y++, 4, "* Kesimpulan dan saran otomatis");

    tampilkan_footer("Tekan sembarang tombol untuk kembali");
    tui_segarkan();
    tui_ambil_karakter();
}
