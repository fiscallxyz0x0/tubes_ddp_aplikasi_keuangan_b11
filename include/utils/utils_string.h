/**
 * @file utils_string.h
 * @brief Header untuk fungsi utilitas manipulasi string
 * @author Kelompok B11
 * @date 2025
 * 
 * Menyediakan fungsi-fungsi pembantu untuk operasi string
 * seperti trim, uppercase, dan safe copy.
 */

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

/**
 * @brief Menghapus whitespace di awal dan akhir string
 * @param str String yang akan di-trim (dimodifikasi in-place)
 */
void str_trim(char *str);

/**
 * @brief Mengkonversi string ke uppercase
 * @param str String yang akan dikonversi (dimodifikasi in-place)
 */
void str_to_upper(char *str);

/**
 * @brief Mengkonversi string ke lowercase
 * @param str String yang akan dikonversi (dimodifikasi in-place)
 */
void str_to_lower(char *str);

/**
 * @brief Menyalin string dengan batasan ukuran (safe copy)
 * @param dst Buffer tujuan
 * @param src String sumber
 * @param max Ukuran maksimal buffer tujuan
 */
void str_copy_safe(char *dst, const char *src, int max);

/**
 * @brief Memisahkan string berdasarkan delimiter
 * @param str String yang akan dipisahkan
 * @param delim Karakter delimiter
 * @param result Array pointer untuk menyimpan hasil split
 * @param max_parts Jumlah maksimal bagian yang dihasilkan
 * @return Jumlah bagian yang dihasilkan
 */
int str_split(char *str, char delim, char **result, int max_parts);

/**
 * @brief Memeriksa apakah string kosong (hanya whitespace atau NULL)
 * @param str String yang diperiksa
 * @return 1 jika kosong, 0 jika tidak
 */
int str_is_empty(const char *str);

/**
 * @brief Membandingkan dua string secara case-insensitive
 * @param s1 String pertama
 * @param s2 String kedua
 * @return 0 jika sama, non-zero jika berbeda
 */
int str_compare_nocase(const char *s1, const char *s2);

/**
 * @brief Menghapus karakter newline dari akhir string
 * @param str String yang akan diproses (dimodifikasi in-place)
 */
void str_remove_newline(char *str);

#endif /* UTILS_STRING_H */
