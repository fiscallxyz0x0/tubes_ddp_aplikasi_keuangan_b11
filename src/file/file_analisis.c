/**
 * @file file_analisis.c
 * @brief Implementasi operasi file analisis keuangan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/file/file_analisis.h"
#include "../../include/file/file_core.h"
#include "../../include/file/file_parser.h"
#include "../../include/utils/utils_string.h"
#include "../../include/constants.h"

int load_analisis_bulan(int bulan, AnalisisKeuangan *result) {
    if (!result || bulan < 1 || bulan > 12) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_bulan(FILE_ANALISIS_PREFIX, bulan, filename, sizeof(filename));
    
    FILE *fp = file_open_read(filename);
    if (!fp) return 0;
    
    char line[512];
    int success = 0;
    
    if (fgets(line, sizeof(line), fp)) {
        str_remove_newline(line);
        if (strlen(line) > 0) {
            success = parse_line_analisis(line, result);
        }
    }
    
    fclose(fp);
    return success;
}

int save_analisis_bulan(int bulan, AnalisisKeuangan *analisis) {
    if (!analisis || bulan < 1 || bulan > 12) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_bulan(FILE_ANALISIS_PREFIX, bulan, filename, sizeof(filename));
    
    FILE *fp = file_open_write(filename);
    if (!fp) return 0;
    
    char line[512];
    format_analisis(analisis, line, sizeof(line));
    fprintf(fp, "%s\n", line);
    
    fclose(fp);
    return 1;
}

int analisis_file_exists(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    char filename[MAX_PATH];
    get_filename_bulan(FILE_ANALISIS_PREFIX, bulan, filename, sizeof(filename));
    
    return file_exists(filename);
}

int init_analisis_bulan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    /* Cek apakah sudah ada */
    if (analisis_file_exists(bulan)) return 1;
    
    /* Buat analisis kosong */
    AnalisisKeuangan analisis;
    memset(&analisis, 0, sizeof(AnalisisKeuangan));
    analisis.kondisi_keuangan = KONDISI_SEIMBANG;
    analisis.kesimpulan = KESIMPULAN_SEIMBANG;
    
    return save_analisis_bulan(bulan, &analisis);
}
