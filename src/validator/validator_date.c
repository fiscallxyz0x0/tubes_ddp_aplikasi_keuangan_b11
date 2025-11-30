/**
 * @file validator_date.c
 * @brief Implementasi fungsi validasi tanggal
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk validasi format tanggal,
 * tanggal valid, dan ekstraksi bulan.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../include/validator/validator_date.h"
#include "../../include/utils/utils_date.h"
#include "../../include/constants.h"

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
int validasi_tanggal_valid(int d, int m, int y) {
    /* Validasi tahun */
    if (y < 1900 || y > 2100) return 0;
    
    /* Validasi bulan */
    if (m < 1 || m > 12) return 0;
    
    /* Validasi hari */
    if (d < 1) return 0;
    
    /* Dapatkan jumlah hari dalam bulan */
    int max_days = get_days_in_month(m, y);
    
    if (d > max_days) return 0;
    
    return 1;
}

/**
 * Validasi tanggal bukan 00-00-0000
 */
int validasi_bukan_nol(const char *tanggal) {
    if (tanggal == NULL) return 0;
    
    int d, m, y;
    if (!parse_tanggal(tanggal, &d, &m, &y)) {
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
    if (!parse_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }
    
    /* Cek bukan tanggal nol */
    if (!validasi_bukan_nol(tanggal)) {
        return 0;
    }
    
    /* Cek kevalidan tanggal */
    if (!validasi_tanggal_valid(d, m, y)) {
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
 * REV-3: Validasi bulan pada tanggal sesuai dengan bulan aktif
 * @param tanggal String tanggal format dd-mm-YYYY
 * @param bulan_aktif Bulan yang sedang dipilih (1-12)
 * @return 1 jika bulan sesuai, 0 jika tidak sesuai
 */
int validasi_bulan_sesuai(const char *tanggal, int bulan_aktif) {
    if (tanggal == NULL || bulan_aktif < 1 || bulan_aktif > 12) return 0;

    int d, m, y;
    if (!parse_tanggal(tanggal, &d, &m, &y)) {
        return 0;
    }

    return (m == bulan_aktif);
}
