#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <operasi_file.h>

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

// Menambahkan satu baris ke akhir file teks
int tulisFile(const char *namaFile, const char *baris) {
    FILE *f = fopen(namaFile, "a");
    if (!f) return 0;
    fprintf(f, "%s\n", baris);
    fclose(f);
    return 1;
}

// Membaca seluruh isi file ke buffer (untuk kasus sederhana)
// Mengembalikan jumlah karakter yang terbaca
int bacaFile(const char *namaFile, char *buffer, int ukuranBuffer) {
    FILE *f = fopen(namaFile, "r");
    if (!f) {
        // Jika belum ada, buat file kosong
        f = fopen(namaFile, "w");
        if (!f) return 0;
        fclose(f);
        buffer[0] = '\0';
        return 0;
    }
    int total = fread(buffer, 1, ukuranBuffer - 1, f);
    buffer[total] = '\0';
    fclose(f);
    return total;
}

// Menulis seluruh transaksi ke file dengan format: ID|Tanggal|Jenis|Kategori|Nominal|Deskripsi
int simpanTransaksiKeFile(Transaksi *arrayTransaksi, int jumlah, const char *namaFile) {
    FILE *f = fopen(namaFile, "w");
    if (!f) return 0;
    for (int i = 0; i < jumlah; ++i) {
        fprintf(f, "%s|%s|%s|%s|%.2f|%s\n",
            arrayTransaksi[i].kodeTransaksi,
            arrayTransaksi[i].tanggal,
            arrayTransaksi[i].jenis,
            arrayTransaksi[i].kategori,
            arrayTransaksi[i].nominal,
            arrayTransaksi[i].deskripsi
        );
    }
    fclose(f);
    return 1;
}

int bacaTransaksiDariFile(Transaksi *arrayTransaksi, int kapasitas, const char *namaFile) {
    FILE *f = fopen(namaFile, "r");
    if (!f) {
        f = fopen(namaFile, "w");
        if (!f) return 0;
        fclose(f);
        return 0;
    }

    int hitung = 0;
    char baris[512];
    while (fgets(baris, sizeof(baris), f) && hitung < kapasitas) {
        // Parsel format ID|Tanggal|Jenis|Kategori|Nominal|Deskripsi
        // Gunakan strtok untuk memisahkan
        char *token = strtok(baris, "|");
        if (!token) continue;
        strncpy(arrayTransaksi[hitung].kodeTransaksi, token, sizeof(arrayTransaksi[hitung].kodeTransaksi) - 1);
        arrayTransaksi[hitung].kodeTransaksi[sizeof(arrayTransaksi[hitung].kodeTransaksi) - 1] = '\0';
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(arrayTransaksi[hitung].tanggal, token, sizeof(arrayTransaksi[hitung].tanggal) - 1);
        arrayTransaksi[hitung].tanggal[sizeof(arrayTransaksi[hitung].tanggal) - 1] = '\0';
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(arrayTransaksi[hitung].jenis, token, sizeof(arrayTransaksi[hitung].jenis) - 1);
        arrayTransaksi[hitung].jenis[sizeof(arrayTransaksi[hitung].jenis) - 1] = '\0';
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(arrayTransaksi[hitung].kategori, token, sizeof(arrayTransaksi[hitung].kategori) - 1);
        arrayTransaksi[hitung].kategori[sizeof(arrayTransaksi[hitung].kategori) - 1] = '\0';
        token = strtok(NULL, "|");
        if (!token) continue;
        arrayTransaksi[hitung].nominal = atof(token);
        token = strtok(NULL, "\n");
        if (!token) token = "";
        strncpy(arrayTransaksi[hitung].deskripsi, token, sizeof(arrayTransaksi[hitung].deskripsi) - 1);
        arrayTransaksi[hitung].deskripsi[sizeof(arrayTransaksi[hitung].deskripsi) - 1] = '\0';

        // Trim newline di field string jika ada
        for (char *p = arrayTransaksi[hitung].kodeTransaksi; *p; ++p) if (*p == '\n') *p = '\0';
        for (char *p = arrayTransaksi[hitung].tanggal; *p; ++p) if (*p == '\n') *p = '\0';
        for (char *p = arrayTransaksi[hitung].jenis; *p; ++p) if (*p == '\n') *p = '\0';
        for (char *p = arrayTransaksi[hitung].kategori; *p; ++p) if (*p == '\n') *p = '\0';
        for (char *p = arrayTransaksi[hitung].deskripsi; *p; ++p) if (*p == '\n') *p = '\0';

        hitung++;
    }
    fclose(f);
    return hitung;
}
