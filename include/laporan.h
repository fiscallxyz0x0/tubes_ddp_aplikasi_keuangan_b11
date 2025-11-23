#ifndef LAPORAN_H
#define LAPORAN_H

// Menggunakan string tetap untuk memudahkan I/O teks
typedef struct {
    int kodePos;                 // Kode numerik internal (unik)
    char namaPos[64];            // Nama kategori pos anggaran
    double batasNominal;         // Batas anggaran untuk pos
} PosAnggaran;

typedef struct {
    char kodeTransaksi[8];       // Format: T001, T002, ...
    char tanggal[16];            // Format bebas: YYYY-MM-DD disarankan
    char jenis[16];              // "Pemasukan" atau "Pengeluaran"
    char kategori[64];           // Nama pos anggaran terkait
    double nominal;              // Nilai uang
    char deskripsi[128];         // Catatan singkat
} Transaksi;

void tampilkanSemuaTransaksi(Transaksi *arrayTrx, int jumlahTrx);
void tampilkanTransaksiPemasukan(Transaksi *arrayTrx, int jumlahTrx);
void tampilkanTransaksiPengeluaran(Transaksi *arrayTrx, int jumlahTrx);
void tampilkanRekapitulasi(Transaksi *arrayTrx, int jumlahTrx);
void tampilkanRealisasiPosAnggaran(PosAnggaran *arrayPos, int jumlahPos, Transaksi *arrayTrx, int jumlahTrx);
void tampilkanAnalisisKondisi(double saldo);
void tampilkanKesimpulanMahasiswa(double totalPemasukan, double saldo);

#endif
