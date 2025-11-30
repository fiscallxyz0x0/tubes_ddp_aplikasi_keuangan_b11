/**
 * @file tui_menu.c
 * @brief Implementasi fungsi menu TUI
 */

#include <ncurses.h>
#include <string.h>
#include "../../include/tui/tui_menu.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/constants.h"

void menu_init(Menu *menu, const char *title) {
    if (!menu) return;
    memset(menu, 0, sizeof(Menu));
    if (title) strncpy(menu->title, title, MAX_MENU_TEXT - 1);
    menu->selected = 0;
    menu->start_y = 5;
    menu->start_x = 5;
}

int menu_add_item(Menu *menu, const char *text, int value) {
    if (!menu || !text || menu->item_count >= MAX_MENU_ITEMS) return 0;
    strncpy(menu->items[menu->item_count].text, text, MAX_MENU_TEXT - 1);
    menu->items[menu->item_count].value = value;
    menu->item_count++;
    return 1;
}

void menu_set_position(Menu *menu, int y, int x) {
    if (!menu) return;
    menu->start_y = y;
    menu->start_x = x;
}

void menu_display(Menu *menu) {
    if (!menu) return;
    int y = menu->start_y, x = menu->start_x;
    
    if (strlen(menu->title) > 0) {
        tui_bold_on();
        tui_color_on(COLOR_PAIR_CYAN);
        tui_print(y, x, menu->title);
        tui_color_off(COLOR_PAIR_CYAN);
        tui_bold_off();
        y += 2;
    }
    
    for (int i = 0; i < menu->item_count; i++) {
        if (i == menu->selected) {
            /* REV-4: Add arrow indicator + bold + color highlight for better visibility */
            tui_bold_on();
            tui_color_on(COLOR_PAIR_HIGHLIGHT);
            tui_printf(y + i, x, "> %d. %s  ", i + 1, menu->items[i].text);
            tui_color_off(COLOR_PAIR_HIGHLIGHT);
            tui_bold_off();
        } else {
            tui_printf(y + i, x, "  %d. %s  ", i + 1, menu->items[i].text);
        }
    }
}

void menu_display_center(Menu *menu) {
    if (!menu) return;
    int max_width = strlen(menu->title);
    for (int i = 0; i < menu->item_count; i++) {
        int len = strlen(menu->items[i].text) + 8;
        if (len > max_width) max_width = len;
    }
    int x = (tui_get_width() - max_width) / 2;
    int y = (tui_get_height() - menu->item_count - 4) / 2;
    if (x < 2) x = 2;
    if (y < 2) y = 2;
    menu_set_position(menu, y, x);
    menu_display(menu);
}

int menu_navigate(Menu *menu) {
    if (!menu || menu->item_count == 0) return -1;
    
    while (1) {
        tui_clear();
        display_header("APLIKASI KEUANGAN MAHASISWA");
        menu_display_center(menu);
        display_footer("UP/DOWN: Navigasi | ENTER: Pilih | ESC: Kembali");
        tui_refresh();
        
        int ch = tui_getch();
        switch (ch) {
            case KEY_UP: case 'k': case 'K':
                if (menu->selected > 0) menu->selected--;
                break;
            case KEY_DOWN: case 'j': case 'J':
                if (menu->selected < menu->item_count - 1) menu->selected++;
                break;
            case KEY_ENTER: case '\n': case '\r':
                return menu->items[menu->selected].value;
            case 27:
                return CANCEL;
            default:
                if (ch >= '1' && ch <= '9') {
                    int idx = ch - '1';
                    if (idx < menu->item_count) {
                        menu->selected = idx;
                        return menu->items[idx].value;
                    }
                }
                break;
        }
    }
}

int menu_get_selected_value(Menu *menu) {
    if (!menu || menu->item_count == 0) return -1;
    return menu->items[menu->selected].value;
}

void display_header(const char *title) {
    int width = tui_get_width();
    tui_color_on(COLOR_PAIR_CYAN);
    tui_draw_hline(0, 0, width, '=');
    tui_bold_on();
    tui_print_center(1, title);
    tui_bold_off();
    tui_draw_hline(2, 0, width, '=');
    tui_color_off(COLOR_PAIR_CYAN);
}

void display_footer(const char *instructions) {
    int h = tui_get_height(), w = tui_get_width();
    tui_color_on(COLOR_PAIR_CYAN);
    tui_draw_hline(h - 2, 0, w, '-');
    if (instructions) tui_print_center(h - 1, instructions);
    tui_color_off(COLOR_PAIR_CYAN);
}
