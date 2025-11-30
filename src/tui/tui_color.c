/**
 * @file tui_color.c
 * @brief Implementasi fungsi manajemen warna TUI
 */

#include <ncurses.h>
#include <string.h>
#include "../../include/tui/tui_color.h"
#include "../../include/constants.h"

void tui_init_colors(void) {
    if (!has_colors()) return;
    init_pair(COLOR_PAIR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_PAIR_RED, COLOR_RED, COLOR_BLACK);
    /* REV-4: Improved highlight visibility - cyan background with black text */
    init_pair(COLOR_PAIR_HIGHLIGHT, COLOR_BLACK, COLOR_CYAN);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_PAIR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

void tui_color_on(int pair_id) { if (has_colors()) attron(COLOR_PAIR(pair_id)); }
void tui_color_off(int pair_id) { if (has_colors()) attroff(COLOR_PAIR(pair_id)); }
void tui_bold_on(void) { attron(A_BOLD); }
void tui_bold_off(void) { attroff(A_BOLD); }
void tui_reverse_on(void) { attron(A_REVERSE); }
void tui_reverse_off(void) { attroff(A_REVERSE); }
void tui_underline_on(void) { attron(A_UNDERLINE); }
void tui_underline_off(void) { attroff(A_UNDERLINE); }

void tui_print_colored(int y, int x, int pair_id, const char *text) {
    if (!text) return;
    tui_color_on(pair_id);
    mvprintw(y, x, "%s", text);
    tui_color_off(pair_id);
}

void tui_print_center_colored(int y, int pair_id, const char *text) {
    if (!text) return;
    int len = strlen(text);
    int x = (COLS - len) / 2;
    if (x < 0) x = 0;
    tui_color_on(pair_id);
    mvprintw(y, x, "%s", text);
    tui_color_off(pair_id);
}

void tui_attr_reset(void) { attrset(A_NORMAL); }
