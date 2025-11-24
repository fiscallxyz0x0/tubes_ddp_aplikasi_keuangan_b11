#include <stdio.h>
#include <string.h>
#include <validasi.h>
#include <pos_anggaran.h>

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

// Edit data pos di array
int editPosAnggaran(int kodePos, const char *namaBaru, double batasBaru, PosAnggaran *arrayPos, int jumlahPos) {
    for (int i = 0; i < jumlahPos; ++i) {
        if (arrayPos[i].kodePos == kodePos) {
            strncpy(arrayPos[i].namaPos, namaBaru, sizeof(arrayPos[i].namaPos) - 1);
            arrayPos[i].namaPos[sizeof(arrayPos[i].namaPos) - 1] = '\0';
            arrayPos[i].batasNominal = batasBaru;
            return 1;
        }
    }
    return 0;
}

// Menghapus pos dari array (geser elemen), mengubah jumlahPos
int hapusPosAnggaran(int kodePos, PosAnggaran *arrayPos, int *jumlahPos) {
    int idx = -1;
    for (int i = 0; i < *jumlahPos; ++i) {
        if (arrayPos[i].kodePos == kodePos) { idx = i; break; }
    }
    if (idx == -1) return 0;

    for (int j = idx; j < *jumlahPos - 1; ++j) {
        arrayPos[j] = arrayPos[j + 1];
    }
    (*jumlahPos)--;
    return 1;
}

// Menerima input nama pos dan batas nominal
PosAnggaran inputPosAnggaran(void) {
    PosAnggaran pos;
    char nama[64];
    double batas;

    printf("Masukkan nama pos anggaran: ");
    fgets(nama, sizeof(nama), stdin);
    // Hapus newline
    nama[strcspn(nama, "\n")] = '\0';

    printf("Masukkan batas nominal: ");
    scanf("%lf", &batas);
    getchar(); // konsumsi newline sisa

    pos.kodePos = -1; // akan diisi kemudian saat ditambahkan ke array
    strncpy(pos.namaPos, nama, sizeof(pos.namaPos));
    pos.batasNominal = batas;

    return pos;
}

// Menulis data pos ke file pos_anggaran.txt (format sederhana: kode|nama|batas)
int simpanPosAnggaran(PosAnggaran pos, const char *namaFile) {
    FILE *f = fopen(namaFile, "a");
    if (!f) return 0;
    fprintf(f, "%d|%s|%.2f\n", pos.kodePos, pos.namaPos, pos.batasNominal);
    fclose(f);
    return 1;
}

// Menulis ulang seluruh array pos ke file (sinkronisasi setelah edit/hapus)
int updateFilePosAnggaran(PosAnggaran *arrayPos, int jumlahPos, const char *namaFile) {
    FILE *f = fopen(namaFile, "w");
    if (!f) return 0;
    for (int i = 0; i < jumlahPos; ++i) {
        fprintf(f, "%d|%s|%.2f\n", arrayPos[i].kodePos, arrayPos[i].namaPos, arrayPos[i].batasNominal);
    }
    fclose(f);
    return 1;
}

// Nama baru tidak boleh duplikat (kecuali kalau tetap pada pos yg sama), batas > 0
int validasiEditPos(const char *namaBaru, double batasBaru, PosAnggaran *arrayPos, int jumlahPos, int kodePos) {
    if (!isNotEmpty(namaBaru)) return 0;
    if (!isPositive(batasBaru)) return 0;
    // Cek duplikasi nama selain dirinya
    for (int i = 0; i < jumlahPos; ++i) {
        if (arrayPos[i].kodePos != kodePos && strcmp(arrayPos[i].namaPos, namaBaru) == 0) {
            return 0;
        }
    }
    return 1;
}

int validasiHapusPos(int kodePos, PosAnggaran *arrayPos, int jumlahPos) {
    for (int i = 0; i < jumlahPos; ++i) {
        if (arrayPos[i].kodePos == kodePos) return 1;
    }
    return 0;
}

// Pastikan nama unik dan batas > 0
int validasiPosAnggaran(const char *nama, double batas, PosAnggaran *arrayPos, int jumlahPos) {
    if (!isNotEmpty(nama)) return 0;
    if (!isPositive(batas)) return 0;
    if (!isUniquePos(nama, arrayPos, jumlahPos)) return 0;
    return 1;
}
