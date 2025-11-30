/**
 * @file pos_menu.c
 * @brief Implementasi menu pos anggaran
 */

#include <stdio.h>
#include <string.h>
#include "../../include/pos/pos_menu.h"
#include "../../include/pos/pos_display.h"
#include "../../include/pos/pos_crud.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_menu.h"
#include "../../include/tui/tui_message.h"
#include "../../include/tui/tui_input.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/constants.h"

/* Menu actions */
#define ACT_VIEW    1
#define ACT_TAMBAH  2
#define ACT_EDIT    3
#define ACT_HAPUS   4
#define ACT_BULAN   5
#define ACT_KEMBALI 0

int menu_pos_utama(int bulan) {
    char title[64];
    snprintf(title, sizeof(title), "Menu Pos Anggaran - %s", get_nama_bulan(bulan));

    Menu menu;
    menu_init(&menu, title);

    menu_add_item(&menu, "Lihat Daftar Pos", ACT_VIEW);
    menu_add_item(&menu, "Tambah Pos Baru", ACT_TAMBAH);
    menu_add_item(&menu, "Edit Pos", ACT_EDIT);
    menu_add_item(&menu, "Hapus Pos", ACT_HAPUS);
    /* REV-2 & REV-6: Removed "Ganti Bulan" and "Kembali" - use ESC to go back */

    return menu_navigate(&menu);
}

int menu_pilih_bulan(int bulan_saat_ini) {
    Menu menu;
    menu_init(&menu, "Pilih Bulan");
    
    for (int i = 1; i <= 12; i++) {
        char item[32];
        if (i == bulan_saat_ini) {
            snprintf(item, sizeof(item), "%s (aktif)", get_nama_bulan(i));
        } else {
            snprintf(item, sizeof(item), "%s", get_nama_bulan(i));
        }
        menu_add_item(&menu, item, i);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL) {
        return bulan_saat_ini;  /* Tetap di bulan sekarang */
    }
    
    return pilihan;
}

void handler_view_pos(int bulan) {
    int selected = 0;
    PosAnggaran list[MAX_POS];
    int count = pos_get_list(list, MAX_POS, bulan);
    
    while (1) {
        tui_clear();
        display_header("DAFTAR POS ANGGARAN");
        
        int next_y = tampilkan_daftar_pos(bulan, selected);
        next_y = tampilkan_ringkasan_pos(bulan, next_y);
        
        display_footer("UP/DOWN: Navigasi | ENTER: Detail | ESC: Kembali");
        tui_refresh();
        
        int ch = tui_getch();
        
        switch (ch) {
            case KEY_UP:
            case 'k':
                if (selected > 0) selected--;
                break;
                
            case KEY_DOWN:
            case 'j':
                if (selected < count - 1) selected++;
                break;
                
            case KEY_ENTER:
            case '\n':
            case '\r':
                if (count > 0) {
                    tui_clear();
                    display_header("DETAIL POS ANGGARAN");
                    tampilkan_detail_pos(&list[selected], 5);
                    display_footer("Tekan sembarang tombol untuk kembali");
                    tui_refresh();
                    tui_getch();
                    
                    /* Reload list */
                    count = pos_get_list(list, MAX_POS, bulan);
                    if (selected >= count) selected = count - 1;
                    if (selected < 0) selected = 0;
                }
                break;
                
            case 27:  /* ESC */
                return;
        }
    }
}

void handler_tambah_pos(int bulan) {
    tampilkan_form_tambah_pos(bulan);
}

void handler_edit_pos(int bulan) {
    PosAnggaran list[MAX_POS];
    int count = pos_get_list(list, MAX_POS, bulan);
    
    if (count == 0) {
        show_warning("Belum ada pos anggaran");
        return;
    }
    
    /* Pilih pos untuk diedit */
    Menu menu;
    menu_init(&menu, "Pilih Pos untuk Diedit");
    
    for (int i = 0; i < count; i++) {
        char item[64];
        snprintf(item, sizeof(item), "%d. %s", list[i].no, list[i].nama);
        menu_add_item(&menu, item, list[i].no);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL || pilihan <= 0) {
        return;
    }
    
    tampilkan_form_edit_pos(pilihan, bulan);
}

void handler_hapus_pos(int bulan) {
    PosAnggaran list[MAX_POS];
    int count = pos_get_list(list, MAX_POS, bulan);
    
    if (count == 0) {
        show_warning("Belum ada pos anggaran");
        return;
    }
    
    /* Pilih pos untuk dihapus */
    Menu menu;
    menu_init(&menu, "Pilih Pos untuk Dihapus");
    
    for (int i = 0; i < count; i++) {
        char item[64];
        if (list[i].jumlah_transaksi > 0) {
            snprintf(item, sizeof(item), "%d. %s (ada %d transaksi)", 
                     list[i].no, list[i].nama, list[i].jumlah_transaksi);
        } else {
            snprintf(item, sizeof(item), "%d. %s", list[i].no, list[i].nama);
        }
        menu_add_item(&menu, item, list[i].no);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL || pilihan <= 0) {
        return;
    }
    
    tampilkan_konfirmasi_hapus_pos(pilihan, bulan);
}
