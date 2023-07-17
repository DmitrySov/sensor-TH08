#include "main.h"


int cTemp;
int humidity;

uint8_t command = 0xE5;
uint8_t value_sensor [3] = {0};
i2c_handle_type hi2cx;

void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2Cx_PORT)
  {
    /* i2c periph clock enable */
    crm_periph_clock_enable(I2Cx_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SDA_GPIO_CLK, TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2Cx_SCL_PIN;
    gpio_init(I2Cx_SCL_GPIO_PORT, &gpio_initstructure);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2Cx_SDA_PIN;
    gpio_init(I2Cx_SDA_GPIO_PORT, &gpio_initstructure);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2Cx_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2Cx_ADDRESS);
  }
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
  delay_ms(100);
  
  if((i2c_status = i2c_master_transmit(&hi2cx, 0x80, &command, 1, I2C_TIMEOUT)) != I2C_OK)
    {
      error_handler(i2c_status);
    }
  delay_ms(30);

  /* start the request reception process */
  if((i2c_status = i2c_master_receive(&hi2cx, 0x80, value_sensor, 2, I2C_TIMEOUT)) != I2C_OK)
   {
     error_handler(i2c_status);
   }
  
  float cTemp = ((((value_sensor[0] * 256) + value_sensor[1]) * 175.72) / 65536) - 46.85;
	 			int fTemp = ( cTemp * 1.8 )+ 32;
  board_led_toggle(LED3);
  humidity = ((((value_sensor[0] * 256 )+ value_sensor[1]) * 125) / 65536) - 6;
  fTemp = ( cTemp * 1.8 )+ 32;
  while (1)
  {
   
  }
}
