#ifndef TRANSAKSI_H
#define TRANSAKSI_H

typedef struct PosAnggaran PosAnggaran;
typedef struct Transaksi Transaksi;

Transaksi inputTransaksi(void);
int validasiTransaksi(const Transaksi *trx, PosAnggaran *arrayPos, int jumlahPos);
void generateKodeTransaksi(char *outKode, int nomorBerikutnya);
int simpanTransaksi(const Transaksi *trx, const char *namaFile);

#endif
