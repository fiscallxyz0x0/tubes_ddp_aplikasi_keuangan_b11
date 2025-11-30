/**
 * @file tui_color.h
 * @brief Header untuk fungsi manajemen warna TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_COLOR_H
#define TUI_COLOR_H

#include <ncurses.h>

void tui_init_colors(void);
void tui_color_on(int pair_id);
void tui_color_off(int pair_id);
void tui_bold_on(void);
void tui_bold_off(void);
void tui_reverse_on(void);
void tui_reverse_off(void);
void tui_underline_on(void);
void tui_underline_off(void);
void tui_print_colored(int y, int x, int pair_id, const char *text);
void tui_print_center_colored(int y, int pair_id, const char *text);
void tui_attr_reset(void);

#endif /* TUI_COLOR_H */
