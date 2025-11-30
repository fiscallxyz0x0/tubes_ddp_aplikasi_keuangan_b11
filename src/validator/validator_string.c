/**
 * @file validator_string.c
 * @brief Implementasi fungsi validasi string
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk validasi panjang string,
 * string kosong, dan format string lainnya.
 */

#include <string.h>
#include <ctype.h>
#include "../../include/validator/validator_string.h"
#include "../../include/constants.h"

/**
 * Validasi panjang nama pos anggaran
 */
int validasi_panjang_pos(const char *nama) {
    if (nama == NULL) return 0;
    
    return (strlen(nama) <= MAX_POS_LENGTH);
}

/**
 * Validasi panjang deskripsi transaksi
 */
int validasi_panjang_deskripsi(const char *deskripsi) {
    if (deskripsi == NULL) return 0;
    
    return (strlen(deskripsi) <= MAX_DESKRIPSI_LENGTH);
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
 * Validasi format ID transaksi (T0001-T9999)
 */
int validasi_format_id(const char *id) {
    if (id == NULL) return 0;
    
    int len = strlen(id);
    
    /* ID harus 5 karakter (T + 4 digit) */
    if (len != 5) return 0;
    
    /* Karakter pertama harus 'T' */
    if (id[0] != 'T') return 0;
    
    /* 4 karakter berikutnya harus digit */
    for (int i = 1; i < 5; i++) {
        if (!isdigit((unsigned char)id[i])) {
            return 0;
        }
    }
    
    return 1;
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
int validasi_karakter_valid(const char *str) {
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
