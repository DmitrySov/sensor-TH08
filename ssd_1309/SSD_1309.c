/*C**************************************************************************
* НАЗВАНИЕ:         SSD_1309.c
*----------------------------------------------------------------------------
* Copyright (c) 2023
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:   
*----------------------------------------------------------------------------
* НАЗНАЧЕНИЕ:
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/

/*_____ I N C L U D E S ____________________________________________________*/

#include "SSD_1309.h"


/*_____ T Y P E D E F S ___________________________________________________*/

ssd1309_t ssd1309;


/*_____ M A C R O S ________________________________________________________*/



/*_____ D E F I N I T I O N ________________________________________________*/



/*_____ F U N C T I O N S ____________________________________________________*/

static void set_pixel_in_buffer(uint8_t x, uint8_t y);


/*_____ V A R I A B L E S ____________________________________________________*/

static uint8_t pixel_buffer[SSD1309_BUFFER_SIZE];	// буфер дисплея;

font_size_t font_size;


/***********************************************************************************
 * Function:		ssd1309_reset
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Функция сброса, выполняется при инициализации;
 *
 * parameters:
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_reset(void)
{
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, FALSE);
	__WRITE_GPIO(RES_GPIO_PORT, RES_PIN, TRUE); 
	__WRITE_GPIO(RES_GPIO_PORT, RES_PIN, FALSE);
        delay_ms(10);
	__WRITE_GPIO(RES_GPIO_PORT, RES_PIN, TRUE);
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, TRUE);

}

/***********************************************************************************
 * Function:		ssd1309_send_command
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Отправка команд;
 *
 * parameters:		uint8_t command   команды отправляются в соответствие таблицы команд 9-1 (datasheet);
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_send_command(uint8_t command)
{
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, FALSE);
	__WRITE_GPIO(D_C_GPIO_PORT, D_C_PIN, FALSE);
	__WRITE_GPIO(WR_GPIO_PORT, WR_PIN, FALSE);
        uint16_t n = 0;
        n = gpio_output_data_read(GPIO_PORT_D);
        n = n & command;
        __WRITE_BITS_0_7(GPIO_PORT_D, 0x00);
	__WRITE_BITS_0_7(GPIO_PORT_D, command);  //
        n = gpio_output_data_read(GPIO_PORT_D);
	__WRITE_GPIO(WR_GPIO_PORT, WR_PIN, TRUE);
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, TRUE);
}

/***********************************************************************************
 * Function:		ssd1309_send_data
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Отправка данных на дисплей;
 *
 * parameters:		uint8_t data     данные для записи на дисплей;
 *
 * on return:
 *
*************************************************************************************/

void ssd1309_send_data(uint8_t data)
{
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, FALSE);
	__WRITE_GPIO(D_C_GPIO_PORT, D_C_PIN, TRUE);
	__WRITE_GPIO(WR_GPIO_PORT, WR_PIN, FALSE);
	/*uint16_t m = 0;
        m = gpio_output_data_read(GPIO_PORT_D);
        m = m & data;*/
	__WRITE_BITS_0_7(GPIO_PORT_D, data);  //
      //  n = gpio_output_data_read(GPIO_PORT_D);
	__WRITE_GPIO(WR_GPIO_PORT, WR_PIN, TRUE);
	__WRITE_GPIO(CS_GPIO_PORT, CS_PIN, TRUE);
}

/***********************************************************************************
 * Function:		set_pixel_in_buffer
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Запись пикселя по координатам в буфер;
 *
 * parameters:		uint8_t x, uint8_t y	координаты пикселя;
 *
 * on return:
 *
 *************************************************************************************/

static void set_pixel_in_buffer(uint8_t x, uint8_t y)
{
	/* Сравниваем входные данные с шириной и высотой дисплея; */
	if (x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT)
	{
		return;
	}
	/* Запись пикселя в буфер; */
	pixel_buffer[x + (y / 8) * SSD1309_X_SIZE] |= (1 << (y % 8));
}

/***********************************************************************************
 * Function:		clear_buffer
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Очистка всего буфера дисплея;
 *
 * parameters:
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_clear_buffer(void)
{
	memset(pixel_buffer, 0x00, sizeof(pixel_buffer));
}

/***********************************************************************************
 * Function:		ssd1309_update_screen
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Обновление дисплея, по значениям буфера;
 *
 * parameters:
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_update_screen(void)
{
	uint16_t bit_pixel;

	/*выбор сегмента (i)*/
	for (uint8_t i = 0; i < 8; i++)
	{
		ssd1309_send_command(SSD1309_PAGE_START_ADDRESS(i));
		bit_pixel = i * 128;

		/*обновляем все 128 столбцов выбранного сегмента*/
		for (uint8_t j = 0; j < 128; j++)
		{
			bit_pixel++;
			ssd1309_send_data(pixel_buffer[bit_pixel]);
		}
	}
}

/***********************************************************************************
 * Function:		ssd1309_goto_x_y
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Установка начальных координат;
 *
 * parameters:		uint16_t x, uint16_t y		начальные координаты;
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_goto_x_y(uint16_t x, uint16_t y)
{
	ssd1309.current_x = x;
	ssd1309.current_y = y;
}

/***********************************************************************************
 * Function:		ssd1309_init
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Инициализация OLED-дисплея, с отправкой команд отображения;
 *
 * parameters:
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_init(void)
{
	ssd1309_reset();
	ssd1309_send_command(SSD1309_DISPLAY_OFF);
        delay_ms(100);
        
	ssd1309_clear_buffer();

	ssd1309_send_command(SSD1309_PAGE_START_ADDRESS(0x00));
	/***************/
	ssd1309_send_command(SSD1309_CONTRAST_VALUE(0xFF));
	ssd1309_send_command(SSD1309_SET_CONTRAST);
	/***************/
	ssd1309_send_command(SSD1309_NORMAL_MODE);
	/***************/
	ssd1309_send_command(SSD1309_START_LOW_COLUMN(0x00));
	ssd1309_send_command(SSD1309_START_HIGH_COLUMN(0x10));
	/***************/
	ssd1309_send_command(SSD1309_DISPLAY_ON); 
	/***************/
	ssd1309_send_command(SSD1309_SET_MODE_ADDRESSING);
	ssd1309_send_command(SSD1309_HORIZONTAL_MODE);
	/***************/
	ssd1309_send_command(SSD1309_SET_COLUMN_RANGE);
	ssd1309_send_command(SSD1309_START_COLUMN(0x00));
	ssd1309_send_command(SSD1309_END_COLUMN(0x7F));
	/***************/
	ssd1309_send_command(SSD1309_SET_PAGE_RANGE);
	ssd1309_send_command(SSD1309_START_PAGE(0x00));
	ssd1309_send_command(SSD1309_END_PAGE(0x07));
	/***************/
	ssd1309_send_command(SSD1309_SEGMENT_0_MAPPED_SEG0);
}

/***********************************************************************************
 * Function:		ssd1309_draw_filled_rect
 *
 *----------------------------------------------------------------------------------
 *
 * description:		Заполненный прямоугольник;
 *
 * parameters:		uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end
 *					координаты прмоугольника;
 *
 * on return:
 *
 *************************************************************************************/

void ssd1309_draw_filled_rect(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end)
{
	for (uint8_t i = x_start; i < x_end; i++)
	{
		for (uint8_t j = y_start; j < y_end; j++)
		{
			set_pixel_in_buffer(i, j);
		}
	}
}