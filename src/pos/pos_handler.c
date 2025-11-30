/**
 * @file pos_handler.c
 * @brief Implementasi handler utama pos anggaran
 */

#include <stdio.h>
#include "../../include/pos/pos_handler.h"
#include "../../include/pos/pos_menu.h"
#include "../../include/pos/pos_crud.h"
#include "../../include/pos/pos_calc.h"
#include "../../include/file/file_pos.h"
#include "../../include/tui/tui_message.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/constants.h"

/* Menu actions (sama dengan pos_menu.c) */
#define ACT_VIEW    1
#define ACT_TAMBAH  2
#define ACT_EDIT    3
#define ACT_HAPUS   4
#define ACT_BULAN   5
#define ACT_KEMBALI 0

void run_pos_module(int bulan_awal) {
    int bulan = bulan_awal;

    /* Inisialisasi pos untuk bulan jika belum ada */
    init_pos_for_bulan(bulan);

    while (1) {
        /* Sinkronisasi kalkulasi */
        sync_pos_transaksi(bulan);

        int action = menu_pos_utama(bulan);

        switch (action) {
            case ACT_VIEW:
                handler_view_pos(bulan);
                break;

            case ACT_TAMBAH:
                handler_tambah_pos(bulan);
                break;

            case ACT_EDIT:
                handler_edit_pos(bulan);
                break;

            case ACT_HAPUS:
                handler_hapus_pos(bulan);
                break;

            /* REV-6: Removed ACT_BULAN case - Ganti Bulan moved to main menu only */

            case ACT_KEMBALI:
            case CANCEL:
                return;
        }
    }
}

int init_pos_for_bulan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    /* Cek apakah sudah ada file */
    if (pos_file_exists(bulan)) {
        return 1;  /* Sudah ada */
    }
    
    /* Cek bulan sebelumnya */
    int bulan_sebelum = (bulan == 1) ? 12 : bulan - 1;
    
    if (pos_file_exists(bulan_sebelum)) {
        /* Tanyakan apakah mau copy dari bulan sebelumnya */
        char msg[100];
        snprintf(msg, sizeof(msg), 
                 "Copy pos dari %s ke %s?",
                 get_nama_bulan(bulan_sebelum),
                 get_nama_bulan(bulan));
        
        if (show_confirm(msg)) {
            if (copy_pos_from_bulan(bulan, bulan_sebelum)) {
                show_success("Pos berhasil dicopy");
                return 1;
            } else {
                show_error("Gagal copy pos");
            }
        }
    }
    
    /* Buat file pos kosong */
    return init_pos_bulan(bulan);
}

int sync_pos_transaksi(int bulan) {
    return update_semua_pos_bulan(bulan);
}
