/**
 * @file validator_pos.c
 * @brief Implementasi fungsi validasi pos anggaran
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk validasi keberadaan pos,
 * keunikan nama pos, dan pengambilan data pos.
 */

#include <string.h>
#include <ctype.h>
#include "../../include/validator/validator_pos.h"
#include "../../include/utils/utils_string.h"

/**
 * Helper: Membandingkan string case-insensitive
 */
static int str_equal_nocase(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return 0;
    
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    
    return (*s1 == '\0' && *s2 == '\0');
}

/**
 * Validasi nama pos unik (belum ada di daftar)
 */
int validasi_pos_unik(const char *nama, PosAnggaran *list, int count) {
    if (nama == NULL || list == NULL) return 1;  /* Jika tidak ada data, dianggap unik */
    
    for (int i = 0; i < count; i++) {
        if (str_equal_nocase(nama, list[i].nama)) {
            return 0;  /* Nama sudah ada */
        }
    }
    
    return 1;  /* Nama unik */
}

/**
 * Validasi pos dengan nomor tertentu ada dalam daftar
 */
int validasi_pos_exists(int no, PosAnggaran *list, int count) {
    if (list == NULL || count <= 0) return 0;
    
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            return 1;  /* Pos ditemukan */
        }
    }
    
    return 0;  /* Pos tidak ditemukan */
}

/**
 * Mendapatkan nama pos berdasarkan nomor
 */
int get_nama_pos_by_no(int no, PosAnggaran *list, int count, char *result) {
    if (list == NULL || result == NULL || count <= 0) return 0;
    
    for (int i = 0; i < count; i++) {
        if (list[i].no == no) {
            str_copy_safe(result, list[i].nama, 21);
            return 1;  /* Berhasil */
        }
    }
    
    result[0] = '\0';
    return 0;  /* Tidak ditemukan */
}

/**
 * Mendapatkan index pos berdasarkan nama
 */
int get_index_pos_by_nama(const char *nama, PosAnggaran *list, int count) {
    if (nama == NULL || list == NULL) return -1;
    
    for (int i = 0; i < count; i++) {
        if (str_equal_nocase(nama, list[i].nama)) {
            return i;  /* Index ditemukan */
        }
    }
    
    return -1;  /* Tidak ditemukan */
}

/**
 * Validasi nama pos untuk edit (unik kecuali nama yang sedang diedit)
 */
int validasi_pos_unik_edit(const char *nama, int no_edit, PosAnggaran *list, int count) {
    if (nama == NULL || list == NULL) return 1;
    
    for (int i = 0; i < count; i++) {
        /* Skip pos yang sedang diedit */
        if (list[i].no == no_edit) continue;
        
        if (str_equal_nocase(nama, list[i].nama)) {
            return 0;  /* Nama sudah ada di pos lain */
        }
    }
    
    return 1;  /* Nama valid untuk edit */
}

/**
 * Validasi pos bisa dihapus (tidak ada transaksi terkait)
 */
int validasi_pos_bisa_hapus(int no, PosAnggaran *pos_list, int pos_count) {
    if (pos_list == NULL || pos_count <= 0) return 0;
    
    for (int i = 0; i < pos_count; i++) {
        if (pos_list[i].no == no) {
            /* Pos bisa dihapus jika tidak ada transaksi */
            return (pos_list[i].jumlah_transaksi == 0);
        }
    }
    
    return 0;  /* Pos tidak ditemukan */
}
