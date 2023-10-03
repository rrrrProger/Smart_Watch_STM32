#include "st7735.h"

void display_date_and_time();
void display_battery_status(int menu_context);
void display_move_pixel(struct point *point_a, uint16_t bg_color, uint16_t color, int pos_x, int pos_y);
void display_ground();
void display_man();
void display_menu();
void display_start_page();
void display_bar(int selected_item, int color, int sword_color);
void display_ateist_man();
void display_man_handshake(struct point hand[], int color, int width);
void display_sword(int x, int y, int color, int sword_color, int width);

#define ITEMS_NUMBER 2
