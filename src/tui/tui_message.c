/**
 * @file tui_message.c
 * @brief Implementasi fungsi message/dialog TUI
 */

#include <ncurses.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "../../include/tui/tui_message.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/constants.h"

#define MSG_LINE (LINES - 4)

static void show_message_colored(int color_pair, const char *prefix, const char *fmt, va_list args) {
    char buffer[256], full_msg[300];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    snprintf(full_msg, sizeof(full_msg), "%s%s", prefix, buffer);
    move(MSG_LINE, 0);
    clrtoeol();
    tui_color_on(color_pair);
    tui_print_center(MSG_LINE, full_msg);
    tui_color_off(color_pair);
    tui_refresh();
    tui_getch();
    move(MSG_LINE, 0);
    clrtoeol();
}

void show_info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    show_message_colored(COLOR_PAIR_CYAN, "[INFO] ", fmt, args);
    va_end(args);
}

void show_success(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    show_message_colored(COLOR_PAIR_GREEN, "[OK] ", fmt, args);
    va_end(args);
}

void show_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    show_message_colored(COLOR_PAIR_RED, "[ERROR] ", fmt, args);
    va_end(args);
}

void show_warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    show_message_colored(COLOR_PAIR_YELLOW, "[WARNING] ", fmt, args);
    va_end(args);
}

int show_confirm(const char *message) {
    char full_msg[256];
    snprintf(full_msg, sizeof(full_msg), "%s (y/n)", message);
    move(MSG_LINE, 0);
    clrtoeol();
    tui_color_on(COLOR_PAIR_YELLOW);
    tui_print_center(MSG_LINE, full_msg);
    tui_color_off(COLOR_PAIR_YELLOW);
    tui_refresh();
    while (1) {
        int ch = tui_getch();
        if (ch == 'y' || ch == 'Y') { move(MSG_LINE, 0); clrtoeol(); return 1; }
        if (ch == 'n' || ch == 'N' || ch == 27) { move(MSG_LINE, 0); clrtoeol(); return 0; }
    }
}

void show_message_box(const char *title, const char *message, int color_pair) {
    int msg_len = strlen(message);
    int title_len = title ? (int)strlen(title) : 0;
    int width = (msg_len > title_len ? msg_len : title_len) + 6;
    int height = 5;
    int x = (COLS - width) / 2, y = (LINES - height) / 2;
    if (x < 1) x = 1;
    if (y < 1) y = 1;
    tui_color_on(color_pair);
    tui_draw_box(y, x, height, width);
    if (title) { tui_bold_on(); tui_print(y, x + 2, title); tui_bold_off(); }
    tui_print(y + 2, x + 3, message);
    tui_color_off(color_pair);
    tui_refresh();
    tui_getch();
}

void show_status(const char *message) {
    if (!message) return;
    move(LINES - 3, 0);
    clrtoeol();
    tui_color_on(COLOR_PAIR_CYAN);
    mvprintw(LINES - 3, 2, "%s", message);
    tui_color_off(COLOR_PAIR_CYAN);
    tui_refresh();
}

void show_loading(const char *message) {
    if (!message) return;
    move(MSG_LINE, 0);
    clrtoeol();
    tui_color_on(COLOR_PAIR_YELLOW);
    tui_print_center(MSG_LINE, message);
    tui_color_off(COLOR_PAIR_YELLOW);
    tui_refresh();
}

void clear_message_area(void) {
    move(MSG_LINE, 0);
    clrtoeol();
    tui_refresh();
}
