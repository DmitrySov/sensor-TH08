/*H**************************************************************************
* ????????:         board.h        
*----------------------------------------------------------------------------
* Copyright (c) 2022
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:
*----------------------------------------------------------------------------
* ????????:
*****************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

/*_____ I N C L U D E S ____________________________________________________*/

#include "main.h"

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/
typedef enum
{
  LED2                                   = 0,
  LED3                                   = 1,
  LED4                                   = 2
} led_type;

#define LED_NUM                          3

#define LED2_PIN                         GPIO_PINS_13
#define LED2_GPIO                        GPIOD
#define LED2_GPIO_CRM_CLK                CRM_GPIOD_PERIPH_CLOCK

#define LED3_PIN                         GPIO_PINS_14
#define LED3_GPIO                        GPIOD
#define LED3_GPIO_CRM_CLK                CRM_GPIOD_PERIPH_CLOCK

#define LED4_PIN                         GPIO_PINS_15
#define LED4_GPIO                        GPIOD
#define LED4_GPIO_CRM_CLK                CRM_GPIOD_PERIPH_CLOCK


void board_led_init ();
void board_led_toggle(led_type led);
void delay_init ();
void delay_ms(uint16_t nms);

#endif	//_BOARD_H_