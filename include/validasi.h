#ifndef VALIDASI_H
#define VALIDASI_H

typedef struct PosAnggaran PosAnggaran;
typedef struct Transaksi Transaksi;

int isPositive(double angka);
int isNotEmpty(const char *teks);
int isUniquePos(const char *nama, PosAnggaran *arrayPos, int jumlahPos);
int isValidJenisTransaksi(const char *jenis);

#endif
