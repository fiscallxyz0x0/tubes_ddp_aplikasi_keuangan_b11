/**
 * @file file_transaksi.c
 * @brief Implementasi operasi file transaksi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/file/file_transaksi.h"
#include "../../include/file/file_core.h"
#include "../../include/file/file_parser.h"
#include "../../include/utils/utils_string.h"
#include "../../include/utils/utils_date.h"
#include "../../include/constants.h"

int load_transaksi(Transaksi *list, int max_count) {
    if (!list || max_count <= 0) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_transaksi(filename, sizeof(filename));
    
    FILE *fp = file_open_read(filename);
    if (!fp) return 0;
    
    char line[512];
    int count = 0;
    
    while (fgets(line, sizeof(line), fp) && count < max_count) {
        str_remove_newline(line);
        if (strlen(line) == 0) continue;
        
        if (parse_line_transaksi(line, &list[count])) {
            count++;
        }
    }
    
    fclose(fp);
    return count;
}

int load_transaksi_bulan(Transaksi *list, int max_count, int bulan) {
    if (!list || max_count <= 0 || bulan < 1 || bulan > 12) return 0;
    
    Transaksi all[MAX_TRANSAKSI];
    int total = load_transaksi(all, MAX_TRANSAKSI);
    
    int count = 0;
    for (int i = 0; i < total && count < max_count; i++) {
        Tanggal tgl;
        if (parse_tanggal_struct(all[i].tanggal, &tgl) && tgl.bulan == bulan) {
            list[count++] = all[i];
        }
    }
    
    return count;
}

int save_transaksi(Transaksi *list, int count) {
    if (!list && count > 0) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_transaksi(filename, sizeof(filename));
    
    FILE *fp = file_open_write(filename);
    if (!fp) return 0;
    
    char line[512];
    for (int i = 0; i < count; i++) {
        format_transaksi(&list[i], line, sizeof(line));
        fprintf(fp, "%s\n", line);
    }
    
    fclose(fp);
    return 1;
}

int add_transaksi(Transaksi *trx) {
    if (!trx) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    if (count >= MAX_TRANSAKSI) return 0;
    
    list[count] = *trx;
    count++;
    
    return save_transaksi(list, count);
}

int update_transaksi(const char *id, Transaksi *trx) {
    if (!id || !trx) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            list[i] = *trx;
            return save_transaksi(list, count);
        }
    }
    
    return 0;
}

int delete_transaksi(const char *id) {
    if (!id) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found < 0) return 0;
    
    /* Shift array */
    for (int i = found; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    
    return save_transaksi(list, count - 1);
}

int find_transaksi_by_id(const char *id, Transaksi *result) {
    if (!id || !result) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            *result = list[i];
            return 1;
        }
    }
    
    return 0;
}

void generate_transaksi_id(char *buffer) {
    if (!buffer) return;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    int max_num = 0;
    for (int i = 0; i < count; i++) {
        if (list[i].id[0] == 'T' && strlen(list[i].id) == 5) {
            int num = atoi(list[i].id + 1);
            if (num > max_num) max_num = num;
        }
    }
    
    sprintf(buffer, "T%04d", max_num + 1);
}

int count_transaksi_by_pos(const char *nama_pos) {
    if (!nama_pos) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi(list, MAX_TRANSAKSI);
    
    int hasil = 0;
    for (int i = 0; i < count; i++) {
        if (str_compare_nocase(list[i].pos, nama_pos) == 0) {
            hasil++;
        }
    }
    
    return hasil;
}
