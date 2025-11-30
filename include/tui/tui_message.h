/**
 * @file tui_message.h
 * @brief Header untuk fungsi message/dialog TUI
 * @author Kelompok B11
 * @date 2025
 */

#ifndef TUI_MESSAGE_H
#define TUI_MESSAGE_H

void show_info(const char *fmt, ...);
void show_success(const char *fmt, ...);
void show_error(const char *fmt, ...);
void show_warning(const char *fmt, ...);
int show_confirm(const char *message);
void show_message_box(const char *title, const char *message, int color_pair);
void show_status(const char *message);
void show_loading(const char *message);
void clear_message_area(void);

#endif /* TUI_MESSAGE_H */
