/**
  **************************************************************************
  * @file     at32f403a_407_clock.c
  * @brief    system clock config program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to 
  * download from Artery official website is the copyrighted work of Artery. 
  * Artery authorizes customers to use, copy, and distribute the BSP 
  * software and its related documentation for the purpose of design and 
  * development in conjunction with Artery microcontrollers. Use of the 
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "at32f403a_407_clock.h"

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         - system clock        = hext * pll_mult
  *         - system clock source = pll (hext)
  *         - hext                = 8000000
  *         - sclk                = 224000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 224000000
  *         - apb1div             = 2
  *         - apb1clk             = 112000000
  *         - apb2div             = 2
  *         - apb2clk             = 112000000
  *         - pll_mult            = 28
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
void system_clock_config(void)
{
  /* reset crm */
  crm_reset();

  /* enable hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HEXT, CRM_PLL_MULT_28, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}

/*F**************************************************************************
* ��������: hick_clockPll_system_clock_config
*----------------------------------------------------------------------------
* ���������:
* f_pep - ������� ��� � ���
* �����:
* 
*----------------------------------------------------------------------------
* ����������:
*----------------------------------------------------------------------------
* �������:
*----------------------------------------------------------------------------
* ��������:
* ��������� ������������, �������� ������� PLL - RC ���������
* �� ������ PLL ������� ������������ � (f_pep* 1���)
*----------------------------------------------------------------------------
* ����������:
****************************************************************************/
void hick_clock_Pll_system_clock_config(uint16_t f_pep)
{
  /* reset crm */
  crm_reset();

  /* enable hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);
   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }
  
    /* enable hick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);
   /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET)
  {
  }

  /* config pll clock resource */
  crm_pll_mult_type MULT=(crm_pll_mult_type)((f_pep>>2)-1);
  crm_pll_config(CRM_PLL_SOURCE_HICK, MULT, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}

/*F**************************************************************************
* ��������: hext_clock_Pll_system_clock_config
*----------------------------------------------------------------------------
* ���������:
* f_pep - ������� ��� � ���
* �����:
* 
*----------------------------------------------------------------------------
* ����������:
*----------------------------------------------------------------------------
* �������:
*----------------------------------------------------------------------------
* ��������:
* ��������� ������������, �������� ������� PLL - ������� �����
* �� ������ PLL ������� ������������ � (f_pep* 1���)
*----------------------------------------------------------------------------
* ����������:
****************************************************************************/
void hext_clock_Pll_system_clock_config(uint16_t f_pep)
{
  /* reset crm */
  crm_reset();

  /* enable hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);
   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

    /* enable hick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);
   /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET)
  {
  }

  /* config pll clock resource */
  //crm_pll_config(CRM_PLL_SOURCE_HEXT, CRM_PLL_MULT_30, CRM_PLL_OUTPUT_RANGE_GT72MHZ);
  crm_pll_mult_type MULT=(crm_pll_mult_type)((f_pep>>2)-1);
  crm_pll_config(CRM_PLL_SOURCE_HEXT, MULT, CRM_PLL_OUTPUT_RANGE_GT72MHZ);
  CRM->cfg_bit.pllhextdiv = TRUE;
  //set hext clock division
  crm_hext_clock_div_set(CRM_HEXT_DIV_2);
  
  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}

/*F**************************************************************************
* ��������: mx_adc_clock_init
*----------------------------------------------------------------------------
* ���������:
*
* �����:
* 
*----------------------------------------------------------------------------
* ����������:
*----------------------------------------------------------------------------
* �������:
*----------------------------------------------------------------------------
* ��������:
* ��������� ������� ������������ ���, � ����������� �� ������� PLL
*----------------------------------------------------------------------------
* ����������:
****************************************************************************/
void mx_adc_clock_init(void)
{
  const uint32_t MAX_ADC_FREQ=20000000;
  crm_clocks_freq_type freq_struct = {0};
  crm_clocks_freq_get(&freq_struct);
  crm_adc_div_type DIV=CRM_ADC_DIV_16;
  if(freq_struct.adc_freq>MAX_ADC_FREQ){
    float f=(float)freq_struct.apb2_freq/(float)MAX_ADC_FREQ;
    uint16_t i=((uint16_t)(f+0.5));
    switch(i)
    {
      case 2:
        DIV=CRM_ADC_DIV_2;
      break;
      case 4:
        DIV=CRM_ADC_DIV_4;
      break;  
      case 6:
        DIV=CRM_ADC_DIV_6;
      break;      
      case 8:
        DIV=CRM_ADC_DIV_8;
      break;   
      case 12:
        DIV=CRM_ADC_DIV_12;
      break;   
      case 16:
        DIV=CRM_ADC_DIV_16;
      break;      
    }
  }
  
  crm_adc_clock_div_set(DIV);

  
}

