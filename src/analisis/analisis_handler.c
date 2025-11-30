/**
 * @file analisis_handler.c
 * @brief Implementasi handler utama modul analisis keuangan
 */

#include <stdio.h>
#include "../../include/analisis/analisis_handler.h"
#include "../../include/analisis/analisis_display.h"
#include "../../include/analisis/analisis_calc.h"
#include "../../include/tui/tui_menu.h"
#include "../../include/tui/tui_message.h"
#include "../../include/pos/pos_menu.h"
#include "../../include/utils/utils_bulan.h"
#include "../../include/constants.h"

#define ACT_LIHAT       1
#define ACT_REFRESH     2
#define ACT_GANTI_BULAN 3
#define ACT_KEMBALI     0

int menu_analisis_utama(int bulan) {
    char title[64];
    snprintf(title, sizeof(title), "Menu Analisis - %s", get_nama_bulan(bulan));

    Menu menu;
    menu_init(&menu, title);

    menu_add_item(&menu, "Lihat Analisis Keuangan", ACT_LIHAT);
    menu_add_item(&menu, "Refresh Analisis", ACT_REFRESH);
    /* REV-2 & REV-6: Removed "Ganti Bulan" and "Kembali" - use ESC to go back */

    return menu_navigate(&menu);
}

void run_analisis_module(int bulan_awal) {
    int bulan = bulan_awal;

    while (1) {
        int action = menu_analisis_utama(bulan);

        switch (action) {
            case ACT_LIHAT:
                tampilkan_analisis_bulan(bulan);
                break;

            case ACT_REFRESH:
                if (refresh_analisis_bulan(bulan)) {
                    show_success("Analisis berhasil diperbarui");
                } else {
                    show_error("Gagal memperbarui analisis");
                }
                break;

            /* REV-6: Removed ACT_GANTI_BULAN case */

            case ACT_KEMBALI:
            case CANCEL:
                return;
        }
    }
}
