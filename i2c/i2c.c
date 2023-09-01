#include "i2c.h"


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

/***********************************************************************************
 *  Function:       i2c_send_request
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Отправляет команду записи без данных по интерфейсу I2C.
 *
 *  parameters:     unsigned char address         адрес устройства;
 * 
 *  on return:      unsigned char status          = 0 - запись прошла успешно;
 *                                                  1 - произошла ошибка во время записи.
 *
 *************************************************************************************/

unsigned char i2c_send_request(unsigned char address)
{
    unsigned char status = 0;


    return status;
}

/***********************************************************************************
 *  Function:       i2c_read_immediate
 *
 *----------------------------------------------------------------------------------
 *
 *  description:    Считывет данные по интерфейсу I2C без указания их начального адреса.
 *
 *  parameters:     unsigned char address         адрес устройства;
 *                  unsigned char *buffer         указатель на буфер для сохранения данных;
 *                  unsigned char n               количество байт данных;
 *
 *  on return:      unsigned char status          = 0 - чтение прошло успешно;
 *                                                  1 - произошла ошибка во время чтения.
 *
 *************************************************************************************/

unsigned char i2c_read_immediate(unsigned char address, unsigned char *buffer, unsigned char n)
{
    unsigned char status = 0;


    return status;
}

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