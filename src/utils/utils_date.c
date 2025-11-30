/**
 * @file utils_date.c
 * @brief Implementasi fungsi utilitas parsing dan manipulasi tanggal
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk parsing, validasi, dan manipulasi
 * tanggal dalam format dd-mm-YYYY.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/utils/utils_date.h"

/* Tabel jumlah hari per bulan (non-kabisat) */
static const int days_in_month[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/**
 * Parse string tanggal ke komponen hari, bulan, tahun
 */
int parse_tanggal(const char *str, int *d, int *m, int *y) {
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
int parse_tanggal_struct(const char *str, Tanggal *tgl) {
    if (str == NULL || tgl == NULL) {
        return 0;
    }
    
    return parse_tanggal(str, &tgl->hari, &tgl->bulan, &tgl->tahun);
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
int get_current_month(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_mon + 1;  /* tm_mon dimulai dari 0 */
}

/**
 * Mendapatkan tahun saat ini dari sistem
 */
int get_current_year(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_year + 1900;  /* tm_year dihitung dari 1900 */
}

/**
 * Mendapatkan hari saat ini dari sistem
 */
int get_current_day(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local->tm_mday;
}

/**
 * Memeriksa apakah tahun adalah tahun kabisat
 */
int is_leap_year(int year) {
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
int get_days_in_month(int month, int year) {
    if (month < 1 || month > 12) return 0;
    
    if (month == 2 && is_leap_year(year)) {
        return 29;  /* Februari pada tahun kabisat */
    }
    
    return days_in_month[month];
}

/**
 * Mengekstrak bulan dari string tanggal
 */
int ekstrak_bulan(const char *tanggal) {
    int d, m, y;
    
    if (!parse_tanggal(tanggal, &d, &m, &y)) {
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
    
    if (!parse_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }
    
    return y;
}

/**
 * Mendapatkan tanggal hari ini dalam format dd-mm-YYYY
 */
void get_today_string(char *result) {
    if (result == NULL) return;
    
    format_tanggal(get_current_day(), get_current_month(), get_current_year(), result);
}
