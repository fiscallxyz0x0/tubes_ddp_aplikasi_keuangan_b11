/**
 * @file pos_calc.c
 * @brief Implementasi fungsi kalkulasi pos anggaran
 */

#include <string.h>
#include "../../include/pos/pos_calc.h"
#include "../../include/file/file_transaksi.h"
#include "../../include/file/file_pos.h"
#include "../../include/utils/utils_string.h"
#include "../../include/utils/utils_date.h"
#include "../../include/constants.h"

unsigned long long hitung_realisasi_pos(const char *nama_pos, int bulan) {
    if (!nama_pos || bulan < 1 || bulan > 12) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi_bulan(list, MAX_TRANSAKSI, bulan);
    
    unsigned long long total = 0;
    for (int i = 0; i < count; i++) {
        /* Hanya hitung pengeluaran untuk pos yang sesuai */
        if (list[i].jenis == JENIS_PENGELUARAN &&
            str_compare_nocase(list[i].pos, nama_pos) == 0) {
            total += list[i].nominal;
        }
    }
    
    return total;
}

long long hitung_sisa_pos(unsigned long long nominal, unsigned long long realisasi) {
    return (long long)nominal - (long long)realisasi;
}

int tentukan_status_pos(long long sisa) {
    return (sisa >= 0) ? STATUS_AMAN : STATUS_TIDAK_AMAN;
}

void update_kalkulasi_pos(PosAnggaran *pos, int bulan) {
    if (!pos || bulan < 1 || bulan > 12) return;
    
    /* Hitung realisasi dari transaksi */
    pos->realisasi = hitung_realisasi_pos(pos->nama, bulan);
    
    /* Hitung sisa */
    pos->sisa = hitung_sisa_pos(pos->nominal, pos->realisasi);
    
    /* Tentukan status */
    pos->status = tentukan_status_pos(pos->sisa);
    
    /* Hitung jumlah transaksi */
    pos->jumlah_transaksi = hitung_jumlah_transaksi_pos(pos->nama, bulan);
}

int update_semua_pos_bulan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    if (count == 0) return 1;  /* Tidak ada pos, sukses */
    
    /* Update kalkulasi untuk setiap pos */
    for (int i = 0; i < count; i++) {
        update_kalkulasi_pos(&list[i], bulan);
    }
    
    /* Simpan kembali */
    return save_pos_bulan(list, count, bulan);
}

int hitung_jumlah_transaksi_pos(const char *nama_pos, int bulan) {
    if (!nama_pos || bulan < 1 || bulan > 12) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi_bulan(list, MAX_TRANSAKSI, bulan);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (str_compare_nocase(list[i].pos, nama_pos) == 0) {
            total++;
        }
    }
    
    return total;
}

unsigned long long hitung_total_anggaran(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    unsigned long long total = 0;
    for (int i = 0; i < count; i++) {
        total += list[i].nominal;
    }
    
    return total;
}

unsigned long long hitung_total_realisasi(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    /* Update kalkulasi dulu */
    for (int i = 0; i < count; i++) {
        update_kalkulasi_pos(&list[i], bulan);
    }
    
    unsigned long long total = 0;
    for (int i = 0; i < count; i++) {
        total += list[i].realisasi;
    }
    
    return total;
}
