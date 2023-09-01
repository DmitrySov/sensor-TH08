#include "TH06.h"

/************************************************************************/
/*  File: TH06.c
 *
 *  Created:  
 *  Author:  
 *
 *  Description:
 *
 *  ���������� ��� ������ � ��������� ��������� � ����������� i2c ��
 *  ����������� ���������� I2C.
 *                                                                     */
/************************************************************************/

#ifndef HIH_C_
#define HIH_C_

/*_____ I N C L U D E S ____________________________________________________*/

//#include "lib\DDT.h"
#include "main.h"

/*_____ M A C R O S ________________________________________________________*/



/*_____ D E F I N I T I O N ________________________________________________*/

#define TH06_ADDRESS           0x80            //  ����� ������� TH06 � ���� I2C;


/*    ������������ ��� ������� ��������� � �����������    */

#define TH_RH_MAX_VALUE      100             //  ������������ �������� ������������� ��������� (%);
#define TH_TEMP_MAX_VALUE    165             //  ... ����������� (��. �);
#define TH_MAX_VALUE         16382           //  ������������ ���������� �������� � "��������";
#define TH_TEMP_SHIFT        40              //  ����� ����������� (��. �);


/*    ��������� ���� ��� ��������� ��������� � �����������    */

#define MEASURE_STOP          0               //  "��������";
#define MEASURE_REQUEST       1               //  "����������� ������� ������� �� ���������";
#define MEASURE_GET_DATA      2               //  "������ ������ � �������";


/*    ������ ��������� ��������   */

#define TH_SET_DELAY_10_MS(DELAY, TEN_MS)    (DELAY) = hih_time_10_ms + (TEN_MS);              //  ��������� ��������;
#define TH_CHECK_DELAY(DELAY)                ((signed char)(hih_time_10_ms - (DELAY)) >= 0)    //  �������� ������� ��������� ��������;


/*    ���������� ����� �����������   */

#define HIH_GRAD_POINTS_RH       5            //  �� ������������� ���������;
#define HIH_GRAD_POINTS_TEMP     5            //  �� �����������;


struct s_hih_table                            //  ��������� ������ � �������������� ���������;
{
  float k_rh[5];
  float b_rh[5];
  float k_temp[5];
  float b_temp[5];
};


/*_____ D E C L A R A T I O N ______________________________________________*/

unsigned char th_data_buff[4];               //  ������ ��� ����������� ��������� �������;
unsigned char th_time_10_ms;                 //  ���������� ��� ������� ��������� ��������;

/*	���������� ���������� ��� ��������� */

unsigned char i2c_write_status;               //  ������ ������ ������� ������� �� I2C;
unsigned char i2c_read_status;                //  ������ ������ ������ � ������� �� I2C;
volatile unsigned char measure_delay;         //  �������� ����� ������� ������;
unsigned char i2c_retry_cnt;                  //  ������� ��������� �������� � ������� �� I2C;
unsigned char measure_retry_cnt;              //  ������� ��������� �������� ���������� ��������;
unsigned short rh_raw, temp_raw;              //  ���������� ���������;

struct s_hih_table hih_table;                 //  ������� � ��������������;
// unsigned char hih_table_update_status;        //  ������ ���������� ������ �����������;


/***********************************************************************************
 *  Function:       th_measure_request
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    ���������� ������� �� ��������� �� ������ TH06_ADDRESS.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char status	  = 0 - ������ ������� ������ �������;
 *                                                  1 - ��������� ������ �� ����� ������.
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
 *  description:    ��������� ���������� ��������� �� ������ HIH_ADDRESS � ��������� �� 
 *                  � ������ hih_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char status          = 0 - ������ ����������� ������ �������;
 *                                                  1 - ��������� ������ �� ����� ������.
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
 *  description:    ��������� ��� ���������� ������ �� ������� th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned char stale_bit       = 0 - ���� ��������� ����� ���������;
 *                                                  1 - ��������� �� ���������.
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
 *  description:    ��������� ��������� ��������� ������������� ��������� �� �������
 *                  th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned short rh_raw_value         ��������� ������� ���������.
 *
 *************************************************************************************/

unsigned short th_get_rh_raw(void)
{
    unsigned short rh_raw_value;
	
    rh_raw_value = th_data_buff[0] << 8;
    rh_raw_value |= th_data_buff[1];
    rh_raw_value &= 0x3FFF;                         //  �������� ��� �������������� ����;
    
    return rh_raw_value;
}

/***********************************************************************************
 *  Function:       th_get_temp_raw
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    ��������� ��������� ��������� ����������� �� ������� th_data_buff.
 *
 *  parameters:     -
 * 
 *  on return:      unsigned short temp_raw_value       ��������� ������� �����������.
 *
 *************************************************************************************/

unsigned short th_get_temp_raw(void)
{
    unsigned short temp_raw_value;
    
    temp_raw_value = th_data_buff[2] << 8;
    temp_raw_value |= th_data_buff[3];
    temp_raw_value = temp_raw_value >> 2;           //  ������� ��� �������������� ����;
    
    return temp_raw_value;
}

/***********************************************************************************
 *  Function:       hih_calc_rh 
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    ������������� ��������� ��������� ������� � ������������� ���������.
 *
 *  parameters:     unsigned short rh_raw_value         ��������� ������� ���������;
 * 
 *  on return:      float rh_value                      ������������� ��������� (%).
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
 *  description:    ������������� ��������� ��������� ������� � �����������.
 *
 *  parameters:     unsigned short temp_raw_value       ��������� ������� �����������;
 * 
 *  on return:      float temp_value			����������� (�C).
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
 *  description:    ������������ ������� � ������������� ��������� hih_table �� ������
 *                  �������������� ������. ��� ������� ������������ ������� 
 *                  �������-�������� �������������.
 *
 *  parameters:     unsigned char n_rh                ���������� ����� ����������� �� 
 *                                                    ���������;
 *                  unsigned char n_temp              ... �� �����������;
 * 
 *  on return:      -
 *
 *************************************************************************************/


#endif /* TH06_C_ */