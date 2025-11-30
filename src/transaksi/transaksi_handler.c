/**
 * @file transaksi_handler.c
 * @brief Implementasi handler utama modul transaksi
 */

#include "../../include/transaksi/transaksi_handler.h"
#include "../../include/transaksi/transaksi_menu.h"
#include "../../include/pos/pos_handler.h"
#include "../../include/pos/pos_menu.h"
#include "../../include/constants.h"

#define ACT_VIEW    1
#define ACT_TAMBAH  2
#define ACT_EDIT    3
#define ACT_HAPUS   4
#define ACT_KEMBALI 0

void run_transaksi_module(int bulan_awal) {
    int bulan = bulan_awal;
    
    /* Pastikan pos anggaran ada untuk bulan ini */
    init_pos_for_bulan(bulan);
    
    while (1) {
        int action = menu_transaksi_utama(bulan);
        
        switch (action) {
            case ACT_VIEW:
                handler_view_transaksi(bulan);
                break;
                
            case ACT_TAMBAH:
                handler_tambah_transaksi(bulan);
                break;
                
            case ACT_EDIT:
                handler_edit_transaksi(bulan);
                break;
                
            case ACT_HAPUS:
                handler_hapus_transaksi(bulan);
                break;
                
            case ACT_KEMBALI:
            case CANCEL:
                return;
        }
    }
}
