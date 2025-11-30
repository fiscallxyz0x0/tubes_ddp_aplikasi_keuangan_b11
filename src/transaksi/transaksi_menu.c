/**
 * @file transaksi_menu.c
 * @brief Implementasi menu transaksi
 */

#include <stdio.h>
#include <string.h>
#include "../../include/transaksi/transaksi_menu.h"
#include "../../include/transaksi/transaksi_display.h"
#include "../../include/transaksi/transaksi_crud.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_menu.h"
#include "../../include/tui/tui_message.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/utils/utils_number.h"
#include "../../include/constants.h"

#define ACT_VIEW    1
#define ACT_TAMBAH  2
#define ACT_EDIT    3
#define ACT_HAPUS   4
#define ACT_KEMBALI 0

int menu_transaksi_utama(int bulan) {
    char title[64];
    snprintf(title, sizeof(title), "Menu Transaksi - %s", get_nama_bulan(bulan));

    Menu menu;
    menu_init(&menu, title);

    menu_add_item(&menu, "Lihat Daftar Transaksi", ACT_VIEW);
    menu_add_item(&menu, "Tambah Transaksi", ACT_TAMBAH);
    menu_add_item(&menu, "Edit Transaksi", ACT_EDIT);
    menu_add_item(&menu, "Hapus Transaksi", ACT_HAPUS);
    /* REV-2: Removed "Kembali" - use ESC to go back */

    return menu_navigate(&menu);
}

void handler_view_transaksi(int bulan) {
    int selected = 0;
    Transaksi list[MAX_TRANSAKSI];
    int count = transaksi_get_list(list, MAX_TRANSAKSI, bulan);
    
    while (1) {
        tui_clear();
        display_header("DAFTAR TRANSAKSI");
        
        int next_y = tampilkan_daftar_transaksi(bulan, selected);
        next_y = tampilkan_ringkasan_transaksi(bulan, next_y);
        
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
                    display_header("DETAIL TRANSAKSI");
                    tampilkan_detail_transaksi(&list[selected], 5);
                    display_footer("Tekan sembarang tombol untuk kembali");
                    tui_refresh();
                    tui_getch();
                    
                    count = transaksi_get_list(list, MAX_TRANSAKSI, bulan);
                    if (selected >= count) selected = count - 1;
                    if (selected < 0) selected = 0;
                }
                break;
                
            case 27:
                return;
        }
    }
}

void handler_tambah_transaksi(int bulan) {
    tampilkan_form_tambah_transaksi(bulan);
}

void handler_edit_transaksi(int bulan) {
    Transaksi list[MAX_TRANSAKSI];
    int count = transaksi_get_list(list, MAX_TRANSAKSI, bulan);
    
    if (count == 0) {
        show_warning("Belum ada transaksi");
        return;
    }
    
    Menu menu;
    menu_init(&menu, "Pilih Transaksi untuk Diedit");
    
    char nominal_str[30];
    for (int i = 0; i < count && i < 15; i++) {
        char item[80];
        format_rupiah(list[i].nominal, nominal_str);
        snprintf(item, sizeof(item), "%s | %s | %s | %s",
                 list[i].id, list[i].tanggal, 
                 list[i].jenis == JENIS_PENGELUARAN ? "Out" : "In",
                 nominal_str);
        menu_add_item(&menu, item, i);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL || pilihan < 0) {
        return;
    }
    
    tampilkan_form_edit_transaksi(list[pilihan].id);
}

void handler_hapus_transaksi(int bulan) {
    Transaksi list[MAX_TRANSAKSI];
    int count = transaksi_get_list(list, MAX_TRANSAKSI, bulan);
    
    if (count == 0) {
        show_warning("Belum ada transaksi");
        return;
    }
    
    Menu menu;
    menu_init(&menu, "Pilih Transaksi untuk Dihapus");
    
    char nominal_str[30];
    for (int i = 0; i < count && i < 15; i++) {
        char item[80];
        format_rupiah(list[i].nominal, nominal_str);
        snprintf(item, sizeof(item), "%s | %s | %s | %s",
                 list[i].id, list[i].tanggal,
                 list[i].jenis == JENIS_PENGELUARAN ? "Out" : "In",
                 nominal_str);
        menu_add_item(&menu, item, i);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL || pilihan < 0) {
        return;
    }
    
    tampilkan_konfirmasi_hapus_transaksi(list[pilihan].id);
}
