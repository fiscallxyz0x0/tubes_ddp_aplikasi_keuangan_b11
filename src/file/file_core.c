/**
 * @file file_core.c
 * @brief Implementasi fungsi operasi file dasar
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi dasar untuk operasi file seperti
 * cek keberadaan file, buat file, buka file, dan generate nama file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "../../include/file/file_core.h"
#include "../../include/constants.h"
#include "../../include/utils/utils_bulan.h"

/**
 * Cek apakah file ada
 */
int file_exists(const char *filename) {
    if (filename == NULL) return 0;
    
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        fclose(f);
        return 1;
    }
    return 0;
}

/**
 * Buat file baru (kosong)
 */
int file_create(const char *filename) {
    if (filename == NULL) return 0;
    
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return 0;
    }
    fclose(f);
    return 1;
}

/**
 * Buka file untuk dibaca
 */
FILE* file_open_read(const char *filename) {
    if (filename == NULL) return NULL;
    
    return fopen(filename, "r");
}

/**
 * Buka file untuk ditulis (overwrite)
 */
FILE* file_open_write(const char *filename) {
    if (filename == NULL) return NULL;
    
    return fopen(filename, "w");
}

/**
 * Buka file untuk append
 */
FILE* file_open_append(const char *filename) {
    if (filename == NULL) return NULL;
    
    return fopen(filename, "a");
}

/**
 * Generate nama file dengan suffix bulan
 */
void get_filename_bulan(const char *base, int bulan, char *result, int result_size) {
    if (base == NULL || result == NULL || result_size <= 0) return;
    
    /* Validasi bulan */
    if (bulan < BULAN_MIN || bulan > BULAN_MAX) {
        bulan = 1;  /* Default ke Januari jika invalid */
    }
    
    /* Format: data/base_MM.txt */
    snprintf(result, result_size, "%s%s_%s%s", DATA_DIR, base, get_kode_bulan(bulan), FILE_EXTENSION);
}

/**
 * Generate nama file transaksi
 */
void get_filename_transaksi(char *result, int result_size) {
    if (result == NULL || result_size <= 0) return;
    
    snprintf(result, result_size, "%s%s%s", DATA_DIR, FILE_TRANSAKSI, FILE_EXTENSION);
}

/**
 * Memastikan direktori data ada
 */
int ensure_data_directory(void) {
    struct stat st = {0};
    
    /* Cek apakah direktori sudah ada */
    if (stat(DATA_DIR, &st) == -1) {
        /* Buat direktori dengan permission 0755 */
        #ifdef _WIN32
        if (mkdir(DATA_DIR) == -1) {
        #else
        if (mkdir(DATA_DIR, 0755) == -1) {
        #endif
            return 0;  /* Gagal membuat direktori */
        }
    }
    
    return 1;
}

/**
 * Membaca seluruh isi file ke buffer
 */
int file_read_all(const char *filename, char *buffer, int buffer_size) {
    if (filename == NULL || buffer == NULL || buffer_size <= 0) {
        return 0;
    }
    
    FILE *f = file_open_read(filename);
    if (f == NULL) {
        buffer[0] = '\0';
        return 0;
    }
    
    int total = fread(buffer, 1, buffer_size - 1, f);
    buffer[total] = '\0';
    
    fclose(f);
    return total;
}

/**
 * Menulis string ke file (overwrite)
 */
int file_write_all(const char *filename, const char *content) {
    if (filename == NULL) return 0;
    
    FILE *f = file_open_write(filename);
    if (f == NULL) {
        return 0;
    }
    
    if (content != NULL) {
        fputs(content, f);
    }
    
    fclose(f);
    return 1;
}

/**
 * Menambahkan baris ke akhir file
 */
int file_append_line(const char *filename, const char *line) {
    if (filename == NULL || line == NULL) return 0;
    
    /* Jika file belum ada, buat dulu */
    if (!file_exists(filename)) {
        if (!file_create(filename)) {
            return 0;
        }
    }
    
    FILE *f = file_open_append(filename);
    if (f == NULL) {
        return 0;
    }
    
    fprintf(f, "%s\n", line);
    fclose(f);
    
    return 1;
}
