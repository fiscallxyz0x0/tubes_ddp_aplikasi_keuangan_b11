/**
 * @file validator_number.c
 * @brief Implementasi fungsi validasi angka
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk validasi nominal positif,
 * nomor pos, dan parsing angka.
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "../../include/validator/validator_number.h"
#include "../../include/constants.h"

/**
 * Validasi nominal harus positif (> 0)
 */
int validasi_nominal_positif(unsigned long long nominal) {
    return (nominal > 0);
}

/**
 * Validasi nomor pos dalam range yang valid
 */
int validasi_no_pos(int no, int max) {
    return (no >= 1 && no <= max);
}

/**
 * Parse string ke unsigned long long dengan validasi
 */
int parse_nominal(const char *str, unsigned long long *result) {
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
 * Validasi jenis transaksi (0 atau 1)
 */
int validasi_jenis_transaksi(int jenis) {
    return (jenis == JENIS_PENGELUARAN || jenis == JENIS_PEMASUKAN);
}
