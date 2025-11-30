/**
 * @file tui_input.h
 * @brief Header untuk fungsi input TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_INPUT_H
#define TUI_INPUT_H

int input_string(int y, int x, const char *prompt, char *buffer, int max_len);
int input_string_required(int y, int x, const char *prompt, char *buffer, int max_len);
int input_number(int y, int x, const char *prompt, unsigned long long *result);
int input_number_min(int y, int x, const char *prompt, unsigned long long *result, unsigned long long min);
int input_tanggal(int y, int x, const char *prompt, char *buffer);
int input_konfirmasi(int y, int x, const char *prompt);
int input_pilihan(int y, int x, const char *prompt, int max);
int input_bulan(int y, int x, const char *prompt, int *result);
int input_jenis_transaksi(int y, int x, int *result);
void clear_input_line(int y);

#endif /* TUI_INPUT_H */
