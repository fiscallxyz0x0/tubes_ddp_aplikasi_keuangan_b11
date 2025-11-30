/**
 * @file analisis_calc.c
 * @brief Implementasi fungsi kalkulasi analisis keuangan
 */

#include <string.h>
#include "../../include/analisis/analisis_calc.h"
#include "../../include/transaksi/transaksi_crud.h"
#include "../../include/file/file_analisis.h"
#include "../../include/constants.h"

int hitung_analisis_bulan(int bulan, AnalisisKeuangan *result) {
    if (!result || bulan < 1 || bulan > 12) return 0;
    
    memset(result, 0, sizeof(AnalisisKeuangan));
    
    /* Hitung total pemasukan dan pengeluaran */
    result->total_pemasukan = transaksi_total_pemasukan(bulan);
    result->total_pengeluaran = transaksi_total_pengeluaran(bulan);
    
    /* Hitung jumlah transaksi */
    result->total_trx_pemasukan = transaksi_count(bulan, JENIS_PEMASUKAN);
    result->total_trx_pengeluaran = transaksi_count(bulan, JENIS_PENGELUARAN);
    
    /* Hitung saldo akhir */
    result->saldo_akhir = (long long)result->total_pemasukan - 
                          (long long)result->total_pengeluaran;
    
    /* Hitung rata-rata pengeluaran */
    if (result->total_trx_pengeluaran > 0) {
        result->rata_rata_pengeluaran = (double)result->total_pengeluaran / 
                                         result->total_trx_pengeluaran;
    } else {
        result->rata_rata_pengeluaran = 0;
    }
    
    /* Hitung persentase sisa */
    if (result->total_pemasukan > 0) {
        result->persentase_sisa = ((double)result->saldo_akhir / 
                                   (double)result->total_pemasukan) * 100.0;
    } else {
        result->persentase_sisa = 0;
    }
    
    /* Tentukan kondisi keuangan */
    result->kondisi_keuangan = tentukan_kondisi_keuangan(
        result->total_pemasukan, result->total_pengeluaran);
    
    /* Tentukan kesimpulan */
    result->kesimpulan = tentukan_kesimpulan(result->persentase_sisa);
    
    return 1;
}

int tentukan_kondisi_keuangan(unsigned long long pemasukan, 
                               unsigned long long pengeluaran) {
    if (pengeluaran > pemasukan) {
        return KONDISI_DEFISIT;
    } else if (pengeluaran == pemasukan) {
        return KONDISI_SEIMBANG;
    } else {
        return KONDISI_SURPLUS;
    }
}

int tentukan_kesimpulan(double persentase_sisa) {
    if (persentase_sisa > 25.0) {
        return KESIMPULAN_HEMAT;
    } else if (persentase_sisa > 0.0) {
        return KESIMPULAN_SEIMBANG;
    } else if (persentase_sisa >= -10.0) {
        return KESIMPULAN_BOROS;
    } else {
        return KESIMPULAN_TIDAK_SEHAT;
    }
}

const char* get_label_kondisi(int kondisi) {
    switch (kondisi) {
        case KONDISI_DEFISIT:
            return "DEFISIT";
        case KONDISI_SEIMBANG:
            return "SEIMBANG";
        case KONDISI_SURPLUS:
            return "SURPLUS";
        default:
            return "TIDAK DIKETAHUI";
    }
}

const char* get_label_kesimpulan(int kesimpulan) {
    switch (kesimpulan) {
        case KESIMPULAN_HEMAT:
            return "HEMAT";
        case KESIMPULAN_SEIMBANG:
            return "SEIMBANG";
        case KESIMPULAN_BOROS:
            return "BOROS";
        case KESIMPULAN_TIDAK_SEHAT:
            return "TIDAK SEHAT";
        default:
            return "TIDAK DIKETAHUI";
    }
}

const char* get_deskripsi_kesimpulan(int kesimpulan) {
    switch (kesimpulan) {
        case KESIMPULAN_HEMAT:
            return "Keuangan Anda sangat baik! Sisa > 25% dari pemasukan.";
        case KESIMPULAN_SEIMBANG:
            return "Keuangan Anda cukup baik. Sisa 0-25% dari pemasukan.";
        case KESIMPULAN_BOROS:
            return "Perlu lebih hemat! Pengeluaran melebihi pemasukan hingga 10%.";
        case KESIMPULAN_TIDAK_SEHAT:
            return "Keuangan tidak sehat! Defisit lebih dari 10% pemasukan.";
        default:
            return "Status keuangan tidak dapat ditentukan.";
    }
}

int refresh_analisis_bulan(int bulan) {
    if (bulan < 1 || bulan > 12) return 0;
    
    AnalisisKeuangan analisis;
    if (!hitung_analisis_bulan(bulan, &analisis)) {
        return 0;
    }
    
    return save_analisis_bulan(bulan, &analisis);
}
