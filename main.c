#include "main.h"

i2c_handle_type hi2cx;

uint8_t tx_buf[BUF_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t rx_buf[BUF_SIZE] = {0};

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

/**
  * @brief  compare whether the valus of buffer 1 and buffer 2 are equal.
  * @param  buffer1: buffer 1 address.
            buffer2: buffer 2 address.
  * @retval 0: equal.
  *         1: unequal.
  */
uint32_t buffer_compare(uint8_t* buffer1, uint8_t* buffer2, uint32_t len)
{
  uint32_t i;

  for(i = 0; i < len; i++)
  {
    if(buffer1[i] != buffer2[i])
    {
      return 1;
    }
  }

  return 0;
}



int main()
{
  i2c_status_type i2c_status;
  
  system_clock_config();
  board_led_init ();
  delay_init ();

  board_led_toggle(LED3);
  
  hi2cx.i2cx = I2Cx_PORT;
  i2c_config(&hi2cx);
  
   /* start the request reception process */
    if((i2c_status = i2c_master_transmit(&hi2cx, I2Cx_ADDRESS, tx_buf, BUF_SIZE, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status);
    }

    delay_ms(10);

    /* start the request reception process */
    if((i2c_status = i2c_master_receive(&hi2cx, I2Cx_ADDRESS, rx_buf, BUF_SIZE, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status);
    }

    if(buffer_compare(tx_buf, rx_buf, BUF_SIZE) == 0)
    {
      board_led_toggle(LED3);
    }
    else
    {
      error_handler(i2c_status);
    }
  while (1)
  {
   
  }
}
