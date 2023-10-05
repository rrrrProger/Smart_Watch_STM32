#include "st7735.h"

struct global {
	int leg_start_x;
	int leg_start_y;
	int leg_width;
	int leg_length;
	int body_length;
	int hand_width;
	int hand_length;
	int neck_length;
	int head_radius;
	int hat_height;
	int hat_width;
	int skateboard_len;
	int skateboard_height;
	int skateboard_offset;
	int wheel_radius;
	int sword_width_distance_top;
	int sword_height_distance_top;
	int sword_width_distance_bottom;
	int sword_height_distance_bottom;
	int sword_line_width;
	int sword_line_height;
	int left_triangle_x;
	int left_triangle_y;
	int right_triangle_x;
	int right_triangle_y;
	int top_triangle_x;
	int top_triangle_y;
	int bottom_triangle_x;
	int bottom_triangle_y;
	int theme_color;
	int item_color;
	int sword_color;
	int start_plane_x;
	int start_plane_y;
};


struct display_object {
	struct display_object *head;
	struct point *point;
	struct display_object *next;
};

struct display_object *display_object_add_point(struct display_object *obj, struct point *p);
void display_date_and_time();
void display_battery_status(int menu_context);
void display_move_pixel(struct point *point_a, uint16_t bg_color, uint16_t color, int pos_x, int pos_y);
void display_ground(int color, int width);
void display_man();
void display_menu();
void display_start_page();
void display_bar(int selected_item, int color, int sword_color);
void display_ateist_man();
void display_man_handshake(struct point hand[], int color, int width);
void display_sword(int color, int sword_color, int width);
void display_bird(int color, int width);
void display_move_line();

#define ITEMS_NUMBER 2
