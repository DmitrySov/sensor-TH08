#include "main.h"


float cTemp;
float humidity;

/*********************/

/********************/
uint8_t command_humidity = 0xE5;
uint8_t value_humidity [3] = {0};

uint8_t command_temperature = 0xE3;
uint8_t value_temperature [3] = {0};

i2c_handle_type hi2cx_m;

int main()
{ 
  i2c_status_type i2c_status;
  system_clock_config();
  board_led_init ();
  delay_init ();

  board_led_toggle(LED3);
  
  
  hi2cx_m.i2cx = I2Cx_PORT;
  i2c_config(&hi2cx_m);
  delay_ms(100);
  
  /*********************************humidity************************/
  if((i2c_status = i2c_master_transmit(&hi2cx_m, 0x80, &command_humidity, 1, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status);
    }
  delay_ms(30);

  /* start the request reception process */
  if((i2c_status = i2c_master_receive(&hi2cx_m, 0x80, value_humidity, 2, I2C_TIMEOUT)) != I2C_OK)
   {
   //  error_handler(i2c_status);
   }
  /**********************************************************/
  
  /*********************************humidity************************/
  if((i2c_status = i2c_master_transmit(&hi2cx_m, 0x80, &command_temperature, 1, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status);
    }
  delay_ms(30);

  /* start the request reception process */
  if((i2c_status = i2c_master_receive(&hi2cx_m, 0x80, value_temperature, 2, I2C_TIMEOUT)) != I2C_OK)
   {
   //  error_handler(i2c_status);
   }
  /**********************************************************/
  humidity = (float)( ((((value_humidity[0] * 256 )+ value_humidity[1]) * 125) / 65536) - 6 );
  
  cTemp = (float)((((value_temperature[0] * 256) + value_temperature[1]) * 175.72) / 65536) - 46.85;
  
  board_led_toggle(LED3);
  while (1)
  {
   
  }
}

