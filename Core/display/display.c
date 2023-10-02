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

static void display_sword(int x, int y, int color, int sword_color, int width) {
	int sword_width_distance_top = 4;
	int sword_height_distance_top = 12;
	int sword_width_distance_bottom = 5;
	int sword_height_distance_bottom = 5;
	int sword_line_width = 15;
	int sword_line_height = 40;

	struct point sword_a = {x, y};
	struct point sword_b = {x + sword_width_distance_top, y - sword_height_distance_top};
	struct point sword_c = {x + sword_width_distance_top + sword_width_distance_bottom, y - sword_height_distance_top + sword_height_distance_bottom};
	struct point sword_d = {x + sword_width_distance_bottom, y + sword_height_distance_bottom};

	struct point sword_line_point_a0 = {sword_a.x + sword_width_distance_top / 3, sword_a.y - sword_height_distance_top / 3};
	struct point sword_line_point_a1 = {sword_d.x + sword_width_distance_top / 3, sword_d.y - sword_height_distance_top / 3};

	struct point sword_line_point_b0 = {sword_a.x + 2 * sword_width_distance_top / 3, sword_a.y - 2 * sword_height_distance_top / 3};
	struct point sword_line_point_b1 = {sword_d.x + 2 * sword_width_distance_top / 3, sword_d.y - 2 * sword_height_distance_top / 3};

	struct point point_a = {sword_b.x + sword_width_distance_bottom / 2, sword_b.y + sword_height_distance_bottom / 2};
	struct point point_b = {sword_b.x + sword_width_distance_bottom / 2 + sword_line_width, sword_b.y + sword_height_distance_bottom / 2 - sword_line_height};

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
	ILI9341_WriteString(40, 10, date, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
	ILI9341_WriteString(ILI9341_WIDTH / 2 - 27, ILI9341_HEIGHT - 10, time, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
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
	  ILI9341_DrawRectangle(&point_a, &point_b, &point_c, &point_d, ILI9341_BLACK, width);
	  ILI9341_WriteString(point_a.x + offset, point_a.y + offset, adc_char, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
  } else {
	  ILI9341_DrawRectangle(&point_a, &point_b, &point_c, &point_d, ILI9341_WHITE, width);
	  ILI9341_WriteString(point_a.x + offset, point_a.y + offset, adc_char, Font_7x10, ILI9341_WHITE, ILI9341_BLACK);
  }
  HAL_ADC_Stop(&hadc2);
}

void display_move_pixel(struct point *point_a, uint16_t bg_color, uint16_t color, int pos_x, int pos_y) {
	ILI9341_DrawPoint(point_a, bg_color);
	point_a->x = point_a->x + pos_x;
	point_a->y = point_a->y + pos_y;
	ILI9341_DrawPoint(point_a, color);
}


void display_ground() {
	struct point point_hor_start = {0, 80};
	struct point point_hor_end = {ILI9341_WIDTH, 80};
	int i;
	int i_end = ILI9341_WIDTH - 15;

	ILI9341_DrawLine(&point_hor_start, &point_hor_end, ILI9341_BLACK, 0);
	for (i = ILI9341_WIDTH; i > i_end; i = i - 15) {
		struct point *point_s = (struct point *)malloc(sizeof(struct point));
		struct point *point_e = (struct point *)malloc(sizeof(struct point));
		if (point_s) {
			point_s->x = i;
			point_s->y = 80;
		}
		if (point_e) {
			point_e->x = i - 10;
			point_e->y = 95;
		}
		if (point_s) {
			free(point_s);
		}
		if (point_e) {
			free(point_e);
		}

	}
}

void display_ateist_man() {
	int leg_start_x = ILI9341_WIDTH / 2;
	int leg_start_y = ILI9341_HEIGHT / 2 + 10;
	int leg_width = 10;
	int leg_length = 20;
	int body_length = 20;
	int hand_width = 10;
	int hand_length = 20;
	int neck_length = 5;
	int head_radius = 7;
	int hat_height   = 5;
	int hat_width   = 7;
	int skateboard_len = 30;
	int skateboard_height = 5;
	int skateboard_offset = 5;
	int wheel_radius = 5;

	struct point leg_l_start = {leg_start_x, leg_start_y};
	struct point leg_l_end   = {leg_start_x - leg_width, leg_start_y + leg_length};
	struct point leg_r_end   = {leg_start_x + leg_width, leg_start_y + leg_length};
	struct point body_end    = {leg_start_x, leg_start_y - body_length};
	struct point hand_l_end  = {leg_start_x - hand_width, leg_start_y - body_length + hand_length};
	struct point hand_r_end  = {leg_start_x + hand_width, leg_start_y - body_length + hand_length};
	struct point neck_end    = {leg_start_x, leg_start_y - body_length - neck_length};
	struct point head_center = {leg_start_x, leg_start_y - body_length - neck_length - head_radius};
	struct point hat_coord_l  = {leg_start_x - hat_width, leg_start_y - body_length - neck_length - 2 * head_radius};
	struct point hat_coord_r  = {leg_start_x + hat_width, leg_start_y - body_length - neck_length - 2 * head_radius};
	struct point hat_coord_t  = {leg_start_x, leg_start_y - body_length - neck_length - head_radius - 2 * head_radius - hat_height};
	struct point skateboard_points[] = {
			{leg_start_x - skateboard_len, leg_start_y + leg_length},
			{leg_start_x + skateboard_len, leg_start_y + leg_length},
			{leg_start_x + skateboard_len, leg_start_y + skateboard_height + leg_length},
			{leg_start_x - skateboard_len, leg_start_y + skateboard_height + leg_length}
	};
	struct point wheel_points[] = {
			{leg_start_x - skateboard_len + skateboard_offset, leg_start_y + leg_length + wheel_radius + skateboard_height},
			{leg_start_x + skateboard_len - skateboard_offset, leg_start_y + leg_length + wheel_radius + skateboard_height}
	};

	ILI9341_DrawLine(&leg_l_start, &leg_l_end, ILI9341_BLACK, 1);
	ILI9341_DrawLine(&leg_l_start, &leg_r_end, ILI9341_BLACK, 1);
	ILI9341_DrawLine(&leg_l_start, &body_end, ILI9341_BLACK, 1);
	ILI9341_DrawLine(&body_end, &hand_l_end, ILI9341_BLACK, 1);
	ILI9341_DrawLine(&body_end, &hand_r_end, ILI9341_BLACK, 1);
	ILI9341_DrawLine(&body_end, &neck_end, ILI9341_BLACK, 1);
	ILI9341_DrawCircle(&head_center, head_radius, ILI9341_BLACK, 1);
	ILI9341_DrawTriangle(&hat_coord_l, &hat_coord_t, &hat_coord_r, ILI9341_BLACK, 1);

	display_sword(hand_r_end.x, hand_r_end.y, ILI9341_BLACK, ILI9341_GREEN, 1);
	display_skateboard(skateboard_points, wheel_points, wheel_radius, ILI9341_BLACK, 1);
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

void display_menu() {

	ILI9341_FillScreen(ILI9341_BLACK);
	for (int i = 0; i < ITEMS_NUMBER; i++) {
		ILI9341_WriteString(items[i].x, items[i].y, (char*)items[i].text, Font_7x10, ILI9341_WHITE, ILI9341_BLACK);
	}
}

void display_start_page() {
	ILI9341_FillScreen(ILI9341_WHITE);
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
