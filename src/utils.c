/*
 * =============================================================================
 * File        : utils.c
 * Deskripsi   : Implementasi modul utilitas dan fungsi-fungsi pendukung
 * Author      : Ghaisan Khoirul Badruzaman
 * Version     : v1.0
 * Tanggal     : 3 Desember 2025
 * =============================================================================
 *
 * TUJUAN MODUL:
 * Modul ini mengimplementasikan fungsi-fungsi utilitas umum yang digunakan
 * di seluruh aplikasi, termasuk:
 * - Alokasi dan manajemen memori dinamis untuk struktur data
 * - Pemrosesan dan manipulasi tanggal (parsing, formatting, validasi)
 * - Pemrosesan dan manipulasi string (trim, case conversion, safe copy)
 * - Formatting angka ke format Rupiah dan persentase
 * - Fungsi validasi input (tanggal, nominal, string)
 *
 * MODUL YANG DIBUTUHKAN (DEPENDENCIES):
 * - stdlib.h    : Untuk alokasi memori dinamis (malloc, free, strtoull)
 * - stdio.h     : Untuk fungsi input/output standar (snprintf)
 * - string.h    : Untuk manipulasi string (strlen, strcpy, memset)
 * - ctype.h     : Untuk pengecekan dan konversi karakter (isdigit, tolower)
 * - time.h      : Untuk mendapatkan tanggal/waktu sistem (localtime)
 * - errno.h     : Untuk penanganan error pada konversi numerik
 * - utils.h     : Header file modul ini
 * - pos.h       : Untuk definisi struct PosAnggaran
 * - transaksi.h : Untuk definisi struct Transaksi
 * - analisis.h  : Untuk definisi struct AnalisisKeuangan
 *
 * CATATAN:
 * Fungsi-fungsi validasi telah dipindahkan dari validator.c ke modul ini
 * untuk konsolidasi fungsi-fungsi utilitas umum.
 * =============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include "utils.h"
#include "pos.h"
#include "transaksi.h"
#include "analisis.h"

/* ===== KONSTANTA LOKAL ===== */

/* Array nama bulan dalam Bahasa Indonesia */
static const char *nama_bulan[] = {
    "Tidak Valid",
    "Januari",
    "Februari",
    "Maret",
    "April",
    "Mei",
    "Juni",
    "Juli",
    "Agustus",
    "September",
    "Oktober",
    "November",
    "Desember"
};

/* Array nama bulan singkat */
static const char *nama_bulan_singkat[] = {
    "Inv",
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "Mei",
    "Jun",
    "Jul",
    "Agu",
    "Sep",
    "Okt",
    "Nov",
    "Des"
};

/* Array kode bulan 2 digit */
static const char *kode_bulan[] = {
    "00",
    "01", "02", "03", "04", "05", "06",
    "07", "08", "09", "10", "11", "12"
};

/* Tabel jumlah hari per bulan (non-kabisat) */
static const int days_in_month[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/* ===== FUNGSI HELPER INTERNAL ===== */

/**
 * Helper: Membalik string di tempat (in-place)
 * I.S.: str berisi string
 * F.S.: Urutan karakter dalam str dibalik
 */
static void balik_string(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

/**
 * Helper: Membandingkan string tanpa memperhatikan besar kecil huruf
 */
static int banding_str_nocase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/* ===== IMPLEMENTASI MANAJEMEN MEMORI ===== */

/**
 * Mengalokasikan array Transaksi
 */
Transaksi* alokasi_array_transaksi(int size) {
    if (size <= 0) return NULL;

    Transaksi *arr = (Transaksi*)malloc(size * sizeof(Transaksi));
    if (arr != NULL) {
        /* Inisialisasi semua elemen */
        memset(arr, 0, size * sizeof(Transaksi));
    }
    return arr;
}

/**
 * Mengalokasikan array PosAnggaran
 */
PosAnggaran* alokasi_array_pos(int size) {
    if (size <= 0) return NULL;

    PosAnggaran *arr = (PosAnggaran*)malloc(size * sizeof(PosAnggaran));
    if (arr != NULL) {
        /* Inisialisasi semua elemen */
        memset(arr, 0, size * sizeof(PosAnggaran));
    }
    return arr;
}

/**
 * Membebaskan memory array Transaksi
 */
void bebaskan_array_transaksi(Transaksi *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

/**
 * Membebaskan memory array PosAnggaran
 */
void bebaskan_array_pos(PosAnggaran *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

/**
 * Menginisialisasi struct ListTransaksi
 */
int inisialisasi_list_transaksi(ListTransaksi *list, int initial_capacity) {
    if (list == NULL || initial_capacity <= 0) return FAILURE;

    list->data = alokasi_array_transaksi(initial_capacity);
    if (list->data == NULL) return FAILURE;

    list->count = 0;
    list->capacity = initial_capacity;
    return SUCCESS;
}

/**
 * Membebaskan memory ListTransaksi
 */
void bebaskan_list_transaksi(ListTransaksi *list) {
    if (list == NULL) return;

    bebaskan_array_transaksi(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

/**
 * Menambahkan transaksi ke ListTransaksi
 */
int tambah_ke_list_transaksi(ListTransaksi *list, const Transaksi *trx) {
    if (list == NULL || trx == NULL) return FAILURE;

    /* Cek apakah perlu memperbesar kapasitas */
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Transaksi *new_data = (Transaksi*)realloc(list->data,
                                                   new_capacity * sizeof(Transaksi));
        if (new_data == NULL) return FAILURE;

        list->data = new_data;
        list->capacity = new_capacity;
    }

    /* Salin data transaksi */
    memcpy(&list->data[list->count], trx, sizeof(Transaksi));
    list->count++;

    return SUCCESS;
}

/**
 * Menginisialisasi struct ListPos
 */
int inisialisasi_list_pos(ListPos *list, int initial_capacity) {
    if (list == NULL || initial_capacity <= 0) return FAILURE;

    list->data = alokasi_array_pos(initial_capacity);
    if (list->data == NULL) return FAILURE;

    list->count = 0;
    list->capacity = initial_capacity;
    return SUCCESS;
}

/**
 * Membebaskan memory ListPos
 */
void bebaskan_list_pos(ListPos *list) {
    if (list == NULL) return;

    bebaskan_array_pos(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

/**
 * Menambahkan pos anggaran ke ListPos
 */
int tambah_ke_list_pos(ListPos *list, const PosAnggaran *pos) {
    if (list == NULL || pos == NULL) return FAILURE;

    /* Cek apakah perlu memperbesar kapasitas */
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        PosAnggaran *new_data = (PosAnggaran*)realloc(list->data,
                                                       new_capacity * sizeof(PosAnggaran));
        if (new_data == NULL) return FAILURE;

        list->data = new_data;
        list->capacity = new_capacity;
    }

    /* Salin data pos */
    memcpy(&list->data[list->count], pos, sizeof(PosAnggaran));
    list->count++;

    return SUCCESS;
}

/**
 * Menginisialisasi struct Transaksi ke nilai default
 */
void inisialisasi_transaksi(Transaksi *trx) {
    if (trx == NULL) return;

    memset(trx->id, 0, sizeof(trx->id));
    memset(trx->tanggal, 0, sizeof(trx->tanggal));
    trx->jenis = 0;
    memset(trx->pos, 0, sizeof(trx->pos));
    trx->nominal = 0;
    memset(trx->deskripsi, 0, sizeof(trx->deskripsi));
}

/**
 * Menginisialisasi struct PosAnggaran ke nilai default
 */
void inisialisasi_pos_anggaran(PosAnggaran *pos) {
    if (pos == NULL) return;

    pos->no = 0;
    memset(pos->nama, 0, sizeof(pos->nama));
    pos->nominal = 0;
    pos->realisasi = 0;
    pos->sisa = 0;
    pos->jumlah_transaksi = 0;
    pos->status = STATUS_AMAN;
}

/**
 * Menginisialisasi struct AnalisisKeuangan ke nilai default
 */
void inisialisasi_analisis_keuangan(AnalisisKeuangan *analisis) {
    if (analisis == NULL) return;

    analisis->total_pemasukan = 0;
    analisis->total_pengeluaran = 0;
    analisis->rata_rata_pengeluaran = 0.0;
    analisis->persentase_sisa = 0.0;
    analisis->saldo_akhir = 0;
    analisis->kondisi_keuangan = KONDISI_SEIMBANG;
    analisis->kesimpulan = KESIMPULAN_SEIMBANG;
    analisis->total_trx_pengeluaran = 0;
    analisis->total_trx_pemasukan = 0;
}

/* ===== IMPLEMENTASI FUNGSI TANGGAL & WAKTU ===== */

/**
 * Mendapatkan nama bulan dalam Bahasa Indonesia
 */
const char* dapatkan_nama_bulan(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return nama_bulan[0];  /* "Tidak Valid" */
    }
    return nama_bulan[bulan];
}

/**
 * Mendapatkan kode bulan 2 digit
 */
const char* dapatkan_kode_bulan(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return kode_bulan[0];  /* "00" */
    }
    return kode_bulan[bulan];
}

/**
 * Mendapatkan nama bulan singkat (3 huruf)
 */
const char* dapatkan_nama_bulan_singkat(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return nama_bulan_singkat[0];  /* "Inv" */
    }
    return nama_bulan_singkat[bulan];
}

/**
 * Mengkonversi nama bulan ke nomor bulan
 */
int nama_ke_nomor_bulan(const char *nama) {
    if (nama == NULL) return 0;

    for (int i = 1; i <= 12; i++) {
        if (banding_str_nocase(nama, nama_bulan[i]) == 0) {
            return i;
        }
        /* Cek juga nama singkat */
        if (banding_str_nocase(nama, nama_bulan_singkat[i]) == 0) {
            return i;
        }
    }

    return 0;  /* Tidak ditemukan */
}

/**
 * Validasi nomor bulan
 */
int cek_valid_bulan(int bulan) {
    return (bulan >= BULAN_MIN && bulan <= BULAN_MAX);
}

/**
 * Parse string tanggal ke komponen hari, bulan, tahun
 */
int urai_tanggal(const char *str, int *d, int *m, int *y) {
    if (str == NULL || d == NULL || m == NULL || y == NULL) {
        return 0;
    }

    /* Format yang diharapkan: dd-mm-YYYY */
    int parsed = sscanf(str, "%d-%d-%d", d, m, y);

    if (parsed != 3) {
        return 0;
    }

    return 1;
}

/**
 * Parse string tanggal ke struct Tanggal
 */
int urai_tanggal_struct(const char *str, Tanggal *tgl) {
    if (str == NULL || tgl == NULL) {
        return 0;
    }

    return urai_tanggal(str, &tgl->hari, &tgl->bulan, &tgl->tahun);
}

/**
 * Format komponen tanggal ke string dd-mm-YYYY
 */
void format_tanggal(int d, int m, int y, char *result) {
    if (result == NULL) return;

    sprintf(result, "%02d-%02d-%04d", d, m, y);
}

/**
 * Mendapatkan bulan saat ini dari sistem
 */
int dapatkan_bulan_saat_ini(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_mon + 1;  /* tm_mon dimulai dari 0 */
}

/**
 * Mendapatkan tahun saat ini dari sistem
 */
int dapatkan_tahun_saat_ini(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_year + 1900;  /* tm_year dihitung dari 1900 */
}

/**
 * Mendapatkan hari saat ini dari sistem
 */
int dapatkan_hari_saat_ini(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_mday;
}

/**
 * Memeriksa apakah tahun adalah tahun kabisat
 */
int cek_tahun_kabisat(int year) {
    /* Tahun kabisat: habis dibagi 4 tapi tidak habis dibagi 100,
       kecuali jika habis dibagi 400 */
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

/**
 * Mendapatkan jumlah hari dalam bulan tertentu
 */
int dapatkan_jumlah_hari_bulan(int month, int year) {
    if (month < 1 || month > 12) return 0;

    if (month == 2 && cek_tahun_kabisat(year)) {
        return 29;  /* Februari pada tahun kabisat */
    }

    return days_in_month[month];
}

/**
 * Mengekstrak bulan dari string tanggal
 */
int ekstrak_bulan(const char *tanggal) {
    int d, m, y;

    if (!urai_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    if (m < 1 || m > 12) return 0;

    return m;
}

/**
 * Mengekstrak tahun dari string tanggal
 */
int ekstrak_tahun(const char *tanggal) {
    int d, m, y;

    if (!urai_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    return y;
}

/**
 * Mendapatkan tanggal hari ini dalam format dd-mm-YYYY
 */
void dapatkan_tanggal_hari_ini_string(char *result) {
    if (result == NULL) return;

    format_tanggal(dapatkan_hari_saat_ini(), dapatkan_bulan_saat_ini(), dapatkan_tahun_saat_ini(), result);
}

/* ===== IMPLEMENTASI FORMAT ANGKA ===== */

/**
 * Memformat angka dengan separator ribuan (tanpa prefix Rp)
 */
void format_angka_pemisah(unsigned long long nominal, char *result) {
    if (result == NULL) return;

    if (nominal == 0) {
        strcpy(result, "0");
        return;
    }

    char buffer[30];
    char formatted[30];
    int i = 0, j = 0, count = 0;

    /* Konversi angka ke string */
    sprintf(buffer, "%llu", nominal);
    int len = strlen(buffer);

    /* Format dengan separator ribuan (titik) */
    for (i = len - 1; i >= 0; i--) {
        if (count > 0 && count % 3 == 0) {
            formatted[j++] = '.';
        }
        formatted[j++] = buffer[i];
        count++;
    }
    formatted[j] = '\0';

    balik_string(formatted);
    strcpy(result, formatted);
}

/**
 * Memformat nominal ke format Rupiah dengan separator ribuan
 */
void format_rupiah(unsigned long long nominal, char *result) {
    if (result == NULL) return;

    char formatted[30];
    format_angka_pemisah(nominal, formatted);

    sprintf(result, "Rp %s", formatted);
}

/**
 * Memformat persentase dengan 2 desimal
 */
void format_persentase(double persen, char *result) {
    if (result == NULL) return;

    sprintf(result, "%.2f%%", persen);
}

/**
 * Memformat nilai rata-rata dengan separator ribuan dan 2 desimal
 */
void format_rata_rata(double rata, char *result) {
    if (result == NULL) return;

    /* Ambil bagian bulat dan desimal */
    unsigned long long bagian_bulat = (unsigned long long)rata;
    int bagian_desimal = (int)((rata - bagian_bulat) * 100 + 0.5);

    /* Format bagian bulat dengan separator */
    char formatted[25];
    format_angka_pemisah(bagian_bulat, formatted);

    /* Gabungkan dengan bagian desimal */
    sprintf(result, "%s,%02d", formatted, bagian_desimal);
}

/**
 * Memformat nilai saldo (bisa negatif) ke format Rupiah
 */
void format_saldo(long long saldo, char *result) {
    if (result == NULL) return;

    if (saldo < 0) {
        char formatted[30];
        format_angka_pemisah((unsigned long long)(-saldo), formatted);
        sprintf(result, "-Rp %s", formatted);
    } else {
        format_rupiah((unsigned long long)saldo, result);
    }
}

/**
 * Mengkonversi string angka ke unsigned long long
 */
int string_ke_ull(const char *str, unsigned long long *result) {
    if (str == NULL || result == NULL) return 0;

    /* Lewati whitespace di awal */
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') return 0;

    /* Pastikan hanya digit */
    const char *p = str;
    while (*p) {
        if (!isdigit((unsigned char)*p)) {
            return 0;
        }
        p++;
    }

    /* Konversi */
    char *endptr;
    *result = strtoull(str, &endptr, 10);

    return (*endptr == '\0');
}

/**
 * Memeriksa apakah string hanya berisi digit
 */
int cek_string_numerik(const char *str) {
    if (str == NULL || *str == '\0') return 0;

    /* Lewati whitespace di awal */
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') return 0;

    /* Cek setiap karakter */
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

/* ===== IMPLEMENTASI MANIPULASI STRING ===== */

/**
 * Menghapus whitespace di awal dan akhir string
 */
void pangkas_string(char *str) {
    if (str == NULL || *str == '\0') return;

    /* Hapus whitespace di awal */
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    /* Jika string hanya whitespace */
    if (*start == '\0') {
        str[0] = '\0';
        return;
    }

    /* Hapus whitespace di akhir */
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';

    /* Geser string jika ada whitespace di awal */
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

/**
 * Mengkonversi string ke uppercase
 */
void string_ke_kapital(char *str) {
    if (str == NULL) return;

    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

/**
 * Mengkonversi string ke lowercase
 */
void string_ke_kecil(char *str) {
    if (str == NULL) return;

    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

/**
 * Menyalin string dengan batasan ukuran (safe copy)
 */
void salin_string_aman(char *dst, const char *src, int max) {
    if (dst == NULL || max <= 0) return;

    if (src == NULL) {
        dst[0] = '\0';
        return;
    }

    int i;
    for (i = 0; i < max - 1 && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

/**
 * Memisahkan string berdasarkan delimiter
 * Catatan: Fungsi ini memodifikasi string asli
 */
int pisah_string(char *str, char delim, char **result, int max_parts) {
    if (str == NULL || result == NULL || max_parts <= 0) return 0;

    int count = 0;
    char *token = str;
    char *next;

    while (token != NULL && count < max_parts) {
        /* Cari delimiter berikutnya */
        next = strchr(token, delim);

        /* Simpan pointer ke bagian ini */
        result[count++] = token;

        if (next != NULL) {
            *next = '\0';  /* Ganti delimiter dengan null terminator */
            token = next + 1;
        } else {
            break;
        }
    }

    return count;
}

/**
 * Memeriksa apakah string kosong (hanya whitespace atau NULL)
 */
int cek_string_kosong(const char *str) {
    if (str == NULL) return 1;

    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0;  /* Ditemukan karakter non-whitespace */
        }
        str++;
    }
    return 1;  /* String kosong atau hanya whitespace */
}

/**
 * Membandingkan dua string secara case-insensitive
 */
int banding_string_tanpa_case(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;

    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/**
 * Menghapus karakter newline dari akhir string
 */
void hapus_newline_string(char *str) {
    if (str == NULL) return;

    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}

/* ===== IMPLEMENTASI FUNGSI VALIDASI (dipindahkan dari validator.c) ===== */

/**
 * Validasi format tanggal dd-mm-YYYY
 */
int validasi_format_tanggal(const char *tanggal) {
    if (tanggal == NULL) return 0;

    int len = strlen(tanggal);

    /* Panjang harus tepat 10 karakter (dd-mm-YYYY) */
    if (len != 10) return 0;

    /* Posisi 2 dan 5 harus berisi '-' */
    if (tanggal[2] != '-' || tanggal[5] != '-') return 0;

    /* Posisi lainnya harus digit */
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;  /* Skip posisi '-' */
        if (!isdigit((unsigned char)tanggal[i])) {
            return 0;
        }
    }

    return 1;
}

/**
 * Validasi tanggal benar-benar valid (termasuk kabisat)
 */
int validasi_tanggal_sah(int d, int m, int y) {
    /* Validasi tahun */
    if (y < 1900 || y > 2100) return 0;

    /* Validasi bulan */
    if (m < 1 || m > 12) return 0;

    /* Validasi hari */
    if (d < 1) return 0;

    /* Dapatkan jumlah hari dalam bulan */
    int max_days = dapatkan_jumlah_hari_bulan(m, y);

    if (d > max_days) return 0;

    return 1;
}

/**
 * Validasi tanggal bukan 00-00-0000
 */
int validasi_bukan_nol(const char *tanggal) {
    if (tanggal == NULL) return 0;

    int d, m, y;
    if (!urai_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    /* Tanggal tidak boleh semua nol */
    if (d == 0 && m == 0 && y == 0) {
        return 0;
    }

    return 1;
}

/**
 * Validasi tanggal lengkap (format dan kevalidan)
 */
int validasi_tanggal_lengkap(const char *tanggal) {
    /* Cek format dulu */
    if (!validasi_format_tanggal(tanggal)) {
        return 0;
    }

    /* Parse komponen tanggal */
    int d, m, y;
    if (!urai_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    /* Cek bukan tanggal nol */
    if (!validasi_bukan_nol(tanggal)) {
        return 0;
    }

    /* Cek kevalidan tanggal */
    if (!validasi_tanggal_sah(d, m, y)) {
        return 0;
    }

    return 1;
}

/**
 * Validasi bulan dalam range 1-12
 */
int validasi_bulan(int bulan) {
    return (bulan >= BULAN_MIN && bulan <= BULAN_MAX);
}

/**
 * Validasi tahun (harus > 0 dan reasonable)
 */
int validasi_tahun(int tahun) {
    return (tahun >= 1900 && tahun <= 2100);
}

/**
 * Validasi bulan pada tanggal sesuai dengan bulan aktif
 */
int validasi_bulan_sesuai(const char *tanggal, int bulan_aktif) {
    if (tanggal == NULL || bulan_aktif < 1 || bulan_aktif > 12) return 0;

    int d, m, y;
    if (!urai_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    return (m == bulan_aktif);
}

/**
 * Validasi nominal harus positif (> 0)
 */
int validasi_nominal_positif(unsigned long long nominal) {
    return (nominal > 0);
}

/**
 * Parse string ke unsigned long long dengan validasi
 */
int urai_nominal(const char *str, unsigned long long *result) {
    if (str == NULL || result == NULL) return 0;

    /* Skip whitespace di awal */
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }

    /* String kosong tidak valid */
    if (*str == '\0') return 0;

    /* Cek apakah semua karakter adalah digit */
    const char *p = str;
    while (*p) {
        if (!isdigit((unsigned char)*p)) {
            return 0;  /* Karakter non-digit ditemukan */
        }
        p++;
    }

    /* Konversi dengan strtoull */
    errno = 0;
    char *endptr;
    unsigned long long value = strtoull(str, &endptr, 10);

    /* Cek error overflow */
    if (errno == ERANGE) {
        return 0;
    }

    /* Pastikan seluruh string terkonversi */
    if (*endptr != '\0') {
        return 0;
    }

    *result = value;
    return 1;
}

/**
 * Validasi pilihan menu dalam range
 */
int validasi_pilihan_menu(int pilihan, int min, int max) {
    return (pilihan >= min && pilihan <= max);
}

/**
 * Validasi string tidak kosong
 */
int validasi_tidak_kosong(const char *str) {
    if (str == NULL) return 0;

    /* Skip whitespace dan cek apakah ada karakter lain */
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 1;  /* Ditemukan karakter non-whitespace */
        }
        str++;
    }

    return 0;  /* String kosong atau hanya whitespace */
}

/**
 * Validasi string tidak mengandung karakter pipe (|)
 */
int validasi_tidak_ada_pipe(const char *str) {
    if (str == NULL) return 1;  /* NULL dianggap valid (tidak ada pipe) */

    while (*str) {
        if (*str == '|') {
            return 0;  /* Ditemukan pipe */
        }
        str++;
    }

    return 1;  /* Tidak ada pipe */
}

/**
 * Validasi string hanya mengandung karakter yang diizinkan
 * Karakter yang diizinkan: alfanumerik, spasi, dan simbol umum (.,'-/)
 */
int validasi_karakter_sah(const char *str) {
    if (str == NULL) return 0;

    while (*str) {
        char c = *str;

        /* Cek karakter yang diizinkan */
        if (!isalnum((unsigned char)c) &&
            c != ' ' && c != '.' && c != ',' &&
            c != '\'' && c != '-' && c != '/' &&
            c != '(' && c != ')') {
            return 0;  /* Karakter tidak valid */
        }
        str++;
    }

    return 1;
}
