#include "TH06.h"

/************************************************************************/
/*  File: TH06.c
 *
 *  Created:  
 *  Author:  
 *
 *  Description:
 *
 *  Библиотека для работы с сенсорами влажности и температуры i2c по
 *  аппаратному интерфейсу I2C.
 *                                                                     */
/************************************************************************/

#ifndef HIH_C_
#define HIH_C_

/*_____ I N C L U D E S ____________________________________________________*/

//#include "lib\DDT.h"
#include "main.h"

/*_____ M A C R O S ________________________________________________________*/



/*_____ D E F I N I T I O N ________________________________________________*/

#define TH06_ADDRESS           0x80            //  адрес сенсора TH06 в сети I2C;


/*    Коэффициенты для расчета влажности и температуры    */

#define TH_RH_MAX_VALUE      100             //  максимальное значение относительной влажности (%);
#define TH_TEMP_MAX_VALUE    165             //  ... температуры (гр. С);
#define TH_MAX_VALUE         16382           //  максимальное измеренное значение в "попугаях";
#define TH_TEMP_SHIFT        40              //  сдвиг температуры (гр. С);


/*    Статусные коды для измерения влажности и температуры    */

#define MEASURE_STOP          0               //  "Ожидание";
#define MEASURE_REQUEST       1               //  "Отправление сенсору команды на измерение";
#define MEASURE_GET_DATA      2               //  "Чтение данных с сенсора";


/*    Отсчет временных задержек   */

#define TH_SET_DELAY_10_MS(DELAY, TEN_MS)    (DELAY) = hih_time_10_ms + (TEN_MS);              //  установка задержки;
#define TH_CHECK_DELAY(DELAY)                ((signed char)(hih_time_10_ms - (DELAY)) >= 0)    //  проверка времени окончания задержки;


/*    Количество точек градуировки   */

#define HIH_GRAD_POINTS_RH       5            //  по относительной влажности;
#define HIH_GRAD_POINTS_TEMP     5            //  по температуре;


struct s_hih_table                            //  структура таблиц с коэффициентами пересчета;
{
  float k_rh[5];
  float b_rh[5];
  float k_temp[5];
  float b_temp[5];
};


/*_____ D E C L A R A T I O N ______________________________________________*/

unsigned char th_data_buff[4];               //  массив для результатов измерений сенсора;
unsigned char th_time_10_ms;                 //  переменная для отсчета временных задержек;

/*	Внутренние переменные для измерений */

unsigned char i2c_write_status;               //  статус записи команды сенсору по I2C;
unsigned char i2c_read_status;                //  статус чтения данных с сенсора по I2C;
volatile unsigned char measure_delay;         //  задержка перед чтением данных;
unsigned char i2c_retry_cnt;                  //  счетчик повторных запросов к сенсору по I2C;
unsigned char measure_retry_cnt;              //  счетчик повторных ожиданий измеренных значений;
unsigned short rh_raw, temp_raw;              //  результаты измерений;

struct s_hih_table hih_table;                 //  таблица с коэффициентами;
// unsigned char hih_table_update_status;        //  статус обновления таблиц градуировки;


/***********************************************************************************
 *  Function:       th_measure_request
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Отправляет команду на измерение по адресу TH06_ADDRESS.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char status	  = 0 - запись команды прошла успешно;
 *                                                  1 - произошла ошибка во время записи.
 *
 *************************************************************************************/

unsigned char th_measure_request(void)
{
    unsigned char status = 0;
    
    status = i2c_send_request(TH06_ADDRESS);
    
    return status;
}

/***********************************************************************************
 *  Function:       th_data_fetch
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Считывает результаты измерения по адресу HIH_ADDRESS и сохраняет их 
 *                  в массив hih_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char status          = 0 - чтение результатов прошло успешно;
 *                                                  1 - произошла ошибка во время чтения.
 *
 *************************************************************************************/

unsigned char hih_data_fetch(void)
{
    unsigned char status = 0;
	
    //status = i2c_read_immediate(HIH_ADDRESS, th_data_buff, 4);
    
    return status;
}

/***********************************************************************************
 *  Function:       th_get_stale_bit 
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Сохраняет бит готовности данных из массива th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char stale_bit       = 0 - было выполнено новое измерение;
 *                                                  1 - измерение не завершено.
 *
 *************************************************************************************/

unsigned char th_get_stale_bit(void)
{
    unsigned char stale_bit = 0;
    
    stale_bit = (th_data_buff[0] & 0x40) >> 6;
    
    return stale_bit;
}

/***********************************************************************************
 *  Function:       th_get_rh_raw
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Сохраняет результат измерения относительной влажности из массива
 *                  th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned short rh_raw_value         показание сенсора влажности.
 *
 *************************************************************************************/

unsigned short th_get_rh_raw(void)
{
    unsigned short rh_raw_value;
	
    rh_raw_value = th_data_buff[0] << 8;
    rh_raw_value |= th_data_buff[1];
    rh_raw_value &= 0x3FFF;                         //  зануляем два неиспользуемых бита;
    
    return rh_raw_value;
}

/***********************************************************************************
 *  Function:       th_get_temp_raw
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Сохраняет результат измерения температуры из массива th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned short temp_raw_value       показание сенсора температуры.
 *
 *************************************************************************************/

unsigned short th_get_temp_raw(void)
{
    unsigned short temp_raw_value;
    
    temp_raw_value = th_data_buff[2] << 8;
    temp_raw_value |= th_data_buff[3];
    temp_raw_value = temp_raw_value >> 2;           //  убираем два неиспользуемых бита;
    
    return temp_raw_value;
}

/***********************************************************************************
 *  Function:       hih_calc_rh 
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Пересчитывает результат измерения сенсора в относительную влажность.
 *
 *  parameters:     unsigned short rh_raw_value         показание сенсора влажности;
 * 
 *  on return:      float rh_value                      относительная влажность (%).
 *
 *************************************************************************************/

float hih_calc_rh(unsigned short rh_raw_value)
{
    float rh_value;
    
    rh_value = (float)rh_raw_value * TH_RH_MAX_VALUE;
    rh_value = (rh_value / TH_MAX_VALUE);
    
    return rh_value;
}

/***********************************************************************************
 *  Function:       th_calc_temp
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Пересчитывает результат измерения сенсора в температуру.
 *
 *  parameters:     unsigned short temp_raw_value       показание сенсора температуры;
 * 
 *  on return:      float temp_value			температура (°C).
 *
 *************************************************************************************/

float th_calc_temp(unsigned short temp_raw_value)
{
    float temp_value;

    temp_value = (float)temp_raw_value * TH_TEMP_MAX_VALUE;
    temp_value = (temp_value / TH_MAX_VALUE) - TH_TEMP_SHIFT;
    
    return temp_value;
}

/***********************************************************************************
 *  Function:       hih_calc_table
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Рассчитывает таблицу с коэфициентами пересчета hih_table на основе
 *                  градуировочных таблиц. Для расчета используются формулы 
 *                  кусочно-линейной аппроксимации.
 *
 *  parameters:     unsigned char n_rh                количество точек градуировки по 
 *                                                    влажности;
 *                  unsigned char n_temp              ... по температуре;
 * 
 *  on return:      -
 *
 *************************************************************************************/


#endif /* TH06_C_ */