/**
 * @file pos_display.c
 * @brief Implementasi fungsi display pos anggaran di TUI
 */

#include <stdio.h>
#include <string.h>
#include "../../include/pos/pos_display.h"
#include "../../include/pos/pos_crud.h"
#include "../../include/pos/pos_calc.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/tui/tui_table.h"
#include "../../include/tui/tui_input.h"
#include "../../include/tui/tui_message.h"
#include "../../include/tui/tui_menu.h"
#include "../../include/utils/utils_number.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/utils/utils_string.h"
#include "../../include/validator/validator_number.h"
#include "../../include/constants.h"

int tampilkan_daftar_pos(int bulan, int selected) {
    PosAnggaran list[MAX_POS];
    int count = pos_get_list(list, MAX_POS, bulan);
    
    /* Tampilkan header bulan */
    char title[64];
    snprintf(title, sizeof(title), "Pos Anggaran - %s", get_nama_bulan(bulan));
    
    tui_color_on(COLOR_PAIR_CYAN);
    tui_bold_on();
    tui_print(4, 2, title);
    tui_bold_off();
    tui_color_off(COLOR_PAIR_CYAN);
    
    return display_pos_table(list, count, 6, selected);
}

int tampilkan_detail_pos(PosAnggaran *pos, int start_y) {
    if (!pos) return start_y;
    
    int y = start_y;
    char buffer[64];
    
    tui_bold_on();
    tui_color_on(COLOR_PAIR_CYAN);
    tui_print(y++, 2, "Detail Pos Anggaran");
    tui_color_off(COLOR_PAIR_CYAN);
    tui_bold_off();
    
    tui_draw_hline(y++, 2, 50, '-');
    
    tui_printf(y++, 2, "Nomor       : %d", pos->no);
    tui_printf(y++, 2, "Nama        : %s", pos->nama);
    
    format_rupiah(pos->nominal, buffer);
    tui_printf(y++, 2, "Anggaran    : %s", buffer);
    
    format_rupiah(pos->realisasi, buffer);
    tui_printf(y++, 2, "Realisasi   : %s", buffer);
    
    format_saldo(pos->sisa, buffer);
    tui_print(y, 2, "Sisa        : ");
    if (pos->sisa < 0) {
        tui_color_on(COLOR_PAIR_RED);
    } else {
        tui_color_on(COLOR_PAIR_GREEN);
    }
    tui_print(y++, 16, buffer);
    tui_color_off(pos->sisa < 0 ? COLOR_PAIR_RED : COLOR_PAIR_GREEN);
    
    tui_printf(y++, 2, "Transaksi   : %d", pos->jumlah_transaksi);
    
    tui_print(y, 2, "Status      : ");
    if (pos->status == STATUS_AMAN) {
        tui_color_on(COLOR_PAIR_GREEN);
        tui_print(y++, 16, "AMAN");
    } else {
        tui_color_on(COLOR_PAIR_RED);
        tui_print(y++, 16, "TIDAK AMAN");
    }
    tui_attr_reset();
    
    return y + 1;
}

int tampilkan_ringkasan_pos(int bulan, int start_y) {
    int y = start_y;
    char buffer[64];
    
    unsigned long long total_anggaran = hitung_total_anggaran(bulan);
    unsigned long long total_realisasi = hitung_total_realisasi(bulan);
    long long total_sisa = (long long)total_anggaran - (long long)total_realisasi;
    
    tui_draw_hline(y++, 2, 60, '=');
    
    tui_bold_on();
    tui_print(y++, 2, "RINGKASAN:");
    tui_bold_off();
    
    format_rupiah(total_anggaran, buffer);
    tui_printf(y++, 2, "Total Anggaran  : %s", buffer);
    
    format_rupiah(total_realisasi, buffer);
    tui_printf(y++, 2, "Total Realisasi : %s", buffer);
    
    format_saldo(total_sisa, buffer);
    tui_print(y, 2, "Total Sisa      : ");
    if (total_sisa < 0) {
        tui_color_on(COLOR_PAIR_RED);
    } else {
        tui_color_on(COLOR_PAIR_GREEN);
    }
    tui_print(y++, 20, buffer);
    tui_attr_reset();
    
    return y + 1;
}

int tampilkan_form_tambah_pos(int bulan) {
    tui_clear();
    display_header("TAMBAH POS ANGGARAN");
    
    char nama[MAX_POS_LENGTH + 1];
    unsigned long long nominal;
    
    int y = 5;
    
    char bulan_info[64];
    snprintf(bulan_info, sizeof(bulan_info), "Bulan: %s", get_nama_bulan(bulan));
    tui_print(y++, 2, bulan_info);
    y++;
    
    /* Input nama */
    if (!input_string_required(y++, 2, "Nama Pos: ", nama, sizeof(nama))) {
        return 0;
    }
    
    /* Input nominal */
    if (!input_number_min(y++, 2, "Anggaran: Rp ", &nominal, 1)) {
        return 0;
    }
    
    /* Konfirmasi */
    y++;
    if (!input_konfirmasi(y, 2, "Simpan pos anggaran?")) {
        show_info("Dibatalkan");
        return 0;
    }
    
    /* Simpan */
    char error_msg[100];
    if (pos_tambah(nama, nominal, bulan, error_msg)) {
        show_success("Pos anggaran berhasil ditambahkan");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}

int tampilkan_form_edit_pos(int no, int bulan) {
    PosAnggaran pos;
    if (!pos_get_by_no(no, bulan, &pos)) {
        show_error("Pos tidak ditemukan");
        return 0;
    }
    
    tui_clear();
    display_header("EDIT POS ANGGARAN");
    
    int y = 5;
    
    /* Tampilkan data saat ini */
    tui_print(y++, 2, "Data saat ini:");
    tui_printf(y++, 2, "  Nama    : %s", pos.nama);
    char nominal_str[30];
    format_rupiah(pos.nominal, nominal_str);
    tui_printf(y++, 2, "  Anggaran: %s", nominal_str);
    y++;
    
    tui_print(y++, 2, "Masukkan data baru (kosongkan jika tidak diubah):");
    y++;
    
    char nama_baru[MAX_POS_LENGTH + 1];
    unsigned long long nominal_baru = 0;
    
    /* Input nama baru */
    if (!input_string(y++, 2, "Nama baru: ", nama_baru, sizeof(nama_baru))) {
        return 0;
    }
    
    /* Input nominal baru */
    char nominal_input[32];
    if (!input_string(y++, 2, "Anggaran baru: Rp ", nominal_input, sizeof(nominal_input))) {
        return 0;
    }
    if (strlen(nominal_input) > 0) {
        parse_nominal(nominal_input, &nominal_baru);
    }
    
    /* Cek apakah ada perubahan */
    if (strlen(nama_baru) == 0 && nominal_baru == 0) {
        show_info("Tidak ada perubahan");
        return 0;
    }
    
    /* Konfirmasi */
    y++;
    if (!input_konfirmasi(y, 2, "Simpan perubahan?")) {
        show_info("Dibatalkan");
        return 0;
    }
    
    /* Simpan */
    char error_msg[100];
    const char *nama_param = strlen(nama_baru) > 0 ? nama_baru : NULL;
    
    if (pos_edit(no, nama_param, nominal_baru, bulan, error_msg)) {
        show_success("Pos anggaran berhasil diupdate");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}

int tampilkan_konfirmasi_hapus_pos(int no, int bulan) {
    PosAnggaran pos;
    if (!pos_get_by_no(no, bulan, &pos)) {
        show_error("Pos tidak ditemukan");
        return 0;
    }
    
    /* Cek apakah bisa dihapus */
    if (pos.jumlah_transaksi > 0) {
        show_error("Pos tidak bisa dihapus karena masih ada %d transaksi", pos.jumlah_transaksi);
        return 0;
    }
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Hapus pos '%s'?", pos.nama);
    
    if (!show_confirm(msg)) {
        show_info("Dibatalkan");
        return 0;
    }
    
    char error_msg[100];
    if (pos_hapus(no, bulan, error_msg)) {
        show_success("Pos anggaran berhasil dihapus");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}

int tampilkan_pilih_pos(int bulan, char *result) {
    if (!result) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = pos_get_list(list, MAX_POS, bulan);
    
    if (count == 0) {
        show_warning("Belum ada pos anggaran untuk bulan ini");
        return 0;
    }
    
    Menu menu;
    menu_init(&menu, "Pilih Pos Anggaran");
    
    for (int i = 0; i < count; i++) {
        menu_add_item(&menu, list[i].nama, i + 1);
    }
    
    int pilihan = menu_navigate(&menu);
    
    if (pilihan == CANCEL || pilihan <= 0) {
        return 0;
    }
    
    str_copy_safe(result, list[pilihan - 1].nama, MAX_POS_LENGTH + 1);
    return 1;
}
