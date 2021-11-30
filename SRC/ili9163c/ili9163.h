#ifndef __ILI9163_H
#define __ILI9163_H

#include <string.h>
#include "user_hal.h"
#include "user_hal_spi.h"

#define TFT_HOR_RES 132
#define TFT_VER_RES 162

#define CSPin_GPIO_Port 	SPI2_CS_Port
#define CSPin_Pin					SPI2_CS_Pin
#define ResPin_GPIO_Port 	SPI2_Reset_Port
#define ResPin_Pin 				SPI2_Reset_Pin
#define AOPin_Pin 				SPI2_DC_Pin
#define AOPin_GPIO_Port 	SPI2_DC_Port

#define HSPI SPI2

#define _DEBUG_  1 	//屏幕打印宏函数开关，1是开，0是关，调试的时候开，调式完毕就可以一键关闭

#define u16RED		0xf800
#define u16BLUE		0x07e0
#define u16GREEN	 0x001f  
#define u16YELLOW	0xf81f
#define u16PURPLE	0xffe0
#define u16CYAN	  0x07ff 		//蓝绿色
#define u16ORANGE	0xfc08
#define u16BLACK	0x0000
#define u16WHITE	0xffff

#define DATA 0
#define REG 1

void ili9163_init(void);

void send_byte(uint8_t data, uint8_t data_reg);
void send_word(uint16_t data, uint8_t data_reg);
void send_data(uint8_t *data, uint8_t data_len);
void send_command(uint8_t data);
void SetAddata_regessWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void ili9163_clr(unsigned short color);
void ili9163_P8X16(unsigned short x, unsigned short y, unsigned short c_dat,unsigned short word_color,unsigned short back_color);
void ili9163_P8X16Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);

extern char ILI9163_Str_BUF[200]; //发送缓冲,最大200字节，不能太小，如果你的内容太长会访问非法内存
/*------------------DEBUG DEFINE BEGIN------------------------*/
#if _DEBUG_
#define lps(x,y,...)  do{\
	sprintf((char *)ILI9163_Str_BUF,__VA_ARGS__);\
	ili9163_P8X16Str(x, y, ILI9163_Str_BUF,0xffff,0x0000);\
} while(0)
#else
#define lps(...)
#endif
/*------------------DEBUG DEFINE END------------------------*/

#endif /* __ILI9163_H */
