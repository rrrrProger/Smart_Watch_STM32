/* vim: set ai et ts=4 sw=4: */
#ifndef __ILI9341_H__
#define __ILI9341_H__

#include "fonts.h"
#include <stdbool.h>
#include "stm32f1xx_hal.h"

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

/*** Redefine if necessary ***/
#define ILI9341_SPI_PORT hspi2
extern SPI_HandleTypeDef ILI9341_SPI_PORT;

#define ILI9341_RES_Pin       GPIO_PIN_8
#define ILI9341_RES_GPIO_Port GPIOA
#define ILI9341_CS_Pin        GPIO_PIN_4
#define ILI9341_CS_GPIO_Port  GPIOA
#define ILI9341_DC_Pin        GPIO_PIN_11
#define ILI9341_DC_GPIO_Port  GPIOA

struct point {
	uint8_t x;
	uint8_t y;
};

// AliExpress/eBay 1.8" display, default orientation
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 160
#define ILI9341_XSTART 0
#define ILI9341_YSTART 0
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY)
*/

// AliExpress/eBay 1.8" display, rotate right
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 0
#define ILI9341_YSTART 0
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, rotate left
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 0
#define ILI9341_YSTART 0
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, upside down
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 160
#define ILI9341_XSTART 0
#define ILI9341_YSTART 0
#define ILI9341_ROTATION (0)
*/

// WaveShare ILI9341S-based 1.8" display, default orientation
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 160
#define ILI9341_XSTART 2
#define ILI9341_YSTART 1
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_RGB)
*/

// WaveShare ILI9341S-based 1.8" display, rotate right
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 1
#define ILI9341_YSTART 2
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_RGB)
*/

// WaveShare ILI9341S-based 1.8" display, rotate left
/*
#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 1
#define ILI9341_YSTART 2
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MV | ILI9341_MADCTL_RGB)
*/

// WaveShare ILI9341S-based 1.8" display, upside down

#define ILI9341_IS_160X128 1
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 1
#define ILI9341_YSTART 2
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_MV)

/*

// 1.44" display, default orientation
#define ILI9341_IS_128X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 2
#define ILI9341_YSTART 3
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)
*/
// 1.44" display, rotate right
/*
#define ILI9341_IS_128X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 3
#define ILI9341_YSTART 2
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// 1.44" display, rotate left
/*
#define ILI9341_IS_128X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 1
#define ILI9341_YSTART 2
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// 1.44" display, upside down
/*
#define ILI9341_IS_128X128 1
#define ILI9341_WIDTH  128
#define ILI9341_HEIGHT 128
#define ILI9341_XSTART 2
#define ILI9341_YSTART 1
#define ILI9341_ROTATION (ILI9341_MADCTL_BGR)
*/

// mini 160x80 display (it's unlikely you want the default orientation)
/*
#define ILI9341_IS_160X80 1
#define ILI9341_XSTART 26
#define ILI9341_YSTART 1
#define ILI9341_WIDTH  80
#define ILI9341_HEIGHT 160
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)
*/

// mini 160x80, rotate left
/*
#define ILI9341_IS_160X80 1
#define ILI9341_XSTART 1
#define ILI9341_YSTART 26
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 80
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// mini 160x80, rotate right
/*
#define ILI9341_IS_160X80 1
#define ILI9341_XSTART 1
#define ILI9341_YSTART 26
#define ILI9341_WIDTH  160
#define ILI9341_HEIGHT 80
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

/****************************/

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMSET  0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29
#define ILI9341_CASET   0x2A
#define ILI9341_RASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_COLMOD  0x3A
#define ILI9341_MADCTL  0x36

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DISSET5 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_PWCTR6  0xFC

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1

// Color definitions
#define	ILI9341_BLACK   0x0000
#define	ILI9341_BLUE    0x001F
#define	ILI9341_RED     0xF800
#define	ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF
#define ILI9341_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// call before initializing any SPI devices
void ILI9341_Unselect();

void ILI9341_Init(void);
void ILI9341_DrawPoint(struct point *point_a, uint16_t color);
void ILI9341_DrawLine(struct point *point_a, struct point *point_b, uint16_t color, int width);
void ILI9341_DrawTriangle(struct point *point_a, struct point *point_b, struct point *point_c, uint16_t color, int width);
void ILI9341_DrawCircle(struct point center, int radius);
void ILI9341_DrawRectangle(struct point *point_a, struct point *point_b, struct point *point_c, struct point *point_d, uint16_t color, int width);
void ILI9341_DrawEllipse();
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ILI9341_InvertColors(bool invert);

#ifdef __cplusplus
}
#endif

#endif // __ILI9341_H__
