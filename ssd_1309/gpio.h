/*H**************************************************************************
* НАЗВАНИЕ:         gpio.h        
*----------------------------------------------------------------------------
* Copyright (c) 2023
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:
*----------------------------------------------------------------------------
* ОПИСАНИЕ:
*****************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

/*_____ I N C L U D E S ____________________________________________________*/
#include "main.h"


/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/
typedef gpio_type gpio_port_t;

typedef uint16_t gpio_pin_t;

#define __WRITE_GPIO(__GPIOx__, __PIN__, __STATE__)     gpio_bits_write(__GPIOx__,  __PIN__, __STATE__)

#define __WRITE_BITS_0_7(__GPIO__, __Value__)           gpio_port_write(__GPIO__, __Value__)
//#define __WRITE_BITS_0_7(__GPIO__, __Value__) 			WRITE_REG(__GPIO__->ODR, __Value__);

/* Определения для портов ввода/вывода; */
#define GPIO_PORT_D 				GPIOD

#define CS_PIN 						GPIO_PINS_10
#define CS_GPIO_PORT 				GPIOC

#define RES_PIN 					GPIO_PINS_11
#define RES_GPIO_PORT 				GPIOC

#define WR_PIN 						GPIO_PINS_12
#define WR_GPIO_PORT				GPIOC

#define D_C_PIN 					GPIO_PINS_6
#define D_C_GPIO_PORT				GPIOC

#define RD_E_PIN 					GPIO_PINS_7
#define RD_E_GPIO_PORT 				GPIOC
/*_____ D E C L A R A T I O N ______________________________________________*/

void gpio_int(void);
void gpio_write(gpio_type *gpio_x, uint16_t port_value);


#endif	//_gpio_H_