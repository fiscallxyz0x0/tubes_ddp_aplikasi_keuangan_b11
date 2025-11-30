/**
 * @file tui_table.c
 * @brief Implementasi fungsi table display TUI
 */

#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "../../include/tui/tui_table.h"
#include "../../include/tui/tui_core.h"
#include "../../include/tui/tui_color.h"
#include "../../include/utils/utils_number.h"
#include "../../include/file/file_parser.h"
#include "../../include/constants.h"

void table_init(Table *table) {
    if (!table) return;
    memset(table, 0, sizeof(Table));
    table->start_y = 4;
    table->start_x = 2;
}

int table_add_column(Table *table, const char *header, int width, int align) {
    if (!table || !header || table->col_count >= MAX_TABLE_COLS) return 0;
    strncpy(table->columns[table->col_count].header, header, MAX_COL_WIDTH - 1);
    table->columns[table->col_count].width = width;
    table->columns[table->col_count].align = align;
    table->col_count++;
    return 1;
}

void table_set_position(Table *table, int y, int x) {
    if (!table) return;
    table->start_y = y;
    table->start_x = x;
}

int table_draw_header(Table *table) {
    if (!table) return 0;
    int x = table->start_x;
    int y = table->start_y;
    
    tui_bold_on();
    tui_color_on(COLOR_PAIR_CYAN);
    for (int i = 0; i < table->col_count; i++) {
        mvprintw(y, x, "%-*s", table->columns[i].width, table->columns[i].header);
        x += table->columns[i].width + 1;
    }
    tui_color_off(COLOR_PAIR_CYAN);
    tui_bold_off();
    
    y++;
    table_draw_separator(table, y);
    
    return y + 1;
}

void table_draw_row(Table *table, int row, int selected, const char **values) {
    if (!table || !values) return;
    int x = table->start_x;
    int y = table->start_y + 2 + row;
    
    if (selected) {
        tui_reverse_on();
        tui_color_on(COLOR_PAIR_HIGHLIGHT);
    }
    
    for (int i = 0; i < table->col_count; i++) {
        int w = table->columns[i].width;
        const char *val = values[i] ? values[i] : "";
        
        switch (table->columns[i].align) {
            case ALIGN_RIGHT:
                mvprintw(y, x, "%*s", w, val);
                break;
            case ALIGN_CENTER: {
                int pad = (w - (int)strlen(val)) / 2;
                if (pad < 0) pad = 0;
                mvprintw(y, x + pad, "%-*s", w - pad, val);
                break;
            }
            default:
                mvprintw(y, x, "%-*s", w, val);
                break;
        }
        x += w + 1;
    }
    
    if (selected) {
        tui_color_off(COLOR_PAIR_HIGHLIGHT);
        tui_reverse_off();
    }
}

void table_draw_separator(Table *table, int y) {
    if (!table) return;
    int total_width = 0;
    for (int i = 0; i < table->col_count; i++) {
        total_width += table->columns[i].width + 1;
    }
    tui_draw_hline(y, table->start_x, total_width - 1, '-');
}

int display_transaksi_table(Transaksi *list, int count, int start_y, int selected) {
    Table table;
    table_init(&table);
    table_set_position(&table, start_y, 2);
    
    table_add_column(&table, "No", 4, ALIGN_RIGHT);
    table_add_column(&table, "ID", 6, ALIGN_LEFT);
    table_add_column(&table, "Tanggal", 12, ALIGN_CENTER);
    table_add_column(&table, "Jenis", 12, ALIGN_LEFT);
    table_add_column(&table, "Pos", 15, ALIGN_LEFT);
    table_add_column(&table, "Nominal", 15, ALIGN_RIGHT);
    table_add_column(&table, "Deskripsi", 20, ALIGN_LEFT);
    
    int row_y = table_draw_header(&table);
    
    if (count == 0) {
        tui_print(row_y, 4, "(Tidak ada transaksi)");
        return row_y + 2;
    }
    
    char no_str[16], nominal_str[30];
    const char *values[7];
    
    for (int i = 0; i < count; i++) {
        snprintf(no_str, sizeof(no_str), "%d", i + 1);
        format_rupiah(list[i].nominal, nominal_str);
        
        values[0] = no_str;
        values[1] = list[i].id;
        values[2] = list[i].tanggal;
        values[3] = get_label_jenis(list[i].jenis);
        values[4] = list[i].pos;
        values[5] = nominal_str;
        values[6] = list[i].deskripsi;
        
        table_draw_row(&table, i, (i == selected), values);
    }
    
    return row_y + count + 1;
}

int display_pos_table(PosAnggaran *list, int count, int start_y, int selected) {
    Table table;
    table_init(&table);
    table_set_position(&table, start_y, 2);
    
    table_add_column(&table, "No", 4, ALIGN_RIGHT);
    table_add_column(&table, "Nama Pos", 20, ALIGN_LEFT);
    table_add_column(&table, "Anggaran", 15, ALIGN_RIGHT);
    table_add_column(&table, "Realisasi", 15, ALIGN_RIGHT);
    table_add_column(&table, "Sisa", 15, ALIGN_RIGHT);
    table_add_column(&table, "Status", 12, ALIGN_CENTER);
    
    int row_y = table_draw_header(&table);
    
    if (count == 0) {
        tui_print(row_y, 4, "(Tidak ada pos anggaran)");
        return row_y + 2;
    }
    
    char no_str[16], anggaran_str[30], realisasi_str[30], sisa_str[30];
    const char *values[6];
    
    for (int i = 0; i < count; i++) {
        snprintf(no_str, sizeof(no_str), "%d", list[i].no);
        format_rupiah(list[i].nominal, anggaran_str);
        format_rupiah(list[i].realisasi, realisasi_str);
        format_saldo(list[i].sisa, sisa_str);
        
        values[0] = no_str;
        values[1] = list[i].nama;
        values[2] = anggaran_str;
        values[3] = realisasi_str;
        values[4] = sisa_str;
        values[5] = (list[i].status == STATUS_AMAN) ? "Aman" : "Tidak Aman";
        
        table_draw_row(&table, i, (i == selected), values);
    }
    
    return row_y + count + 1;
}
