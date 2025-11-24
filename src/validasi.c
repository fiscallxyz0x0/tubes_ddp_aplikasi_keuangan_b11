#include <validasi.h>
#include <string.h>

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

int isNotEmpty(const char *teks) {
    return (teks && teks[0] != '\0');
}

int isPositive(double angka) {
    return angka > 0.0;
}

int isUniquePos(const char *nama, PosAnggaran *arrayPos, int jumlahPos) {
    for (int i = 0; i < jumlahPos; ++i) {
        if (strcmp(arrayPos[i].namaPos, nama) == 0) return 0;
    }
    return 1;
}

int isValidJenisTransaksi(const char *jenis) {
    return (strcmp(jenis, "Pemasukan") == 0 || strcmp(jenis, "Pengeluaran") == 0);
}
