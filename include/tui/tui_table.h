/**
 * @file tui_table.h
 * @brief Header untuk fungsi table display TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_TABLE_H
#define TUI_TABLE_H

#include "../types.h"

#define MAX_TABLE_COLS 10
#define MAX_COL_WIDTH 30

#define ALIGN_LEFT   0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT  2

typedef struct {
    char header[MAX_COL_WIDTH];
    int width;
    int align;
} TableColumn;

typedef struct {
    TableColumn columns[MAX_TABLE_COLS];
    int col_count;
    int start_y;
    int start_x;
} Table;

void table_init(Table *table);
int table_add_column(Table *table, const char *header, int width, int align);
void table_set_position(Table *table, int y, int x);
int table_draw_header(Table *table);
void table_draw_row(Table *table, int row, int selected, const char **values);
void table_draw_separator(Table *table, int y);
int display_transaksi_table(Transaksi *list, int count, int start_y, int selected);
int display_pos_table(PosAnggaran *list, int count, int start_y, int selected);

#endif /* TUI_TABLE_H */
