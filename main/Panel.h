#ifndef PANEL_H
#define PANEL_H

int
init_panel(void);

void
panel_clear(void);

void
panel_display_text(char*, unsigned);

void
panel_display_text_horizontal_scroll(char* text, unsigned length);

#endif