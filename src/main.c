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

#include <stdio.h>
#include <string.h>
#include <operasi_file.h>
#include <tampilan.h>
#include <pos_anggaran.h>
#include <transaksi.h>
#include <laporan.h>
#include <perhitungan.h>

#define FILE_POS "data/pos_anggaran.txt"
#define FILE_TRX "data/data_keuangan.txt"
#define NILAI_MAKS_POS 200
#define NILAI_MAKS_TRANSAKSI 1000

int maks_pos = NILAI_MAKS_POS;
int maks_transaksi = NILAI_MAKS_TRANSAKSI;

int main() {
    PosAnggaran arrayPos[maks_pos];
    int jumlahPos = 0;
    Transaksi arrayTrx[maks_transaksi];
    int jumlahTrx = 0;
    int nomorTrxBerikutnya = 1;

    // Muat transaksi dari file pada awal
    jumlahTrx = bacaTransaksiDariFile(arrayTrx, maks_transaksi, FILE_TRX);
    nomorTrxBerikutnya = jumlahTrx + 1;

    // Muat pos anggaran dari file (opsional sederhana)
    // Format: kode|nama|batas
    {
        FILE *f = fopen(FILE_POS, "r");
        if (f) {
            char baris[256];
            while (fgets(baris, sizeof(baris), f) && jumlahPos < maks_pos) {
                int kode; char nama[64]; double batas;
                // Parsing sederhana
                if (sscanf(baris, "%d|%63[^|]|%lf", &kode, nama, &batas) == 3) {
                    arrayPos[jumlahPos].kodePos = kode;
                    strncpy(arrayPos[jumlahPos].namaPos, nama, sizeof(arrayPos[jumlahPos].namaPos));
                    arrayPos[jumlahPos].batasNominal = batas;
                    jumlahPos++;
                }
            }
            fclose(f);
        } else {
            // Buat file jika belum ada
            f = fopen(FILE_POS, "w");
            if (f) fclose(f);
        }
    }

    int pilih;
    do {
        tampilkanMenu();
        if (scanf("%d", &pilih) != 1) { getchar(); continue; }
        getchar(); // konsumsi newline

        switch (pilih) {
            case 1: {
                PosAnggaran pos = inputPosAnggaran();
                if (!validasiPosAnggaran(pos.namaPos, pos.batasNominal, arrayPos, jumlahPos)) {
                    tampilkanPesanError("Data pos tidak valid (nama unik & batas > 0).");
                    break;
                }
                pos.kodePos = (jumlahPos == 0) ? 1 : arrayPos[jumlahPos - 1].kodePos + 1;
                arrayPos[jumlahPos++] = pos;
                if (!simpanPosAnggaran(pos, FILE_POS)) {
                    tampilkanPesanError("Gagal menyimpan pos ke file.");
                } else {
                    tampilkanPesanSukses("Pos anggaran ditambahkan.");
                }
                break;
            }
            case 2: {
                int kode;
                printf("Masukkan kode pos yang akan dihapus: ");
                scanf("%d", &kode); getchar();
                if (!validasiHapusPos(kode, arrayPos, jumlahPos)) {
                    tampilkanPesanError("Kode pos tidak ditemukan.");
                    break;
                }
                if (!hapusPosAnggaran(kode, arrayPos, &jumlahPos)) {
                    tampilkanPesanError("Gagal menghapus pos.");
                    break;
                }
                if (!updateFilePosAnggaran(arrayPos, jumlahPos, FILE_POS)) {
                    tampilkanPesanError("Gagal memperbarui file pos.");
                } else {
                    tampilkanPesanSukses("Pos anggaran dihapus.");
                }
                break;
            }
            case 3: {
                int kode;
                char namaBaru[64];
                double batasBaru;
                printf("Masukkan kode pos yang akan diedit: ");
                scanf("%d", &kode);
                while (getchar() != '\n');  // buang newline dari buffer

                printf("Nama baru: ");
                fgets(namaBaru, sizeof(namaBaru), stdin);
                namaBaru[strcspn(namaBaru, "\n")] = '\0';  // hapus newline

                printf("Batas nominal baru: ");
                scanf("%lf", &batasBaru);

                if (!validasiEditPos(namaBaru, batasBaru, arrayPos, jumlahPos, kode)) {
                    tampilkanPesanError("Data edit tidak valid (nama unik & batas > 0).");
                    break;
                }
                if (!editPosAnggaran(kode, namaBaru, batasBaru, arrayPos, jumlahPos)) {
                    tampilkanPesanError("Kode pos tidak ditemukan.");
                    break;
                }
                if (!updateFilePosAnggaran(arrayPos, jumlahPos, FILE_POS)) {
                    tampilkanPesanError("Gagal memperbarui file pos.");
                } else {
                    tampilkanPesanSukses("Pos anggaran diperbarui.");
                }
                break;
            }
            case 4: {
                Transaksi trx = inputTransaksi();
                if (!validasiTransaksi(&trx, arrayPos, jumlahPos)) {
                    tampilkanPesanError("Transaksi tidak valid (jenis/besar/tanggal/pos).");
                    break;
                }
                generateKodeTransaksi(trx.kodeTransaksi, nomorTrxBerikutnya++);
                arrayTrx[jumlahTrx++] = trx;
                if (!simpanTransaksi(&trx, FILE_TRX)) {
                    tampilkanPesanError("Gagal menyimpan transaksi.");
                } else {
                    tampilkanPesanSukses("Transaksi ditambahkan.");
                }
                break;
            }
            case 5:
                tampilkanSemuaTransaksi(arrayTrx, jumlahTrx);
                break;
            case 6:
                tampilkanTransaksiPemasukan(arrayTrx, jumlahTrx);
                break;
            case 7:
                tampilkanTransaksiPengeluaran(arrayTrx, jumlahTrx);
                break;
            case 8:
                tampilkanRekapitulasi(arrayTrx, jumlahTrx);
                break;
            case 9:
                tampilkanRealisasiPosAnggaran(arrayPos, jumlahPos, arrayTrx, jumlahTrx);
                break;
            case 10:
                if (simpanTransaksiKeFile(arrayTrx, jumlahTrx, FILE_TRX))
                    tampilkanPesanSukses("Seluruh transaksi disimpan ulang ke file.");
                else
                    tampilkanPesanError("Gagal menulis ulang transaksi ke file.");
                break;
            case 0:
                printf("Terima kasih, sampai jumpa.\n");
                break;
            default:
                tampilkanPesanError("Menu tidak dikenal.");
        }
    } while (pilih != 0);

    return 0;
}
