/**
 * @file utils_array.c
 * @brief Implementasi fungsi utilitas operasi array dinamis
 * @author Kelompok B11
 * @date 2025
 * 
 * Implementasi fungsi-fungsi untuk alokasi dan dealokasi
 * array dinamis Transaksi dan PosAnggaran.
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/utils/utils_array.h"
#include "../../include/constants.h"

/**
 * Mengalokasikan array Transaksi
 */
Transaksi* alloc_transaksi_array(int size) {
    if (size <= 0) return NULL;
    
    Transaksi *arr = (Transaksi*)malloc(size * sizeof(Transaksi));
    if (arr != NULL) {
        /* Inisialisasi semua elemen */
        memset(arr, 0, size * sizeof(Transaksi));
    }
    return arr;
}

/**
 * Mengalokasikan array PosAnggaran
 */
PosAnggaran* alloc_pos_array(int size) {
    if (size <= 0) return NULL;
    
    PosAnggaran *arr = (PosAnggaran*)malloc(size * sizeof(PosAnggaran));
    if (arr != NULL) {
        /* Inisialisasi semua elemen */
        memset(arr, 0, size * sizeof(PosAnggaran));
    }
    return arr;
}

/**
 * Membebaskan memory array Transaksi
 */
void free_transaksi_array(Transaksi *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

/**
 * Membebaskan memory array PosAnggaran
 */
void free_pos_array(PosAnggaran *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

/**
 * Menginisialisasi struct ListTransaksi
 */
int init_list_transaksi(ListTransaksi *list, int initial_capacity) {
    if (list == NULL || initial_capacity <= 0) return FAILURE;
    
    list->data = alloc_transaksi_array(initial_capacity);
    if (list->data == NULL) return FAILURE;
    
    list->count = 0;
    list->capacity = initial_capacity;
    return SUCCESS;
}

/**
 * Membebaskan memory ListTransaksi
 */
void free_list_transaksi(ListTransaksi *list) {
    if (list == NULL) return;
    
    free_transaksi_array(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

/**
 * Menambahkan transaksi ke ListTransaksi
 */
int add_to_list_transaksi(ListTransaksi *list, const Transaksi *trx) {
    if (list == NULL || trx == NULL) return FAILURE;
    
    /* Cek apakah perlu memperbesar kapasitas */
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Transaksi *new_data = (Transaksi*)realloc(list->data, 
                                                   new_capacity * sizeof(Transaksi));
        if (new_data == NULL) return FAILURE;
        
        list->data = new_data;
        list->capacity = new_capacity;
    }
    
    /* Copy data transaksi */
    memcpy(&list->data[list->count], trx, sizeof(Transaksi));
    list->count++;
    
    return SUCCESS;
}

/**
 * Menginisialisasi struct ListPos
 */
int init_list_pos(ListPos *list, int initial_capacity) {
    if (list == NULL || initial_capacity <= 0) return FAILURE;
    
    list->data = alloc_pos_array(initial_capacity);
    if (list->data == NULL) return FAILURE;
    
    list->count = 0;
    list->capacity = initial_capacity;
    return SUCCESS;
}

/**
 * Membebaskan memory ListPos
 */
void free_list_pos(ListPos *list) {
    if (list == NULL) return;
    
    free_pos_array(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

/**
 * Menambahkan pos anggaran ke ListPos
 */
int add_to_list_pos(ListPos *list, const PosAnggaran *pos) {
    if (list == NULL || pos == NULL) return FAILURE;
    
    /* Cek apakah perlu memperbesar kapasitas */
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        PosAnggaran *new_data = (PosAnggaran*)realloc(list->data, 
                                                       new_capacity * sizeof(PosAnggaran));
        if (new_data == NULL) return FAILURE;
        
        list->data = new_data;
        list->capacity = new_capacity;
    }
    
    /* Copy data pos */
    memcpy(&list->data[list->count], pos, sizeof(PosAnggaran));
    list->count++;
    
    return SUCCESS;
}

/**
 * Menginisialisasi struct Transaksi ke nilai default
 */
void init_transaksi(Transaksi *trx) {
    if (trx == NULL) return;
    
    memset(trx->id, 0, sizeof(trx->id));
    memset(trx->tanggal, 0, sizeof(trx->tanggal));
    trx->jenis = 0;
    memset(trx->pos, 0, sizeof(trx->pos));
    trx->nominal = 0;
    memset(trx->deskripsi, 0, sizeof(trx->deskripsi));
}

/**
 * Menginisialisasi struct PosAnggaran ke nilai default
 */
void init_pos_anggaran(PosAnggaran *pos) {
    if (pos == NULL) return;
    
    pos->no = 0;
    memset(pos->nama, 0, sizeof(pos->nama));
    pos->nominal = 0;
    pos->realisasi = 0;
    pos->sisa = 0;
    pos->jumlah_transaksi = 0;
    pos->status = STATUS_AMAN;
}

/**
 * Menginisialisasi struct AnalisisKeuangan ke nilai default
 */
void init_analisis_keuangan(AnalisisKeuangan *analisis) {
    if (analisis == NULL) return;
    
    analisis->total_pemasukan = 0;
    analisis->total_pengeluaran = 0;
    analisis->rata_rata_pengeluaran = 0.0;
    analisis->persentase_sisa = 0.0;
    analisis->saldo_akhir = 0;
    analisis->kondisi_keuangan = KONDISI_SEIMBANG;
    analisis->kesimpulan = KESIMPULAN_SEIMBANG;
    analisis->total_trx_pengeluaran = 0;
    analisis->total_trx_pemasukan = 0;
}
