/**
 * @file tui_core.c
 * @brief Implementasi fungsi core TUI (ncurses)
 */

#include <ncurses.h>
#include <stdarg.h>
#include <string.h>
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"

int tui_init(void) {
    if (initscr() == NULL) return 0;
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    if (has_colors()) {
        start_color();
        tui_init_colors();
    }
    return 1;
}

void tui_cleanup(void) { curs_set(1); endwin(); }
void tui_clear(void) { clear(); }
void tui_refresh(void) { refresh(); }
int tui_get_width(void) { return COLS; }
int tui_get_height(void) { return LINES; }

void tui_print(int y, int x, const char *text) {
    if (text) mvprintw(y, x, "%s", text);
}

void tui_printf(int y, int x, const char *fmt, ...) {
    if (!fmt) return;
    va_list args;
    va_start(args, fmt);
    move(y, x);
    vw_printw(stdscr, fmt, args);
    va_end(args);
}

void tui_print_center(int y, const char *text) {
    if (!text) return;
    int x = (COLS - (int)strlen(text)) / 2;
    if (x < 0) x = 0;
    mvprintw(y, x, "%s", text);
}

void tui_draw_hline(int y, int x, int length, char ch) {
    if (ch == 0) ch = '-';
    move(y, x);
    for (int i = 0; i < length; i++) addch(ch);
}

void tui_draw_box(int y, int x, int height, int width) {
    mvaddch(y, x, ACS_ULCORNER);
    for (int i = 1; i < width - 1; i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);
    for (int i = 1; i < height - 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + width - 1, ACS_VLINE);
    }
    mvaddch(y + height - 1, x, ACS_LLCORNER);
    for (int i = 1; i < width - 1; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);
}

int tui_getch(void) { return getch(); }
void tui_cursor(int visible) { curs_set(visible ? 1 : 0); }
void tui_move(int y, int x) { move(y, x); }

void tui_pause(int y) {
    tui_print_center(y, "Tekan sembarang tombol untuk melanjutkan...");
    tui_refresh();
    tui_getch();
}
