/**
 * @file utils_bulan.c
 * @brief Implementasi fungsi utilitas konversi nama bulan
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk konversi antara nomor bulan
 * dan nama bulan dalam Bahasa Indonesia.
 */

#include <string.h>
#include <ctype.h>
#include "../../include/utils/utils_bulan.h"
#include "../../include/constants.h"

/* Array nama bulan dalam Bahasa Indonesia */
static const char *nama_bulan[] = {
    "Invalid",
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

/**
 * Mendapatkan nama bulan dalam Bahasa Indonesia
 */
const char* get_nama_bulan(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return nama_bulan[0];  /* "Invalid" */
    }
    return nama_bulan[bulan];
}

/**
 * Mendapatkan kode bulan 2 digit
 */
const char* get_kode_bulan(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return kode_bulan[0];  /* "00" */
    }
    return kode_bulan[bulan];
}

/**
 * Mendapatkan nama bulan singkat (3 huruf)
 */
const char* get_nama_bulan_singkat(int bulan) {
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        return nama_bulan_singkat[0];  /* "Inv" */
    }
    return nama_bulan_singkat[bulan];
}

/**
 * Helper: Membandingkan string case-insensitive
 */
static int str_cmp_nocase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/**
 * Mengkonversi nama bulan ke nomor bulan
 */
int nama_ke_nomor_bulan(const char *nama) {
    if (nama == NULL) return 0;
    
    for (int i = 1; i <= 12; i++) {
        if (str_cmp_nocase(nama, nama_bulan[i]) == 0) {
            return i;
        }
        /* Cek juga nama singkat */
        if (str_cmp_nocase(nama, nama_bulan_singkat[i]) == 0) {
            return i;
        }
    }
    
    return 0;  /* Tidak ditemukan */
}

/**
 * Validasi nomor bulan
 */
int is_valid_bulan(int bulan) {
    return (bulan >= BULAN_MIN && bulan <= BULAN_MAX);
}
