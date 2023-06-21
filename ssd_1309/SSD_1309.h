/*H**************************************************************************
* НАЗВАНИЕ:         SSD_1309.h        
*----------------------------------------------------------------------------
* Copyright (c) 2023
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:
*----------------------------------------------------------------------------
* ОПИСАНИЕ:
*****************************************************************************/

#ifndef _SSD_1309_H_
#define _SSD_1309_H_

/*_____ I N C L U D E S ____________________________________________________*/
#include "main.h"

 //#include "gpio.h"


/*_____ T Y P E D E F S ___________________________________________________*/

typedef struct {
	uint16_t current_x;
	uint16_t current_y;
} ssd1309_t;

typedef enum
{
	 pt8 = 8,
	 pt10 = 10,
	 pt12 = 12,
	 pt14 = 14,
	 pt16 = 16,
} font_size_t;


/*_____ D E F I N I T I O N __ A N D ___ M A C R O S ________________*/

#define SSD1309_X_SIZE				128
#define SSD1309_Y_SIZE				64
#define SSD1309_BUFFER_SIZE			(SSD1309_X_SIZE * SSD1309_Y_SIZE) / 8

#define SSD1309_WIDTH				128
#define SSD1309_HEIGHT				64

/* Определения для инициализации дисплея; */

#define  SSD1309_DISPLAY_OFF 					0xAE		//	Выключение дисплея;
#define  SSD1309_DISPLAY_ON 					0xAF		//	Включение дисплея;

#define  SSD1309_PAGE_START_ADDRESS(X)          (0xB0 | X)  //	Стартовый адрес сектора (В0-В7);

#define  SSD1309_SET_CONTRAST					0x81		//	Команда установки уровня контрастности (0-256);
#define  SSD1309_CONTRAST_VALUE(X)				(X)

#define  SSD1309_NORMAL_MODE          			0xC0		//	Команда C0h, нормальный режим, сканирование с COM0 по COM[N –1];
#define  SSD1309_REMAPPED_MODE        			0xC8		//	Команда С8h, переназначенный режим, сканирование с COM[N –1] по COM0;

#define  SSD1309_START_LOW_COLUMN(X)			(0x00 | X)	//	Команды 00~0F, начальный нижний столбец (Режим адресации страницы);
#define  SSD1309_START_HIGH_COLUMN(X)		    (0x10 | X)	//	Команды 10~1F, начальный верхний столбец (Режим адресации страницы);

#define  SSD1309_SET_MODE_ADDRESSING			0x20		//	Команда режим адресации:
#define  SSD1309_HORIZONTAL_MODE				0x00		//	-00h - горизонтальный режим;
#define  SSD1309_VERTICAL_MODE					0x01		//	-01h - вертикальный режим;
#define  SSD1309_PAGE_MODE						0x10		//	-10h - страничный режим;

#define  SSD1309_SET_COLUMN_RANGE 				0x21   		//	Команда диапазон столбцов:
#define  SSD1309_START_COLUMN(X)				(X)   		//	0x00-0x7Fh - начальный диапазон столбцов;
#define  SSD1309_END_COLUMN(X)					(X)			//	0x00-0x7Fh - конечный диапазон стобцов;

#define  SSD1309_SET_PAGE_RANGE 				0x22		//	Команда диапазон страниц:
#define  SSD1309_START_PAGE(X)      			(X)   		//	0x00-0x07h - начальный диапазон страниц;
#define  SSD1309_END_PAGE(X)	    			(X)	 		//	0x00-0x07h - конечный диапазон страниц;

#define  SSD1309_SEGMENT_0_MAPPED_SEG0			0xA0 		//	Команда адрес столбца 0 сопоставляется с сегментом 0;
#define  SSD1309_SEGMENT_127_MAPPED_SEG0		0xA1		//	Команда адрес столбца 127 сопоставляется с сегметом 0;

/* Определения для портов ввода/вывода; */
/*#define GPIO_PORT_D 				GPIOB

#define RD_E_PIN 					GPIO_PINS_3
#define RD_E_GPIO_PORT 				GPIOB

#define WR_PIN 						GPIO_PINS_4
#define WR_GPIO_PORT				GPIOB

#define CS_PIN 						GPIO_PINS_5
#define CS_GPIO_PORT 				GPIOB

#define D_C_PIN 					GPIO_PINS_6
#define D_C_GPIO_PORT				GPIOB

#define RES_PIN 					GPIO_PINS_7
#define RES_GPIO_PORT 				GPIOB*/


/*_____ F U N C T I O N S ____________________________________________*/

void ssd1309_reset(void);
void ssd1309_send_command(uint8_t command);
void ssd1309_send_data(uint8_t data);

void ssd1309_clear_buffer(void);
void ssd1309_update_screen(void);
void ssd1309_goto_x_y(uint16_t x, uint16_t y);
void ssd1309_init(void);
void ssd1309_draw_filled_rect(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);






#endif	//_SSD_1309_H_