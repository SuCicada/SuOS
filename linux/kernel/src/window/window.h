//
// Created by SuCicada on 2023/06/19.
//

#ifndef SUOS_WINDOW_H
#define SUOS_WINDOW_H
SHEET *create_background_sheet(SHTCTL *shtctl);
SHEET *create_mouse_sheet(SHTCTL *shtctl);
SHEET *create_window8_sheet(SHTCTL *shtctl);

void init_screen(unsigned char *buf, int xsize, int ysize);

#endif //SUOS_WINDOW_H
