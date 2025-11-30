/**
 * @file utils_number.c
 * @brief Implementasi fungsi utilitas format angka dan nominal
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk memformat angka ke format
 * Rupiah, persentase, dan rata-rata.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/utils/utils_number.h"

/**
 * Helper: Membalik string in-place
 */
static void reverse_string(char *str) {
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
 * Memformat angka dengan separator ribuan (tanpa prefix Rp)
 */
void format_number_separator(unsigned long long nominal, char *result) {
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
    
    reverse_string(formatted);
    strcpy(result, formatted);
}

/**
 * Memformat nominal ke format Rupiah dengan separator ribuan
 */
void format_rupiah(unsigned long long nominal, char *result) {
    if (result == NULL) return;
    
    char formatted[30];
    format_number_separator(nominal, formatted);
    
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
    format_number_separator(bagian_bulat, formatted);
    
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
        format_number_separator((unsigned long long)(-saldo), formatted);
        sprintf(result, "-Rp %s", formatted);
    } else {
        format_rupiah((unsigned long long)saldo, result);
    }
}

/**
 * Mengkonversi string angka ke unsigned long long
 */
int str_to_ull(const char *str, unsigned long long *result) {
    if (str == NULL || result == NULL) return 0;
    
    /* Skip whitespace di awal */
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
int is_numeric_string(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    
    /* Skip whitespace di awal */
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
