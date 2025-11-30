/**
 * @file app_menu.h
 * @brief Header untuk menu utama aplikasi
 * @author Kelompok B11
 * @date 2025
 */

#ifndef APP_MENU_H
#define APP_MENU_H

/**
 * @brief Tampilkan splash screen aplikasi
 */
void tampilkan_splash_screen(void);

/**
 * @brief Tampilkan menu utama aplikasi
 * @return Kode aksi yang dipilih
 */
int menu_utama(void);

/**
 * @brief Tampilkan menu pilih bulan global
 * @param bulan_saat_ini Bulan yang aktif saat ini
 * @return Bulan yang dipilih
 */
int pilih_bulan_global(int bulan_saat_ini);

/**
 * @brief Jalankan aplikasi utama
 */
void run_aplikasi(void);

/**
 * @brief Tampilkan tentang aplikasi
 */
void tampilkan_tentang(void);

/**
 * @brief Tampilkan bantuan penggunaan
 */
void tampilkan_bantuan(void);

#endif /* APP_MENU_H */
