/*H**************************************************************************
* ????????:         i2c.h        
*----------------------------------------------------------------------------
* Copyright (c) 2023
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:
*----------------------------------------------------------------------------
* ????????:
*****************************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

/*_____ I N C L U D E S ____________________________________________________*/

#include "main.h"

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/
/***********************************/
#define I2C_TIMEOUT                      240000

#define I2Cx_SPEED                       100000
#define I2Cx_ADDRESS                     0xA0

#define I2Cx_PORT                        I2C2
#define I2Cx_CLK                         CRM_I2C2_PERIPH_CLOCK

#define I2Cx_SCL_PIN                     GPIO_PINS_10
#define I2Cx_SCL_GPIO_PORT               GPIOB
#define I2Cx_SCL_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define I2Cx_SDA_PIN                     GPIO_PINS_11
#define I2Cx_SDA_GPIO_PORT               GPIOB
#define I2Cx_SDA_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define BUF_SIZE                         8
/*******************************/
void i2c_lowlevel_init(i2c_handle_type* hi2c);
unsigned char i2c_send_request(unsigned char address);
void error_handler(uint32_t error_code);

#endif	//_i2c_h