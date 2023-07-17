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

#ifndef _TH08_H_
#define _TH08_H_

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
#define     SI7006_ADDRESS       0x40                                                
#define     SI7006_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE           0xF5               
#define     SI7006_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE                 0xF3  

void error_handler(uint32_t error_code);
void tt_i2c_write(uint8_t slaveAddr, uint8_t regAddr);
uint8_t tt_i2c_read(uint8_t slaveAddr);
void MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE (void);
void MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE (void);
void si7006(void);

#endif	//_TH08_H