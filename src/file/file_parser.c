/**
 * @file file_parser.c
 * @brief Implementasi fungsi parsing format pipe-delimited
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk parsing baris file ke struct
 * dan memformat struct ke string pipe-delimited.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/file/file_parser.h"
#include "../../include/utils/utils_string.h"
#include "../../include/constants.h"

/**
 * Helper: Safe string to int conversion
 */
static int safe_atoi(const char *str) {
    if (str == NULL) return 0;
    return atoi(str);
}

/**
 * Helper: Safe string to unsigned long long conversion
 */
static unsigned long long safe_atoull(const char *str) {
    if (str == NULL) return 0;
    return strtoull(str, NULL, 10);
}

/**
 * Helper: Safe string to double conversion
 */
static double safe_atof(const char *str) {
    if (str == NULL) return 0.0;
    return atof(str);
}

/**
 * Helper: Safe string to long long conversion
 */
static long long safe_atoll(const char *str) {
    if (str == NULL) return 0;
    return strtoll(str, NULL, 10);
}

/**
 * Mendapatkan label jenis transaksi
 */
const char* get_label_jenis(int jenis) {
    if (jenis == JENIS_PEMASUKAN) {
        return "Pemasukan";
    }
    return "Pengeluaran";
}

/**
 * Konversi string jenis ke kode
 */
int parse_jenis_transaksi(const char *jenis_str) {
    if (jenis_str == NULL) return -1;
    
    /* Case-insensitive comparison */
    if (str_compare_nocase(jenis_str, "Pemasukan") == 0) {
        return JENIS_PEMASUKAN;
    }
    if (str_compare_nocase(jenis_str, "Pengeluaran") == 0) {
        return JENIS_PENGELUARAN;
    }
    
    return -1;  /* Invalid */
}

/**
 * Parse baris teks ke struct Transaksi
 * Format: id|tanggal|jenis|pos|nominal|deskripsi
 */
int parse_line_transaksi(const char *line, Transaksi *trx) {
    if (line == NULL || trx == NULL) return 0;
    
    /* Buat salinan line karena strtok memodifikasi string */
    char buffer[MAX_LINE_LENGTH];
    str_copy_safe(buffer, line, MAX_LINE_LENGTH);
    str_remove_newline(buffer);
    
    /* Parse field dengan delimiter | */
    char *token;
    int field = 0;
    
    token = strtok(buffer, "|");
    while (token != NULL && field < 6) {
        str_trim(token);
        
        switch (field) {
            case 0:  /* id */
                str_copy_safe(trx->id, token, sizeof(trx->id));
                break;
            case 1:  /* tanggal */
                str_copy_safe(trx->tanggal, token, sizeof(trx->tanggal));
                break;
            case 2:  /* jenis */
                trx->jenis = parse_jenis_transaksi(token);
                break;
            case 3:  /* pos */
                str_copy_safe(trx->pos, token, sizeof(trx->pos));
                break;
            case 4:  /* nominal */
                trx->nominal = safe_atoull(token);
                break;
            case 5:  /* deskripsi */
                str_copy_safe(trx->deskripsi, token, sizeof(trx->deskripsi));
                break;
        }
        
        field++;
        token = strtok(NULL, "|");
    }
    
    /* Minimal harus ada 5 field (deskripsi bisa kosong) */
    return (field >= 5);
}

/**
 * Parse baris teks ke struct PosAnggaran
 * Format: no|nama|nominal|realisasi|sisa|jumlah_trx|status
 */
int parse_line_pos(const char *line, PosAnggaran *pos) {
    if (line == NULL || pos == NULL) return 0;
    
    char buffer[MAX_LINE_LENGTH];
    str_copy_safe(buffer, line, MAX_LINE_LENGTH);
    str_remove_newline(buffer);
    
    char *token;
    int field = 0;
    
    token = strtok(buffer, "|");
    while (token != NULL && field < 7) {
        str_trim(token);
        
        switch (field) {
            case 0:  /* no */
                pos->no = safe_atoi(token);
                break;
            case 1:  /* nama */
                str_copy_safe(pos->nama, token, sizeof(pos->nama));
                break;
            case 2:  /* nominal */
                pos->nominal = safe_atoull(token);
                break;
            case 3:  /* realisasi */
                pos->realisasi = safe_atoull(token);
                break;
            case 4:  /* sisa */
                pos->sisa = safe_atoll(token);
                break;
            case 5:  /* jumlah_transaksi */
                pos->jumlah_transaksi = safe_atoi(token);
                break;
            case 6:  /* status */
                pos->status = safe_atoi(token);
                break;
        }
        
        field++;
        token = strtok(NULL, "|");
    }
    
    return (field >= 7);
}

/**
 * Parse baris teks ke struct AnalisisKeuangan
 * Format: pemasukan|pengeluaran|rata|persen|saldo|kondisi|kesimpulan|trx_out|trx_in
 */
int parse_line_analisis(const char *line, AnalisisKeuangan *data) {
    if (line == NULL || data == NULL) return 0;
    
    char buffer[MAX_LINE_LENGTH];
    str_copy_safe(buffer, line, MAX_LINE_LENGTH);
    str_remove_newline(buffer);
    
    char *token;
    int field = 0;
    
    token = strtok(buffer, "|");
    while (token != NULL && field < 9) {
        str_trim(token);
        
        switch (field) {
            case 0:  /* total_pemasukan */
                data->total_pemasukan = safe_atoull(token);
                break;
            case 1:  /* total_pengeluaran */
                data->total_pengeluaran = safe_atoull(token);
                break;
            case 2:  /* rata_rata_pengeluaran */
                data->rata_rata_pengeluaran = safe_atof(token);
                break;
            case 3:  /* persentase_sisa */
                data->persentase_sisa = safe_atof(token);
                break;
            case 4:  /* saldo_akhir */
                data->saldo_akhir = safe_atoll(token);
                break;
            case 5:  /* kondisi_keuangan */
                data->kondisi_keuangan = safe_atoi(token);
                break;
            case 6:  /* kesimpulan */
                data->kesimpulan = safe_atoi(token);
                break;
            case 7:  /* total_trx_pengeluaran */
                data->total_trx_pengeluaran = safe_atoi(token);
                break;
            case 8:  /* total_trx_pemasukan */
                data->total_trx_pemasukan = safe_atoi(token);
                break;
        }
        
        field++;
        token = strtok(NULL, "|");
    }
    
    return (field >= 9);
}

/**
 * Format struct Transaksi ke string pipe-delimited
 */
void format_transaksi(const Transaksi *trx, char *result, int result_size) {
    if (trx == NULL || result == NULL || result_size <= 0) return;
    
    snprintf(result, result_size, "%s|%s|%s|%s|%llu|%s",
            trx->id,
            trx->tanggal,
            get_label_jenis(trx->jenis),
            trx->pos,
            trx->nominal,
            trx->deskripsi);
}

/**
 * Format struct PosAnggaran ke string pipe-delimited
 */
void format_pos(const PosAnggaran *pos, char *result, int result_size) {
    if (pos == NULL || result == NULL || result_size <= 0) return;
    
    snprintf(result, result_size, "%d|%s|%llu|%llu|%lld|%d|%d",
            pos->no,
            pos->nama,
            pos->nominal,
            pos->realisasi,
            pos->sisa,
            pos->jumlah_transaksi,
            pos->status);
}

/**
 * Format struct AnalisisKeuangan ke string pipe-delimited
 */
void format_analisis(const AnalisisKeuangan *data, char *result, int result_size) {
    if (data == NULL || result == NULL || result_size <= 0) return;
    
    snprintf(result, result_size, "%llu|%llu|%.2f|%.2f|%lld|%d|%d|%d|%d",
            data->total_pemasukan,
            data->total_pengeluaran,
            data->rata_rata_pengeluaran,
            data->persentase_sisa,
            data->saldo_akhir,
            data->kondisi_keuangan,
            data->kesimpulan,
            data->total_trx_pengeluaran,
            data->total_trx_pemasukan);
}
