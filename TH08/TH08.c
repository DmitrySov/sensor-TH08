/*C**************************************************************************
* ????????:         TH08.c
*----------------------------------------------------------------------------
* Copyright (c) 2023
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
#include "TH08.h"
/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/

/*_____ D E C L A R A T I O N ______________________________________________*/

extern int cTemp;
extern int humidity;

i2c_handle_type hi2cx_th08;
i2c_status_type i2c_status_th08;

/**
  * @brief  error handler program
  * @param  i2c_status
  * @retval none
  */
void error_handler(uint32_t error_code)
{
  while(1)
  {
   // at32_led_toggle(LED2);
    delay_ms(500);
  }
}

void tt_i2c_write(uint8_t slaveAddr, uint8_t regAddr)
{
	uint8_t buf[1];

	buf[0] = regAddr;
	//buf[1] = 0;
	 /* start the request reception process */
    if((i2c_status_th08 = i2c_master_transmit(&hi2cx_th08, slaveAddr, buf, 1, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status_th08);
    }
	return ;
}

uint8_t tt_i2c_read(uint8_t slaveAddr)
{
	uint8_t data;
	/* start the request reception process */
    if((i2c_status_th08 = i2c_master_receive(&hi2cx_th08, slaveAddr, &data, BUF_SIZE, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status_th08);
    }
	return data;
}



void MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE (void)
 {
	 uint32_t data1;
	 uint32_t data2;

	 // Send Relative humidity measurement command, NO HOLD MASTER(0xF5)

	 		tt_i2c_write(SI7006_ADDRESS, SI7006_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE);

	 // for time delay
       // k_sleep(K_MSEC(1000));

	 // Read 2 bytes of humidity data

	 // humidity msb, humidity lsb

	 		data1 = tt_i2c_read(SI7006_ADDRESS);
	        data2 = tt_i2c_read(SI7006_ADDRESS);

	 		//printf("data1 : 0x%02x\n",data1);
	 		//printf("data2 : 0x%02x\n",data2);

	 // Convert the data

	 			 humidity = ((((data1 * 256 )+ data2) * 125) / 65536) - 6;



	 // Output data to screen
	 			//printk("FOR NO HOLD MASTER MODE\n");
	 			//printk("Relative Humidity : %02d percentage\n", humidity);


 }

 void MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE (void)
 {
	 uint32_t data3;
     uint32_t data4;

	 // Send temperature measurement command, NO HOLD MASTER(0xF3)

	tt_i2c_write(SI7006_ADDRESS, SI7006_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE);

	 // For time delay
        delay_ms(10);
	 		
	 // Read 2 bytes of temperature data

	 // humidity msb, humidity lsb


	 	         data3 =	tt_i2c_read(SI7006_ADDRESS);
	 	         data4 =	tt_i2c_read(SI7006_ADDRESS);

	 	        //printf("data3 : 0x%02x\n",data3);
	 	        //printf("data4 : 0x%02x\n",data4);


	 // Convert the data

	 			 cTemp = ((((data3 * 256) + data4) * 175.72) / 65536) - 46.85;
	 			int fTemp = ( cTemp * 1.8 )+ 32;

	 // Output data to screen
	 			/*printk("FOR NO HOLD MASTER MODE\n");
	 			printk("Temperature in Celsius : %02d C \n", cTemp);
	 			printk("Temperature in Fahrenheit : %02d F \n", fTemp);*/


 }


void si7006(void)
{
 
    MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE ();

	MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE ();
}