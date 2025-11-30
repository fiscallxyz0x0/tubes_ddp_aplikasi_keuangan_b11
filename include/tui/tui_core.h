/**
 * @file tui_core.h
 * @brief Header untuk fungsi core TUI (ncurses)
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_CORE_H
#define TUI_CORE_H

#include <ncurses.h>

int tui_init(void);
void tui_cleanup(void);
void tui_clear(void);
void tui_refresh(void);
int tui_get_width(void);
int tui_get_height(void);
void tui_print(int y, int x, const char *text);
void tui_printf(int y, int x, const char *fmt, ...);
void tui_print_center(int y, const char *text);
void tui_draw_hline(int y, int x, int length, char ch);
void tui_draw_box(int y, int x, int height, int width);
int tui_getch(void);
void tui_cursor(int visible);
void tui_move(int y, int x);
void tui_pause(int y);

#endif /* TUI_CORE_H */
