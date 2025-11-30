/**
 * @file utils_string.c
 * @brief Implementasi fungsi utilitas manipulasi string
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi pembantu untuk operasi string
 * seperti trim, uppercase, dan safe copy.
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../include/utils/utils_string.h"

/**
 * Menghapus whitespace di awal dan akhir string
 */
void str_trim(char *str) {
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
void str_to_upper(char *str) {
    if (str == NULL) return;
    
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

/**
 * Mengkonversi string ke lowercase
 */
void str_to_lower(char *str) {
    if (str == NULL) return;
    
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

/**
 * Menyalin string dengan batasan ukuran (safe copy)
 */
void str_copy_safe(char *dst, const char *src, int max) {
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
int str_split(char *str, char delim, char **result, int max_parts) {
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
int str_is_empty(const char *str) {
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
int str_compare_nocase(const char *s1, const char *s2) {
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
void str_remove_newline(char *str) {
    if (str == NULL) return;
    
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}
