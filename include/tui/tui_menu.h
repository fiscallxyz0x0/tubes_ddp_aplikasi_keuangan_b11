/**
 * @file tui_menu.h
 * @brief Header untuk fungsi menu TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_MENU_H
#define TUI_MENU_H

#define MAX_MENU_ITEMS 20
#define MAX_MENU_TEXT 50

typedef struct {
    char text[MAX_MENU_TEXT];
    int value;
} MenuItem;

typedef struct {
    char title[MAX_MENU_TEXT];
    MenuItem items[MAX_MENU_ITEMS];
    int item_count;
    int selected;
    int start_y;
    int start_x;
} Menu;

void menu_init(Menu *menu, const char *title);
int menu_add_item(Menu *menu, const char *text, int value);
void menu_set_position(Menu *menu, int y, int x);
void menu_display(Menu *menu);
void menu_display_center(Menu *menu);
int menu_navigate(Menu *menu);
int menu_get_selected_value(Menu *menu);
void display_header(const char *title);
void display_footer(const char *instructions);

#endif /* TUI_MENU_H */
