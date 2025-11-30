/**
 * @file pos_crud.c
 * @brief Implementasi operasi CRUD pos anggaran
 */

#include <stdio.h>
#include <string.h>
#include "../../include/pos/pos_crud.h"
#include "../../include/pos/pos_calc.h"
#include "../../include/file/file_pos.h"
#include "../../include/file/file_transaksi.h"
#include "../../include/validator/validator_string.h"
#include "../../include/validator/validator_pos.h"
#include "../../include/utils/utils_string.h"
#include "../../include/constants.h"

static void set_error(char *error_msg, const char *msg) {
    if (error_msg && msg) {
        str_copy_safe(error_msg, msg, 100);
    }
}

int pos_tambah(const char *nama, unsigned long long nominal, int bulan, char *error_msg) {
    if (!nama || bulan < 1 || bulan > 12) {
        set_error(error_msg, "Parameter tidak valid");
        return 0;
    }
    
    /* Validasi nama */
    if (!validasi_tidak_kosong(nama)) {
        set_error(error_msg, "Nama pos tidak boleh kosong");
        return 0;
    }
    
    if (!validasi_panjang_pos(nama)) {
        set_error(error_msg, "Nama pos terlalu panjang (max 20 karakter)");
        return 0;
    }
    
    if (!validasi_tidak_ada_pipe(nama)) {
        set_error(error_msg, "Nama pos tidak boleh mengandung karakter |");
        return 0;
    }
    
    /* Cek nama unik */
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    if (!validasi_pos_unik(nama, list, count)) {
        set_error(error_msg, "Nama pos sudah ada");
        return 0;
    }
    
    /* Validasi nominal */
    if (nominal == 0) {
        set_error(error_msg, "Nominal anggaran harus lebih dari 0");
        return 0;
    }
    
    /* Buat pos baru */
    PosAnggaran pos;
    memset(&pos, 0, sizeof(PosAnggaran));
    str_copy_safe(pos.nama, nama, sizeof(pos.nama));
    pos.nominal = nominal;
    
    if (!add_pos(&pos, bulan)) {
        set_error(error_msg, "Gagal menyimpan pos anggaran");
        return 0;
    }
    
    return 1;
}

int pos_edit(int no, const char *nama_baru, unsigned long long nominal_baru, int bulan, char *error_msg) {
    if (no <= 0 || bulan < 1 || bulan > 12) {
        set_error(error_msg, "Parameter tidak valid");
        return 0;
    }
    
    /* Load pos yang akan diedit */
    PosAnggaran pos;
    if (!find_pos_by_no(no, bulan, &pos)) {
        set_error(error_msg, "Pos tidak ditemukan");
        return 0;
    }
    
    /* Validasi nama baru jika diubah */
    if (nama_baru && strlen(nama_baru) > 0) {
        if (!validasi_panjang_pos(nama_baru)) {
            set_error(error_msg, "Nama pos terlalu panjang (max 20 karakter)");
            return 0;
        }
        
        if (!validasi_tidak_ada_pipe(nama_baru)) {
            set_error(error_msg, "Nama pos tidak boleh mengandung karakter |");
            return 0;
        }
        
        /* Cek nama unik (kecuali pos ini sendiri) */
        PosAnggaran list[MAX_POS];
        int count = load_pos_bulan(list, MAX_POS, bulan);
        
        if (!validasi_pos_unik_edit(nama_baru, no, list, count)) {
            set_error(error_msg, "Nama pos sudah digunakan");
            return 0;
        }
        
        str_copy_safe(pos.nama, nama_baru, sizeof(pos.nama));
    }
    
    /* Update nominal jika diubah */
    if (nominal_baru > 0) {
        pos.nominal = nominal_baru;
    }
    
    /* Update kalkulasi */
    update_kalkulasi_pos(&pos, bulan);
    
    if (!update_pos(no, &pos, bulan)) {
        set_error(error_msg, "Gagal menyimpan perubahan");
        return 0;
    }
    
    return 1;
}

int pos_hapus(int no, int bulan, char *error_msg) {
    if (no <= 0 || bulan < 1 || bulan > 12) {
        set_error(error_msg, "Parameter tidak valid");
        return 0;
    }
    
    /* Load pos yang akan dihapus */
    PosAnggaran pos;
    if (!find_pos_by_no(no, bulan, &pos)) {
        set_error(error_msg, "Pos tidak ditemukan");
        return 0;
    }
    
    /* Update kalkulasi untuk cek transaksi terkait */
    update_kalkulasi_pos(&pos, bulan);
    
    /* Cek apakah pos bisa dihapus */
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    /* Cari index pos */
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            list[i] = pos;  /* Update dengan kalkulasi terbaru */
            idx = i;
            break;
        }
    }
    
    if (idx < 0 || !validasi_pos_bisa_hapus(no, list, count)) {
        set_error(error_msg, "Pos tidak bisa dihapus karena masih ada transaksi terkait");
        return 0;
    }
    
    if (!delete_pos(no, bulan)) {
        set_error(error_msg, "Gagal menghapus pos");
        return 0;
    }
    
    return 1;
}

int pos_get_list(PosAnggaran *list, int max_count, int bulan) {
    if (!list || max_count <= 0 || bulan < 1 || bulan > 12) return 0;
    
    int count = load_pos_bulan(list, max_count, bulan);
    
    /* Update kalkulasi untuk setiap pos */
    for (int i = 0; i < count; i++) {
        update_kalkulasi_pos(&list[i], bulan);
    }
    
    return count;
}

int pos_get_by_no(int no, int bulan, PosAnggaran *result) {
    if (no <= 0 || bulan < 1 || bulan > 12 || !result) return 0;
    
    if (!find_pos_by_no(no, bulan, result)) return 0;
    
    /* Update kalkulasi */
    update_kalkulasi_pos(result, bulan);
    
    return 1;
}

int pos_get_names(char names[][MAX_POS_LENGTH + 1], int max_count, int bulan) {
    if (!names || max_count <= 0 || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran list[MAX_POS];
    int count = load_pos_bulan(list, MAX_POS, bulan);
    
    int result_count = (count < max_count) ? count : max_count;
    
    for (int i = 0; i < result_count; i++) {
        str_copy_safe(names[i], list[i].nama, MAX_POS_LENGTH + 1);
    }
    
    return result_count;
}

int pos_exists(const char *nama, int bulan) {
    if (!nama || bulan < 1 || bulan > 12) return 0;
    
    PosAnggaran result;
    return find_pos_by_nama(nama, bulan, &result);
}

int pos_refresh(int bulan) {
    return update_semua_pos_bulan(bulan);
}
