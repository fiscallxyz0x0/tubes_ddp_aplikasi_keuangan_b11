/**
 * @file transaksi_display.c
 * @brief Implementasi fungsi display transaksi di TUI
 */

#include <stdio.h>
#include <string.h>
#include "../../include/transaksi/transaksi_display.h"
#include "../../include/transaksi/transaksi_crud.h"
#include "../../include/pos/pos_display.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/tui/tui_table.h"
#include "../../include/tui/tui_input.h"
#include "../../include/tui/tui_message.h"
#include "../../include/tui/tui_menu.h"
#include "../../include/file/file_parser.h"
#include "../../include/utils/utils_number.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/utils/utils_date.h"
#include "../../include/utils/utils_string.h"
#include "../../include/validator/validator_number.h"
#include "../../include/validator/validator_date.h"
#include "../../include/constants.h"

int tampilkan_daftar_transaksi(int bulan, int selected) {
    Transaksi list[MAX_TRANSAKSI];
    int count = transaksi_get_list(list, MAX_TRANSAKSI, bulan);
    
    char title[64];
    snprintf(title, sizeof(title), "Transaksi - %s", get_nama_bulan(bulan));
    
    tui_color_on(COLOR_PAIR_CYAN);
    tui_bold_on();
    tui_print(4, 2, title);
    tui_bold_off();
    tui_color_off(COLOR_PAIR_CYAN);
    
    return display_transaksi_table(list, count, 6, selected);
}

int tampilkan_detail_transaksi(Transaksi *trx, int start_y) {
    if (!trx) return start_y;
    
    int y = start_y;
    char buffer[64];
    
    tui_bold_on();
    tui_color_on(COLOR_PAIR_CYAN);
    tui_print(y++, 2, "Detail Transaksi");
    tui_color_off(COLOR_PAIR_CYAN);
    tui_bold_off();
    
    tui_draw_hline(y++, 2, 50, '-');
    
    tui_printf(y++, 2, "ID          : %s", trx->id);
    tui_printf(y++, 2, "Tanggal     : %s", trx->tanggal);
    
    tui_print(y, 2, "Jenis       : ");
    if (trx->jenis == JENIS_PENGELUARAN) {
        tui_color_on(COLOR_PAIR_RED);
        tui_print(y++, 16, "Pengeluaran");
    } else {
        tui_color_on(COLOR_PAIR_GREEN);
        tui_print(y++, 16, "Pemasukan");
    }
    tui_attr_reset();
    
    tui_printf(y++, 2, "Pos         : %s", trx->pos);
    
    format_rupiah(trx->nominal, buffer);
    tui_printf(y++, 2, "Nominal     : %s", buffer);
    
    tui_printf(y++, 2, "Deskripsi   : %s", 
               strlen(trx->deskripsi) > 0 ? trx->deskripsi : "-");
    
    return y + 1;
}

int tampilkan_ringkasan_transaksi(int bulan, int start_y) {
    int y = start_y;
    char buffer[64];
    
    unsigned long long pemasukan = transaksi_total_pemasukan(bulan);
    unsigned long long pengeluaran = transaksi_total_pengeluaran(bulan);
    long long saldo = (long long)pemasukan - (long long)pengeluaran;
    int jml_masuk = transaksi_count(bulan, JENIS_PEMASUKAN);
    int jml_keluar = transaksi_count(bulan, JENIS_PENGELUARAN);
    
    tui_draw_hline(y++, 2, 60, '=');
    
    tui_bold_on();
    tui_print(y++, 2, "RINGKASAN:");
    tui_bold_off();
    
    format_rupiah(pemasukan, buffer);
    tui_printf(y++, 2, "Total Pemasukan   : %s (%d transaksi)", buffer, jml_masuk);
    
    format_rupiah(pengeluaran, buffer);
    tui_printf(y++, 2, "Total Pengeluaran : %s (%d transaksi)", buffer, jml_keluar);
    
    format_saldo(saldo, buffer);
    tui_print(y, 2, "Saldo             : ");
    if (saldo < 0) {
        tui_color_on(COLOR_PAIR_RED);
    } else {
        tui_color_on(COLOR_PAIR_GREEN);
    }
    tui_print(y++, 22, buffer);
    tui_attr_reset();
    
    return y + 1;
}

int tampilkan_form_tambah_transaksi(int bulan) {
    tui_clear();
    display_header("TAMBAH TRANSAKSI");

    int y = 5;
    char tanggal[12], pos[MAX_POS_LENGTH + 1], deskripsi[MAX_DESKRIPSI_LENGTH + 1];
    unsigned long long nominal;
    int jenis;

    /* Info bulan */
    char bulan_info[64];
    snprintf(bulan_info, sizeof(bulan_info), "Bulan: %s", get_nama_bulan(bulan));
    tui_print(y++, 2, bulan_info);
    y++;

    /* Input tanggal dengan validasi bulan - REV-3 */
    while (1) {
        if (!input_tanggal(y, 2, "Tanggal", tanggal)) {
            return 0;
        }
        /* REV-3: Validasi bulan sesuai */
        if (!validasi_bulan_sesuai(tanggal, bulan)) {
            char error_msg[128];
            snprintf(error_msg, sizeof(error_msg),
                     "Anda memasukkan %s yang berbeda dari bulan terpilih! Input tidak valid!",
                     tanggal);
            show_error(error_msg);
            /* Redraw form */
            tui_clear();
            display_header("TAMBAH TRANSAKSI");
            y = 5;
            tui_print(y++, 2, bulan_info);
            y++;
            continue;
        }
        y++;
        break;
    }

    /* Input jenis */
    if (!input_jenis_transaksi(y++, 2, &jenis)) {
        return 0;
    }
    y++;
    
    /* Pilih pos */
    tui_print(y++, 2, "Pilih Pos Anggaran:");
    if (!tampilkan_pilih_pos(bulan, pos)) {
        show_warning("Pos anggaran harus dipilih");
        return 0;
    }
    
    /* Kembali ke form */
    tui_clear();
    display_header("TAMBAH TRANSAKSI");
    y = 5;
    tui_printf(y++, 2, "Tanggal : %s", tanggal);
    tui_printf(y++, 2, "Jenis   : %s", get_label_jenis(jenis));
    tui_printf(y++, 2, "Pos     : %s", pos);
    y++;
    
    /* Input nominal */
    if (!input_number_min(y++, 2, "Nominal: Rp ", &nominal, 1)) {
        return 0;
    }
    
    /* Input deskripsi (opsional) */
    if (!input_string(y++, 2, "Deskripsi (opsional): ", deskripsi, sizeof(deskripsi))) {
        return 0;
    }
    
    /* Konfirmasi */
    y++;
    if (!input_konfirmasi(y, 2, "Simpan transaksi?")) {
        show_info("Dibatalkan");
        return 0;
    }
    
    /* Simpan */
    char error_msg[100];
    if (transaksi_tambah(tanggal, jenis, pos, nominal, deskripsi, error_msg)) {
        show_success("Transaksi berhasil ditambahkan");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}

int tampilkan_form_edit_transaksi(const char *id) {
    Transaksi trx;
    if (!transaksi_get_by_id(id, &trx)) {
        show_error("Transaksi tidak ditemukan");
        return 0;
    }

    /* Get bulan from existing transaction for validation */
    int bulan_trx = ekstrak_bulan(trx.tanggal);

    char tanggal_baru[12], deskripsi_baru[MAX_DESKRIPSI_LENGTH + 1], nominal_input[32];
    unsigned long long nominal_baru = 0;

    while (1) {
        tui_clear();
        display_header("EDIT TRANSAKSI");

        int y = 5;
        char nominal_str[64];
        format_rupiah(trx.nominal, nominal_str);

        /* Tampilkan data saat ini */
        tui_print(y++, 2, "Data saat ini:");
        tui_printf(y++, 2, "  ID        : %s", trx.id);
        tui_printf(y++, 2, "  Tanggal   : %s", trx.tanggal);
        tui_printf(y++, 2, "  Jenis     : %s", get_label_jenis(trx.jenis));
        tui_printf(y++, 2, "  Pos       : %s", trx.pos);
        tui_printf(y++, 2, "  Nominal   : %s", nominal_str);
        tui_printf(y++, 2, "  Deskripsi : %s", trx.deskripsi);
        y++;

        tui_print(y++, 2, "Masukkan data baru (kosongkan jika tidak diubah):");
        y++;

        /* REV-7: Input tanggal baru dengan validasi langsung */
        if (!input_string(y++, 2, "Tanggal baru (dd-mm-YYYY): ", tanggal_baru, sizeof(tanggal_baru))) {
            return 0;
        }

        /* REV-7: Validasi langsung setelah input tanggal */
        if (strlen(tanggal_baru) > 0) {
            if (!validasi_tanggal_lengkap(tanggal_baru)) {
                show_error("Format tanggal tidak valid! Gunakan format dd-mm-YYYY");
                continue;
            }
            /* REV-3: Validasi bulan sesuai dengan transaksi asli */
            if (!validasi_bulan_sesuai(tanggal_baru, bulan_trx)) {
                char error_msg[128];
                snprintf(error_msg, sizeof(error_msg),
                         "Anda memasukkan %s yang berbeda dari bulan terpilih! Input tidak valid!",
                         tanggal_baru);
                show_error(error_msg);
                continue;
            }
        }

        /* REV-7: Input nominal baru dengan validasi langsung */
        if (!input_string(y++, 2, "Nominal baru: Rp ", nominal_input, sizeof(nominal_input))) {
            return 0;
        }
        if (strlen(nominal_input) > 0) {
            if (!parse_nominal(nominal_input, &nominal_baru) || nominal_baru == 0) {
                show_error("Nominal tidak valid! Harus berupa angka lebih dari 0");
                continue;
            }
        }

        /* REV-7: Input deskripsi baru dengan validasi langsung */
        if (!input_string(y++, 2, "Deskripsi baru: ", deskripsi_baru, sizeof(deskripsi_baru))) {
            return 0;
        }
        if (strlen(deskripsi_baru) > MAX_DESKRIPSI_LENGTH) {
            show_error("Deskripsi terlalu panjang (max 50 karakter)");
            continue;
        }

        break; /* All validations passed */
    }

    /* Cek perubahan */
    if (strlen(tanggal_baru) == 0 && nominal_baru == 0 && strlen(deskripsi_baru) == 0) {
        show_info("Tidak ada perubahan");
        return 0;
    }

    /* Konfirmasi */
    if (!show_confirm("Simpan perubahan?")) {
        show_info("Dibatalkan");
        return 0;
    }

    /* Simpan */
    char error_msg[100];
    const char *tgl_param = strlen(tanggal_baru) > 0 ? tanggal_baru : NULL;
    const char *desk_param = strlen(deskripsi_baru) > 0 ? deskripsi_baru : NULL;

    if (transaksi_edit(id, tgl_param, -1, NULL, nominal_baru, desk_param, error_msg)) {
        show_success("Transaksi berhasil diupdate");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}

int tampilkan_konfirmasi_hapus_transaksi(const char *id) {
    Transaksi trx;
    if (!transaksi_get_by_id(id, &trx)) {
        show_error("Transaksi tidak ditemukan");
        return 0;
    }
    
    char nominal_str[30];
    format_rupiah(trx.nominal, nominal_str);
    
    char msg[128];
    snprintf(msg, sizeof(msg), "Hapus transaksi %s (%s %s)?", 
             trx.id, get_label_jenis(trx.jenis), nominal_str);
    
    if (!show_confirm(msg)) {
        show_info("Dibatalkan");
        return 0;
    }
    
    char error_msg[100];
    if (transaksi_hapus(id, error_msg)) {
        show_success("Transaksi berhasil dihapus");
        return 1;
    } else {
        show_error("%s", error_msg);
        return 0;
    }
}
