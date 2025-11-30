/**
 * @file transaksi_crud.c
 * @brief Implementasi operasi CRUD transaksi dengan validasi
 */

#include <stdio.h>
#include <string.h>
#include "../../include/transaksi/transaksi_crud.h"
#include "../../include/file/file_transaksi.h"
#include "../../include/pos/pos_calc.h"
#include "../../include/validator/validator_string.h"
#include "../../include/validator/validator_date.h"
#include "../../include/validator/validator_number.h"
#include "../../include/utils/utils_string.h"
#include "../../include/utils/utils_date.h"
#include "../../include/constants.h"

static void set_error(char *error_msg, const char *msg) {
    if (error_msg && msg) {
        str_copy_safe(error_msg, msg, 100);
    }
}

int transaksi_tambah(const char *tanggal, int jenis, const char *pos,
                     unsigned long long nominal, const char *deskripsi,
                     char *error_msg) {
    /* Validasi tanggal */
    if (!tanggal || !validasi_tanggal_lengkap(tanggal)) {
        set_error(error_msg, "Tanggal tidak valid");
        return 0;
    }
    
    /* Validasi jenis */
    if (!validasi_jenis_transaksi(jenis)) {
        set_error(error_msg, "Jenis transaksi tidak valid");
        return 0;
    }
    
    /* Validasi pos */
    if (!pos || !validasi_tidak_kosong(pos)) {
        set_error(error_msg, "Pos anggaran harus dipilih");
        return 0;
    }
    
    /* Validasi nominal */
    if (!validasi_nominal_positif(nominal)) {
        set_error(error_msg, "Nominal harus lebih dari 0");
        return 0;
    }
    
    /* Validasi deskripsi (opsional tapi tidak boleh ada pipe) */
    if (deskripsi && strlen(deskripsi) > 0) {
        if (!validasi_panjang_deskripsi(deskripsi)) {
            set_error(error_msg, "Deskripsi terlalu panjang (max 50 karakter)");
            return 0;
        }
        if (!validasi_tidak_ada_pipe(deskripsi)) {
            set_error(error_msg, "Deskripsi tidak boleh mengandung karakter |");
            return 0;
        }
    }
    
    /* Buat transaksi baru */
    Transaksi trx;
    memset(&trx, 0, sizeof(Transaksi));
    
    generate_transaksi_id(trx.id);
    str_copy_safe(trx.tanggal, tanggal, sizeof(trx.tanggal));
    trx.jenis = jenis;
    str_copy_safe(trx.pos, pos, sizeof(trx.pos));
    trx.nominal = nominal;
    if (deskripsi) {
        str_copy_safe(trx.deskripsi, deskripsi, sizeof(trx.deskripsi));
    }
    
    if (!add_transaksi(&trx)) {
        set_error(error_msg, "Gagal menyimpan transaksi");
        return 0;
    }
    
    /* Update kalkulasi pos */
    int bulan = ekstrak_bulan(tanggal);
    if (bulan > 0) {
        update_semua_pos_bulan(bulan);
    }
    
    return 1;
}

int transaksi_edit(const char *id, const char *tanggal, int jenis,
                   const char *pos, unsigned long long nominal,
                   const char *deskripsi, char *error_msg) {
    if (!id) {
        set_error(error_msg, "ID transaksi tidak valid");
        return 0;
    }
    
    /* Load transaksi yang akan diedit */
    Transaksi trx;
    if (!find_transaksi_by_id(id, &trx)) {
        set_error(error_msg, "Transaksi tidak ditemukan");
        return 0;
    }
    
    int old_bulan = ekstrak_bulan(trx.tanggal);
    
    /* Update tanggal jika diubah */
    if (tanggal && strlen(tanggal) > 0) {
        if (!validasi_tanggal_lengkap(tanggal)) {
            set_error(error_msg, "Tanggal tidak valid");
            return 0;
        }
        str_copy_safe(trx.tanggal, tanggal, sizeof(trx.tanggal));
    }
    
    /* Update jenis jika diubah */
    if (jenis >= 0) {
        if (!validasi_jenis_transaksi(jenis)) {
            set_error(error_msg, "Jenis transaksi tidak valid");
            return 0;
        }
        trx.jenis = jenis;
    }
    
    /* Update pos jika diubah */
    if (pos && strlen(pos) > 0) {
        str_copy_safe(trx.pos, pos, sizeof(trx.pos));
    }
    
    /* Update nominal jika diubah */
    if (nominal > 0) {
        trx.nominal = nominal;
    }
    
    /* Update deskripsi jika diubah */
    if (deskripsi) {
        if (strlen(deskripsi) > 0 && !validasi_panjang_deskripsi(deskripsi)) {
            set_error(error_msg, "Deskripsi terlalu panjang");
            return 0;
        }
        str_copy_safe(trx.deskripsi, deskripsi, sizeof(trx.deskripsi));
    }
    
    if (!update_transaksi(id, &trx)) {
        set_error(error_msg, "Gagal menyimpan perubahan");
        return 0;
    }
    
    /* Update kalkulasi pos untuk bulan lama dan baru */
    int new_bulan = ekstrak_bulan(trx.tanggal);
    if (old_bulan > 0) update_semua_pos_bulan(old_bulan);
    if (new_bulan > 0 && new_bulan != old_bulan) update_semua_pos_bulan(new_bulan);
    
    return 1;
}

int transaksi_hapus(const char *id, char *error_msg) {
    if (!id) {
        set_error(error_msg, "ID transaksi tidak valid");
        return 0;
    }
    
    /* Load transaksi untuk dapat bulan */
    Transaksi trx;
    if (!find_transaksi_by_id(id, &trx)) {
        set_error(error_msg, "Transaksi tidak ditemukan");
        return 0;
    }
    
    int bulan = ekstrak_bulan(trx.tanggal);
    
    if (!delete_transaksi(id)) {
        set_error(error_msg, "Gagal menghapus transaksi");
        return 0;
    }
    
    /* Update kalkulasi pos */
    if (bulan > 0) {
        update_semua_pos_bulan(bulan);
    }
    
    return 1;
}

int transaksi_get_list(Transaksi *list, int max_count, int bulan) {
    if (!list || max_count <= 0) return 0;
    
    if (bulan > 0 && bulan <= 12) {
        return load_transaksi_bulan(list, max_count, bulan);
    } else {
        return load_transaksi(list, max_count);
    }
}

int transaksi_get_by_id(const char *id, Transaksi *result) {
    return find_transaksi_by_id(id, result);
}

unsigned long long transaksi_total_pemasukan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi_bulan(list, MAX_TRANSAKSI, bulan);
    
    unsigned long long total = 0;
    for (int i = 0; i < count; i++) {
        if (list[i].jenis == JENIS_PEMASUKAN) {
            total += list[i].nominal;
        }
    }
    
    return total;
}

unsigned long long transaksi_total_pengeluaran(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi_bulan(list, MAX_TRANSAKSI, bulan);
    
    unsigned long long total = 0;
    for (int i = 0; i < count; i++) {
        if (list[i].jenis == JENIS_PENGELUARAN) {
            total += list[i].nominal;
        }
    }
    
    return total;
}

int transaksi_count(int bulan, int jenis) {
    if (bulan < 1 || bulan > 12) return 0;
    
    Transaksi list[MAX_TRANSAKSI];
    int count = load_transaksi_bulan(list, MAX_TRANSAKSI, bulan);
    
    if (jenis < 0) return count;
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (list[i].jenis == jenis) {
            total++;
        }
    }
    
    return total;
}
