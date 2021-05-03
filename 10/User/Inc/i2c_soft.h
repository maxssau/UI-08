// i2c soft routines

#ifndef __i2c__soft__h__
#define __i2c__soft__h__ 1

#include "stm32f4xx_hal.h"

/*
I2C_port_active
0 - for DSP, EEPROM, Display
1 - for DAC
*/

//_Bool I2C_port_active=0;

void Delay_us (uint32_t __IO us);
void SCL_in (_Bool) ;
void SCL_out (_Bool);
void SDA_in (_Bool);
void SDA_out (_Bool);
void i2c_stop_cond (_Bool);
void i2c_init (_Bool);
void i2c_start_cond (_Bool);
void i2c_restart_cond (_Bool);
void SCL_O(_Bool __port);
void SDA_O(_Bool __port);

uint8_t i2c_send_byte (uint8_t data,_Bool);
uint8_t i2c_get_byte (uint8_t last_byte,_Bool);

GPIO_PinState SCL_I(_Bool port);
GPIO_PinState SDA_I(_Bool port);

#endif