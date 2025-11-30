/**
 * @file tui_input.c
 * @brief Implementasi fungsi input TUI
 */

#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/tui/tui_input.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/tui/tui_message.h"
#include "../../include/validator/validator_string.h"
#include "../../include/validator/validator_number.h"
#include "../../include/validator/validator_date.h"
#include "../../include/constants.h"

void clear_input_line(int y) {
    move(y, 0);
    clrtoeol();
}

int input_string(int y, int x, const char *prompt, char *buffer, int max_len) {
    if (!buffer || max_len <= 0) return 0;
    tui_print(y, x, prompt);
    tui_cursor(1);
    
    int input_x = x + strlen(prompt);
    move(y, input_x);
    
    char temp[256];
    memset(temp, 0, sizeof(temp));
    int pos = 0, ch;
    
    while (1) {
        ch = getch();
        if (ch == 27) { tui_cursor(0); buffer[0] = '\0'; return 0; }
        if (ch == '\n' || ch == '\r' || ch == KEY_ENTER) break;
        if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (pos > 0) { pos--; temp[pos] = '\0'; mvaddch(y, input_x + pos, ' '); move(y, input_x + pos); }
        } else if (isprint(ch) && pos < max_len - 1 && pos < 254) {
            temp[pos] = ch; mvaddch(y, input_x + pos, ch); pos++; temp[pos] = '\0';
        }
        refresh();
    }
    tui_cursor(0);
    
    strncpy(buffer, temp, max_len - 1);
    buffer[max_len - 1] = '\0';
    
    /* Trim */
    char *start = buffer;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != buffer) memmove(buffer, start, strlen(start) + 1);
    char *end = buffer + strlen(buffer) - 1;
    while (end > buffer && isspace((unsigned char)*end)) { *end = '\0'; end--; }
    
    return 1;
}

int input_string_required(int y, int x, const char *prompt, char *buffer, int max_len) {
    while (1) {
        if (!input_string(y, x, prompt, buffer, max_len)) return 0;
        if (validasi_tidak_kosong(buffer)) return 1;
        show_error("Input tidak boleh kosong!");
        clear_input_line(y);
    }
}

int input_number(int y, int x, const char *prompt, unsigned long long *result) {
    char buffer[32];
    while (1) {
        if (!input_string(y, x, prompt, buffer, sizeof(buffer))) return 0;
        if (parse_nominal(buffer, result)) return 1;
        show_error("Input harus berupa angka positif!");
        clear_input_line(y);
    }
}

int input_number_min(int y, int x, const char *prompt, unsigned long long *result, unsigned long long min) {
    while (1) {
        if (!input_number(y, x, prompt, result)) return 0;
        if (*result >= min) return 1;
        show_error("Nilai harus minimal %llu!", min);
        clear_input_line(y);
    }
}

int input_tanggal(int y, int x, const char *prompt, char *buffer) {
    char full_prompt[128];
    snprintf(full_prompt, sizeof(full_prompt), "%s (dd-mm-YYYY): ", prompt);
    while (1) {
        if (!input_string(y, x, full_prompt, buffer, 11)) return 0;
        if (validasi_tanggal_lengkap(buffer)) return 1;
        show_error("Format tanggal tidak valid! Gunakan dd-mm-YYYY");
        clear_input_line(y);
    }
}

int input_konfirmasi(int y, int x, const char *prompt) {
    char full_prompt[128];
    snprintf(full_prompt, sizeof(full_prompt), "%s (y/n): ", prompt);
    tui_print(y, x, full_prompt);
    tui_refresh();
    while (1) {
        int ch = tui_getch();
        if (ch == 'y' || ch == 'Y') return 1;
        if (ch == 'n' || ch == 'N' || ch == 27) return 0;
    }
}

int input_pilihan(int y, int x, const char *prompt, int max) {
    char buffer[16], full_prompt[128];
    snprintf(full_prompt, sizeof(full_prompt), "%s (1-%d): ", prompt, max);
    while (1) {
        if (!input_string(y, x, full_prompt, buffer, sizeof(buffer))) return 0;
        int pilihan = atoi(buffer);
        if (validasi_pilihan_menu(pilihan, 1, max)) return pilihan;
        show_error("Pilihan tidak valid! Masukkan 1-%d", max);
        clear_input_line(y);
    }
}

int input_bulan(int y, int x, const char *prompt, int *result) {
    char buffer[16], full_prompt[128];
    snprintf(full_prompt, sizeof(full_prompt), "%s (1-12): ", prompt);
    while (1) {
        if (!input_string(y, x, full_prompt, buffer, sizeof(buffer))) return 0;
        int bulan = atoi(buffer);
        if (bulan >= BULAN_MIN && bulan <= BULAN_MAX) { *result = bulan; return 1; }
        show_error("Bulan tidak valid! Masukkan 1-12");
        clear_input_line(y);
    }
}

int input_jenis_transaksi(int y, int x, int *result) {
    tui_print(y, x, "Jenis: 1=Pengeluaran, 2=Pemasukan: ");
    tui_refresh();
    while (1) {
        int ch = tui_getch();
        if (ch == '1') { *result = JENIS_PENGELUARAN; return 1; }
        if (ch == '2') { *result = JENIS_PEMASUKAN; return 1; }
        if (ch == 27) return 0;
    }
}
