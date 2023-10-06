#include "display.h"
#include <stdio.h>
#include "st7735.h"
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include <math.h>

extern char time[30];
extern char date[30];
extern ADC_HandleTypeDef hadc2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim1;
extern struct global gl;

struct item {
	int x;
	int y;
	char text[20];
	int  selected;
};

struct item items[] = {
		{30, 10, "Pokryshka timer", 1},
		{30, 40, "Wifi connect", 0},
};

struct display_object *display_init_object(struct point *p) {
	struct display_object *obj = (struct display_object *)malloc(sizeof(struct display_object));
	if (obj) {
		obj->point = p;
		obj->next = NULL;
		obj->head = obj;
		return obj;
	} else {
		return NULL;
	}
}

struct display_object *display_object_add_point(struct display_object *obj, struct point *p) {
	struct display_object *last_obj = NULL;

	for (struct display_object *temp = obj; temp != NULL; temp = temp->next) {
		if (!temp->next)
			last_obj = temp;
	}
	if (last_obj) {
		last_obj->next = (struct display_object *)malloc(sizeof(struct display_object));
		if (last_obj->next) {
			last_obj->next->point = p;
			last_obj->next->next = NULL;
			last_obj->head = obj->head;
		}
	}
}

void display_sword(int color, int sword_color, int width) {
	int x = gl.leg_start_x + gl.hand_width;
	int y = gl.leg_start_y - gl.body_length + gl.hand_length;

	struct point sword_a = {x, y};
	struct point sword_b = {x + gl.sword_width_distance_top, y - gl.sword_height_distance_top};
	struct point sword_c = {x + gl.sword_width_distance_top + gl.sword_width_distance_bottom, y - gl.sword_height_distance_top + gl.sword_height_distance_bottom};
	struct point sword_d = {x + gl.sword_width_distance_bottom, y + gl.sword_height_distance_bottom};

	struct point sword_line_point_a0 = {sword_a.x + gl.sword_width_distance_top / 3, sword_a.y - gl.sword_height_distance_top / 3};
	struct point sword_line_point_a1 = {sword_d.x + gl.sword_width_distance_top / 3, sword_d.y - gl.sword_height_distance_top / 3};

	struct point sword_line_point_b0 = {sword_a.x + 2 * gl.sword_width_distance_top / 3, sword_a.y - 2 * gl.sword_height_distance_top / 3};
	struct point sword_line_point_b1 = {sword_d.x + 2 * gl.sword_width_distance_top / 3, sword_d.y - 2 * gl.sword_height_distance_top / 3};

	struct point point_a = {sword_b.x + gl.sword_width_distance_bottom / 2, sword_b.y + gl.sword_height_distance_bottom / 2};
	struct point point_b = {sword_b.x + gl.sword_width_distance_bottom / 2 + gl.sword_line_width, sword_b.y + gl.sword_height_distance_bottom / 2 - gl.sword_line_height};


	ILI9341_DrawRectangle(&sword_a, &sword_b, &sword_c, &sword_d, color, width);
	ILI9341_DrawLine(&sword_line_point_a0, &sword_line_point_a1, color, width);
	ILI9341_DrawLine(&sword_line_point_b0, &sword_line_point_b1, color, width);
	//Sword body line
	ILI9341_DrawLine(&point_a, &point_b, sword_color, 1);
}

static void display_skateboard(struct point points[], struct point wheel_points[], int radius, int color, int width) {
	ILI9341_DrawRectangle(&points[0], &points[1], &points[2], &points[3], ILI9341_BLACK, 1);
	ILI9341_DrawCircle(&wheel_points[0], radius, color, width);
	ILI9341_DrawCircle(&wheel_points[1], radius, color, width);
}

void display_date_and_time() {
	ILI9341_WriteString(40, 10, date, Font_7x10, gl.item_color, gl.theme_color);
	ILI9341_WriteString(ILI9341_WIDTH / 2 - 27, ILI9341_HEIGHT - 10, time, Font_7x10, gl.item_color, gl.theme_color);
}

void display_battery_status(int menu_context) {
  char    adc_char[20];
  float   adc_value = 0;
  float   bat_percent = 0.0;
  int     display_bat = 0;
  float   supply_voltage = 3.28;
  float   min_voltage = 3.2;
  float   display_bat_float = 0;
  int     battery_voltage = 4.2;
  int     width = 0;
  int 	  offset = 2;
  struct  point point_a = {127, 8};
  struct  point point_b = {157, 8};
  struct  point point_c = {157, 22};
  struct  point point_d = {127, 22};

  HAL_ADC_Start(&hadc2);
  HAL_ADC_PollForConversion(&hadc2, 1);
  adc_value = HAL_ADC_GetValue(&hadc2);
  bat_percent = adc_value / 4095;
  display_bat_float = bat_percent * supply_voltage * 2.08;
  display_bat_float = ceilf(display_bat_float * 100) / 100;
//  display_bat_float = bat_percent * supply_voltage * 2.08;
  display_bat = ceil(display_bat_float);
  if (display_bat < 0)
	  display_bat = 0;

  sprintf(adc_char, "%.2f", display_bat_float);
//  ILI9341_FillRectangle(point_a.x, point_a.y, point_b.x - point_a.x, point_c.y - point_a.y, ILI9341_GREEN);
  if (!menu_context) {
	  ILI9341_DrawRectangle(&point_a, &point_b, &point_c, &point_d, gl.item_color, width);
	  ILI9341_WriteString(point_a.x + offset, point_a.y + offset, adc_char, Font_7x10, gl.item_color, gl.theme_color);
  } else {
	  ILI9341_DrawRectangle(&point_a, &point_b, &point_c, &point_d, gl.item_color, width);
	  ILI9341_WriteString(point_a.x + offset, point_a.y + offset, adc_char, Font_7x10, gl.theme_color, gl.item_color);
  }
  HAL_ADC_Stop(&hadc2);
}

void display_man_handshake(struct point hand[], int color, int width) {
	int hand_length = sqrt(pow((hand[1].x - hand[0].x), 2) + pow((hand[1].y - hand[0].y), 2));
	int hand_end_start_x = hand[1].x;
	int hand_end_start_y = hand[1].y;
}

void display_move_plane() {
	struct point *plane_points;
}

void display_move_pixel(struct point *point_a, uint16_t bg_color, uint16_t color, int pos_x, int pos_y) {
	ILI9341_DrawPoint(point_a, bg_color);
	point_a->x = point_a->x + pos_x;
	point_a->y = point_a->y + pos_y;
	ILI9341_DrawPoint(point_a, color);
}

void display_ground(int color, int width) {
	struct point ground_points[] = {
			{0, gl.leg_start_y + gl.leg_length},
			{ILI9341_WIDTH, gl.leg_start_y + gl.leg_length}
	};
	ILI9341_DrawLine(&ground_points[0], &ground_points[1], color, width);
}

void display_ateist_man(int sword_color) {
	struct point leg_l_start = {gl.leg_start_x, gl.leg_start_y};
	struct point leg_l_end   = {gl.leg_start_x - gl.leg_width, gl.leg_start_y + gl.leg_length};
	struct point leg_r_end   = {gl.leg_start_x + gl.leg_width, gl.leg_start_y + gl.leg_length};
	struct point body_end    = {gl.leg_start_x, gl.leg_start_y - gl.body_length};
	struct point hand_l_end  = {gl.leg_start_x - gl.hand_width, gl.leg_start_y - gl.body_length + gl.hand_length};
	struct point hand_r_end  = {gl.leg_start_x + gl.hand_width, gl.leg_start_y - gl.body_length + gl.hand_length};
	struct point neck_end    = {gl.leg_start_x, gl.leg_start_y - gl.body_length - gl.neck_length};
	struct point head_center = {gl.leg_start_x, gl.leg_start_y - gl.body_length - gl.neck_length - gl.head_radius};
	struct point hat_coord_l  = {gl.leg_start_x - gl.hat_width, gl.leg_start_y - gl.body_length - gl.neck_length - 2 * gl.head_radius};
	struct point hat_coord_r  = {gl.leg_start_x + gl.hat_width, gl.leg_start_y - gl.body_length - gl.neck_length - 2 * gl.head_radius};
	struct point hat_coord_t  = {gl.leg_start_x, gl.leg_start_y - gl.body_length - gl.neck_length - gl.head_radius - 2 * gl.head_radius - gl.hat_height};
	struct point skateboard_points[] = {
			{gl.leg_start_x - gl.skateboard_len, gl.leg_start_y + gl.leg_length},
			{gl.leg_start_x + gl.skateboard_len, gl.leg_start_y + gl.leg_length},
			{gl.leg_start_x + gl.skateboard_len, gl.leg_start_y + gl.skateboard_height + gl.leg_length},
			{gl.leg_start_x - gl.skateboard_len, gl.leg_start_y + gl.skateboard_height + gl.leg_length}
	};
	struct point wheel_points[] = {
			{gl.leg_start_x - gl.skateboard_len + gl.skateboard_offset, gl.leg_start_y + gl.leg_length + gl.wheel_radius + gl.skateboard_height},
			{gl.leg_start_x + gl.skateboard_len - gl.skateboard_offset, gl.leg_start_y + gl.leg_length + gl.wheel_radius + gl.skateboard_height}
	};

	struct point hand[] = {
			{gl.leg_start_x, gl.leg_start_y - gl.body_length},
			{gl.leg_start_x - gl.hand_width, gl.leg_start_y - gl.body_length + gl.hand_length}
	};

	ILI9341_DrawLine(&leg_l_start, &leg_l_end, gl.item_color, 1);
	ILI9341_DrawLine(&leg_l_start, &leg_r_end, gl.item_color, 1);
	ILI9341_DrawLine(&leg_l_start, &body_end, gl.item_color, 1);
	ILI9341_DrawLine(&body_end, &hand_l_end, gl.item_color, 1);
	ILI9341_DrawLine(&body_end, &hand_r_end, gl.item_color, 1);
	ILI9341_DrawLine(&body_end, &neck_end, gl.item_color, 1);
	ILI9341_DrawCircle(&head_center, gl.head_radius, gl.item_color, 1);
	ILI9341_DrawTriangle(&hat_coord_l, &hat_coord_t, &hat_coord_r, gl.item_color, 1);

//	display_skateboard(skateboard_points, wheel_points, wheel_radius, ILI9341_BLACK, 1);
}

void display_david_star(uint16_t color, int start_x, int start_y) {
	int star_width = 30;
	int star_height = 50;
	int star_distance = 67;

	int width = 1;

	struct point point_a = {start_x, start_y};
	struct point point_b = {start_x - star_width, start_y + star_height};
	struct point point_c = {start_x + star_width, start_y + star_height};

	struct point point_a1 = {start_x, start_y + star_distance};
	struct point point_b1 = {start_x - star_width, start_y + star_distance - star_height};
	struct point point_c1 = {start_x + star_width, start_y + star_distance - star_height};

	ILI9341_DrawTriangle(&point_a, &point_b, &point_c, color, width);
	ILI9341_DrawTriangle(&point_a1, &point_b1, &point_c1, color, width);
}

void display_bird(int color, int width) {
	;
}

void display_star(int color, int width) {
	struct point point_a = {gl.left_triangle_x, gl.left_triangle_y};
	struct point point_b = {gl.top_triangle_x, gl.top_triangle_y};
	struct point point_c = {gl.right_triangle_x, gl.right_triangle_y};
	struct point point_e = {gl.left_triangle_x, gl.top_triangle_y + 10};
	struct point point_f = {gl.right_triangle_x, gl.top_triangle_y + 10};
	struct point point_g = {gl.bottom_triangle_x, gl.bottom_triangle_y};

	ILI9341_DrawTriangle(&point_a, &point_b, &point_c, color, width);
	ILI9341_DrawTriangle(&point_e, &point_f, &point_g, color, width);
///	ILI9341_DrawTriangle();
}

void display_menu() {

	ILI9341_FillScreen(ILI9341_BLACK);
	for (int i = 0; i < ITEMS_NUMBER; i++) {
		ILI9341_WriteString(items[i].x, items[i].y, (char*)items[i].text, Font_7x10, ILI9341_WHITE, ILI9341_BLACK);
	}
}

void display_start_page() {
	ILI9341_FillScreen(gl.theme_color);
	display_ateist_man(gl.sword_color);
	display_ground(gl.item_color, 1);
	display_sword(gl.item_color, gl.sword_color, 1);
	// Read The ADC Conversion Result & Map It To PWM DutyCycle
}

void display_bar (int selected_item, int color, int sword_color) {
	int line_width = 120;
	int sword_width = 20;
	int sword_height = 9;
	int offset = 14;

	struct point sword_a = {items[selected_item - 1].x - 10 - sword_width, items[selected_item - 1].y + offset};
	struct point sword_b = {items[selected_item - 1].x - 10 - sword_width, items[selected_item - 1].y - sword_height + offset};
	struct point sword_c = {items[selected_item - 1].x - 10, items[selected_item - 1].y - sword_height + offset};
	struct point sword_d = {items[selected_item - 1].x - 10, items[selected_item - 1].y + offset};

	struct point sword_line_point_a0 = {sword_c.x - sword_width / 3, sword_b.y};
	struct point sword_line_point_a1 = {sword_c.x - sword_width / 3, sword_d.y};

	struct point sword_line_point_b0 = {sword_c.x - 2 * sword_width / 3, sword_b.y};
	struct point sword_line_point_b1 = {sword_c.x - 2 * sword_width / 3, sword_d.y};

	struct point point_a = {items[selected_item - 1].x - 10, items[selected_item - 1].y + offset - sword_height / 2};
	struct point point_b = {items[selected_item - 1].x - 10 + line_width, items[selected_item - 1].y + offset - sword_height / 2};

	ILI9341_DrawRectangle(&sword_a, &sword_b, &sword_c, &sword_d, color, 0);
	ILI9341_DrawLine(&sword_line_point_a0, &sword_line_point_a1, color, 0);
	ILI9341_DrawLine(&sword_line_point_b0, &sword_line_point_b1, color, 0);
	//Sword body line
	ILI9341_DrawLine(&point_a, &point_b, sword_color, 1);

//	ILI9341_DrawRectangle();
}
