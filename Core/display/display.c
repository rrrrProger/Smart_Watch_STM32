#include "display.h"
#include <stdio.h>
#include "st7735.h"
#include <stdlib.h>
#include "stm32f1xx_hal.h"

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

void display_date_and_time() {
	ILI9341_WriteString(40, 10, date, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
	ILI9341_WriteString(40, 110, time, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
}

void display_battery_status() {
  char    adc_char[20];
  float   adc_value = 0;
  float   bat_percent = 0;
  int     display_bat = 0;
  float   supply_voltage = 3.28;
  float   min_voltage = 3.2;
  int     battery_voltage = 4.2;
  int     width = 0;
  struct  point point_a = {128, 7};
  struct  point point_b = {152, 7};
  struct  point point_c = {152, 20};
  struct  point point_d = {128, 20};

  HAL_ADC_Start(&hadc2);
  HAL_ADC_PollForConversion(&hadc2, 1);
  adc_value = HAL_ADC_GetValue(&hadc2);
  bat_percent = adc_value / 4095;
  display_bat = bat_percent * supply_voltage * 2 * 100 - min_voltage * 100;
  if (display_bat < 0)
	  display_bat = 0;

  sprintf(adc_char, "%d", display_bat);
  ILI9341_WriteString(133, 10, adc_char, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
  ILI9341_DrawRectangle(&point_a, &point_b, &point_c, &point_d, ILI9341_BLACK, width);
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

void display_vader() {
	;
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
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim1);
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
