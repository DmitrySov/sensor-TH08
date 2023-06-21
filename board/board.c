/*C**************************************************************************
* ????????:         board.c
*----------------------------------------------------------------------------
* Copyright (c) 2022
*----------------------------------------------------------------------------
* RELEASE:
* REVISION:   
*----------------------------------------------------------------------------
* ??????????:
*
*
* ????????:
* 
* 
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "board.h"
/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/


/*_____ D E C L A R A T I O N ______________________________________________*/

/* delay macros */
#define STEP_DELAY_MS                    50

/* at-start led resouce array */
gpio_type *led_gpio_port[LED_NUM]        = {LED2_GPIO, LED3_GPIO, LED4_GPIO};
uint16_t led_gpio_pin[LED_NUM]           = {LED2_PIN, LED3_PIN, LED4_PIN};
crm_periph_clock_type led_gpio_crm_clk[LED_NUM] = {LED2_GPIO_CRM_CLK, LED3_GPIO_CRM_CLK, LED4_GPIO_CRM_CLK};

/* delay variable */
static __IO uint32_t fac_us;
static __IO uint32_t fac_ms;

void board_led_init ( void )
{
  gpio_init_type gpio_init_struct;
  uint32_t i;
  for(i = 0; i < LED_NUM; i++)
    {
      /* enable the led clock */
      crm_periph_clock_enable(led_gpio_crm_clk[i], TRUE);

      /* set default parameter */
      gpio_default_para_init(&gpio_init_struct);

      /* configure the led gpio */
      gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
      gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
      gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
      gpio_init_struct.gpio_pins = led_gpio_pin[i];
      gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
      gpio_init(led_gpio_port[i], &gpio_init_struct);
    }
}

void board_led_toggle(led_type led)
{
  if(led > (LED_NUM - 1))
    return;
  if(led_gpio_pin[led])
    led_gpio_port[led]->odt ^= led_gpio_pin[led];
}

/**********************************
 * @brief board_led
 * @param
 * 1) led - ????? ??????????: LED1, LED2
 * 2) status: false - ?????????; true - ????????
 * @return
*************************************/
void board_led ( led_type led, bool status )
{
	if ( led > ( LED_NUM - 1 ) )
	{
return;
	}

	if ( led_gpio_pin[led] )
	{
		if ( status == false )
		{
		//OFF
			led_gpio_port[led]->scr = led_gpio_pin[led];
		}
		else
		{
		//ON
			led_gpio_port[led]->clr = led_gpio_pin[led];
		}
	}
}


/**
  * @brief  initialize delay function
  * @param  none
  * @retval none
  */
  void delay_init ( void )
{
  /* configure systick */
  systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
  fac_us = system_core_clock / (1000000U);
  fac_ms = fac_us * (1000U);
}


/**
  * @brief  inserts a delay time.
  * @param  nms: specifies the delay time length, in milliseconds.
  * @retval none
  */
void delay_ms (uint16_t nms)
{
  
  uint32_t temp = 0;
  while(nms)
  {
    if(nms > STEP_DELAY_MS)
    {
      SysTick->LOAD = (uint32_t)(STEP_DELAY_MS * fac_ms);
      nms -= STEP_DELAY_MS;
    }
    else
    {
      SysTick->LOAD = (uint32_t)(nms * fac_ms);
      nms = 0;
    }
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
      temp = SysTick->CTRL;
    }while((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
  }
 
}
