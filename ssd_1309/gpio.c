/*H**************************************************************************
* ÍÀÇÂÀÍÈÅ:         gpio.c
        
*----------------------------------------------------------------------------
* Copyright (c) 2023
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:
*----------------------------------------------------------------------------
* ÎÏÈÑÀÍÈÅ:
*****************************************************************************/
/*_____ I N C L U D E S ____________________________________________________*/

#include "gpio.h"

/*_____ T Y P E D E F S ___________________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/


/*_____ F U N C T I O N S ____________________________________________________*/


/*_____ V A R I A B L E S ____________________________________________________*/
/**
  * @brief  write data to the specified gpio data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE.
  * @param  port_value: specifies the value to be written to the port output data register.
  * @retval none
  */
void gpio_write(gpio_type *gpio_x, uint16_t port_value)
{
  gpio_x->odt = port_value;
}

void gpio_int(void)
{
    gpio_init_type gpio_init_struct;
  
    /* enable the gpio clock */
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

    /* set default parameter */
    gpio_default_para_init(&gpio_init_struct);

    
    __WRITE_GPIO(CS_GPIO_PORT, CS_PIN, TRUE);
    __WRITE_GPIO(RES_GPIO_PORT, RES_PIN, TRUE); 
	
    __WRITE_GPIO(WR_GPIO_PORT, WR_PIN, TRUE);
	//__WRITE_BITS_0_7(GPIO_PORT_D, 0xFF);
    __WRITE_GPIO(GPIOD, GPIO_PINS_0|GPIO_PINS_1|GPIO_PINS_2|GPIO_PINS_3|GPIO_PINS_4|GPIO_PINS_5|GPIO_PINS_6|GPIO_PINS_7, TRUE);
    __WRITE_GPIO(D_C_GPIO_PORT, D_C_PIN, TRUE);
    __WRITE_GPIO(RD_E_GPIO_PORT, RD_E_PIN, TRUE);

    /* configure the gpio port D*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_1|GPIO_PINS_2|GPIO_PINS_3|GPIO_PINS_4|GPIO_PINS_5|GPIO_PINS_6|GPIO_PINS_7;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIO_PORT_D, &gpio_init_struct);

    /* configure the CS*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = CS_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(CS_GPIO_PORT, &gpio_init_struct);

    /* configure the RES*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = RES_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(RES_GPIO_PORT, &gpio_init_struct);

    /* configure the WR*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = WR_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(WR_GPIO_PORT, &gpio_init_struct);

    /* configure the D/C*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = D_C_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(D_C_GPIO_PORT, &gpio_init_struct);

    /* configure the RD/E*/
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = RD_E_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(RD_E_GPIO_PORT, &gpio_init_struct);

}