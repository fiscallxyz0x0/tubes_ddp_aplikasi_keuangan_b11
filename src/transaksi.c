#include <stdio.h>
#include <string.h>
#include <transaksi.h>
#include <validasi.h>
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

// Membuat kode unik otomatis: T001, T002, ...
void generateKodeTransaksi(char *outKode, int nomorBerikutnya) {
    // Nomor berikutnya diasumsikan 1-based
    sprintf(outKode, "T%03d", nomorBerikutnya);
}

// Menerima input jenis, nominal, tanggal, pos/kategori, deskripsi
Transaksi inputTransaksi(void) {
    Transaksi trx;
    char jenis[16], tanggal[16], kategori[64], deskripsi[128];
    double nominal;

    printf("Masukkan tanggal (YYYY-MM-DD): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\n")] = '\0';

    printf("Jenis (Pemasukan/Pengeluaran): ");
    fgets(jenis, sizeof(jenis), stdin);
    jenis[strcspn(jenis, "\n")] = '\0';

    printf("Kategori/Pos Anggaran: ");
    fgets(kategori, sizeof(kategori), stdin);
    kategori[strcspn(kategori, "\n")] = '\0';

    printf("Nominal: ");
    scanf("%lf", &nominal);
    getchar(); // konsumsi newline

    printf("Deskripsi singkat: ");
    fgets(deskripsi, sizeof(deskripsi), stdin);
    deskripsi[strcspn(deskripsi, "\n")] = '\0';

    strncpy(trx.tanggal, tanggal, sizeof(trx.tanggal));
    strncpy(trx.jenis, jenis, sizeof(trx.jenis));
    strncpy(trx.kategori, kategori, sizeof(trx.kategori));
    trx.nominal = nominal;
    strncpy(trx.deskripsi, deskripsi, sizeof(trx.deskripsi));

    trx.kodeTransaksi[0] = '\0'; // akan diisi oleh generateKodeTransaksi
    return trx;
}

// Simpan satu transaksi secara append ke data_keuangan.txt
int simpanTransaksi(const Transaksi *trx, const char *namaFile) {
    FILE *f = fopen(namaFile, "a");
    if (!f) return 0;
    fprintf(f, "%s|%s|%s|%s|%.2f|%s\n",
        trx->kodeTransaksi, trx->tanggal, trx->jenis, trx->kategori, trx->nominal, trx->deskripsi);
    fclose(f);
    return 1;
}

// Cek jenis valid, nominal > 0, tanggal tidak kosong, pos ada di arrayPos
int validasiTransaksi(const Transaksi *trx, PosAnggaran *arrayPos, int jumlahPos) {
    if (!isNotEmpty(trx->tanggal)) return 0;
    if (!isValidJenisTransaksi(trx->jenis)) return 0;
    if (!isPositive(trx->nominal)) return 0;

    // Pos harus ada
    int adaPos = 0;
    for (int i = 0; i < jumlahPos; ++i) {
        if (strcmp(arrayPos[i].namaPos, trx->kategori) == 0) { adaPos = 1; break; }
    }
    return adaPos;
}
