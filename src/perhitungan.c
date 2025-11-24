#include <perhitungan.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Menggunakan string tetap untuk memudahkan I/O teks
struct PosAnggaran {
    int kodePos;                 // Kode numerik internal (unik)
    char namaPos[64];            // Nama kategori pos anggaran
    double batasNominal;         // Batas anggaran untuk pos
};

struct Transaksi {
    char kodeTransaksi[8];       // Format: T001, T002, ...
    char tanggal[16];            // Format bebas: YYYY-MM-DD disarankan
    char jenis[16];              // "Pemasukan" atau "Pengeluaran"
    char kategori[64];           // Nama pos anggaran terkait
    double nominal;              // Nilai uang
    char deskripsi[128];         // Catatan singkat
};


const char* analisisKondisiKeuangan(double saldo) {
    if (saldo < 0.0) return "Defisit";
    if (saldo == 0.0) return "Seimbang";
    return "Surplus";
}

double hitungRataRataPengeluaran(Transaksi *arrayTrx, int jumlahTrx) {
    double totalKeluar = 0.0;
    int jumlahKeluar = 0;
    for (int i = 0; i < jumlahTrx; ++i) {
        if (strcmp(arrayTrx[i].jenis, "Pengeluaran") == 0) {
            totalKeluar += arrayTrx[i].nominal;
            jumlahKeluar++;
        }
    }
    if (jumlahKeluar == 0) return 0.0;
    return totalKeluar / (double)jumlahKeluar;
}

// Mengisi array pengeluaran per pos (outPengeluaranPerPos) sesuai urutan arrayPos
void hitungRealisasiAnggaran(PosAnggaran *arrayPos, int jumlahPos, Transaksi *arrayTrx, int jumlahTrx, double *outPengeluaranPerPos) {
    for (int i = 0; i < jumlahPos; ++i) outPengeluaranPerPos[i] = 0.0;

    for (int i = 0; i < jumlahPos; ++i) {
        for (int j = 0; j < jumlahTrx; ++j) {
            if (strcmp(arrayTrx[j].jenis, "Pengeluaran") == 0 &&
                strcmp(arrayTrx[j].kategori, arrayPos[i].namaPos) == 0) {
                outPengeluaranPerPos[i] += arrayTrx[j].nominal;
            }
        }
    }
}

double hitungSaldo(double totalMasuk, double totalKeluar) {
    return totalMasuk - totalKeluar;
}

double hitungTotalPengeluaran(Transaksi *arrayTrx, int jumlahTrx) {
    double total = 0.0;
    for (int i = 0; i < jumlahTrx; ++i) {
        if (strcmp(arrayTrx[i].jenis, "Pengeluaran") == 0) total += arrayTrx[i].nominal;
    }
    return total;
}

// Menentukan kesimpulan gaya hidup keuangan mahasiswa
const char* kesimpulanMahasiswa(double totalPemasukan, double saldo) {
    if (totalPemasukan <= 0.0) {
        return "Pemasukan tidak terdeteksi. Fokus pada menambah pemasukan.";
    }
    double persen = (saldo / totalPemasukan) * 100.0;

    if (saldo >= 0.0) {
        if (persen > 25.0) return "Anda termasuk mahasiswa hemat dan produktif.";
        if (persen > 0.0)  return "Keuangan Anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.";
        return "Keuangan Anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.";
    } else {
        double defisit = -persen;
        if (defisit < 10.0) return "Anda mulai boros, perhatikan pengeluaran harian.";
        return "Kondisi keuangan kurang sehat. Kurangi pengeluaran dan cari tambahan pemasukan.";
    }
}

static int sama_tanpa_case(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

/*
 * Menghitung total pemasukan dari array transaksi
 */

double hitungTotalPemasukan(const Transaksi *arrayTrx, int jumlahTrx) {
    if (!arrayTrx || jumlahTrx <= 0) return 0.0;

    double total = 0.0;
    for (int i = 0; i < jumlahTrx; i++) {
        const char *jenis = arrayTrx[i].jenis;
        if (jenis && (sama_tanpa_case(jenis, "PEMASUKAN") || sama_tanpa_case(jenis, "Pemasukan"))) {
            total += arrayTrx[i].nominal;
        }
    }
    return total;
}
