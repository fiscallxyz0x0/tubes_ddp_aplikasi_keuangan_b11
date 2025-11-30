/**
 * @file file_pos.c
 * @brief Implementasi operasi file pos anggaran
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/file/file_pos.h"
#include "../../include/file/file_core.h"
#include "../../include/file/file_parser.h"
#include "../../include/utils/utils_string.h"
#include "../../include/constants.h"

int load_pos_bulan(PosAnggaran *list, int max_count, int bulan) {
    if (!list || max_count <= 0 || bulan < 1 || bulan > 12) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_bulan(FILE_POS_PREFIX, bulan, filename, sizeof(filename));
    
    FILE *fp = file_open_read(filename);
    if (!fp) return 0;
    
    char line[512];
    int count = 0;
    
    while (fgets(line, sizeof(line), fp) && count < max_count) {
        str_remove_newline(line);
        if (strlen(line) == 0) continue;
        
        if (parse_line_pos(line, &list[count])) {
            count++;
        }
    }
    
    fclose(fp);
    return count;
}

int save_pos_bulan(PosAnggaran *list, int count, int bulan) {
    if (!list && count > 0) return 0;
    if (bulan < 1 || bulan > 12) return 0;
    
    ensure_data_directory();
    char filename[MAX_PATH];
    get_filename_bulan(FILE_POS_PREFIX, bulan, filename, sizeof(filename));
    
    FILE *fp = file_open_write(filename);
    if (!fp) return 0;
    
    char line[512];
    for (int i = 0; i < count; i++) {
        format_pos(&list[i], line, sizeof(line));
        fprintf(fp, "%s\n", line);
    }
    
    fclose(fp);
    return 1;
}

int add_pos(PosAnggaran *pos, int bulan) {
    if (!pos || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    if (count >= MAX_POS) return 0;
    
    /* Set nomor pos */
    int max_no = 0;
    for (int i = 0; i < count; i++) {
        if (list[i].no > max_no) max_no = list[i].no;
    }
    pos->no = max_no + 1;
    
    /* Inisialisasi nilai default */
    pos->realisasi = 0;
    pos->sisa = pos->nominal;
    pos->jumlah_transaksi = 0;
    pos->status = STATUS_AMAN;
    
    list[count] = *pos;
    count++;
    
    return save_pos_bulan(list, count, bulan);
}

int update_pos(int no, PosAnggaran *pos, int bulan) {
    if (!pos || no <= 0 || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            /* Pertahankan nomor asli */
            pos->no = no;
            list[i] = *pos;
            return save_pos_bulan(list, count, bulan);
        }
    }
    
    return 0;
}

int delete_pos(int no, int bulan) {
    if (no <= 0 || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            found = i;
            break;
        }
    }
    
    if (found < 0) return 0;
    
    /* Shift array */
    for (int i = found; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    
    return save_pos_bulan(list, count - 1, bulan);
}

int find_pos_by_nama(const char *nama, int bulan, PosAnggaran *result) {
    if (!nama || !result || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    for (int i = 0; i < count; i++) {
        if (str_compare_nocase(list[i].nama, nama) == 0) {
            *result = list[i];
            return 1;
        }
    }
    
    return 0;
}

int find_pos_by_no(int no, int bulan, PosAnggaran *result) {
    if (no <= 0 || !result || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            *result = list[i];
            return 1;
        }
    }
    
    return 0;
}

int pos_file_exists(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    char filename[MAX_PATH];
    get_filename_bulan(FILE_POS_PREFIX, bulan, filename, sizeof(filename));
    
    return file_exists(filename);
}

int init_pos_bulan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    /* Cek apakah sudah ada */
    if (pos_file_exists(bulan)) return 1;
    
    /* Buat file kosong */
    return save_pos_bulan(NULL, 0, bulan);
}

int copy_pos_from_bulan(int bulan_tujuan, int bulan_sumber) {
    if (bulan_tujuan < 1 || bulan_tujuan > 12) return 0;
    if (bulan_sumber < 1 || bulan_sumber > 12) return 0;
    if (bulan_tujuan == bulan_sumber) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan_sumber);
    
    if (count == 0) return 0;
    
    /* Reset realisasi dan sisa untuk bulan baru */
    for (int i = 0; i < count; i++) {
        list[i].realisasi = 0;
        list[i].sisa = list[i].nominal;
        list[i].jumlah_transaksi = 0;
        list[i].status = STATUS_AMAN;
    }
    
    return save_pos_bulan(list, count, bulan_tujuan);
}
