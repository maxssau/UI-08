#ifndef __i2c__soft__c__
#define __i2c__soft__c__ 1

#include "stm32f4xx_hal.h"
#include "i2c_soft.h"
#include "audio_configuration.h"

void SCL_O(_Bool __port)
{
  if(__port)
  {
    HAL_GPIO_WritePin(DAC_SCL_PORT, DAC_SCL_PIN, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(DSP_SCL_PORT, DSP_SCL_PIN, GPIO_PIN_RESET);
  }
}

void SDA_O(_Bool __port)
{
  if(__port)
  {
    HAL_GPIO_WritePin(DAC_SDA_PORT, DAC_SDA_PIN, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(DSP_SDA_PORT, DSP_SDA_PIN, GPIO_PIN_RESET);
  }
}

GPIO_PinState SCL_I(_Bool port)
{
  if(port)
  {
    return HAL_GPIO_ReadPin(DAC_SCL_PORT, DAC_SCL_PIN);
  }
  else
  {
    return HAL_GPIO_ReadPin(DSP_SCL_PORT, DSP_SCL_PIN);
  };
}

GPIO_PinState SDA_I(_Bool port)
{
  if(port)
  {
    return HAL_GPIO_ReadPin(DAC_SDA_PORT, DAC_SDA_PIN);
  }
  else
  {
    return HAL_GPIO_ReadPin(DSP_SDA_PORT, DSP_SDA_PIN);
  };
}

volatile uint8_t i2c_frame_error=0; 

void Delay_us (uint32_t __IO us)
{
  us *=(SystemCoreClock/1000000)/5;
  while(us--);
}

void SCL_in (_Bool __port) 
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(__port)
  {
    GPIO_InitStruct.Pin = DAC_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DAC_SCL_PORT, &GPIO_InitStruct);
  }
  else
  {
    GPIO_InitStruct.Pin = DSP_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DSP_SCL_PORT, &GPIO_InitStruct);
  }
}

void SCL_out (_Bool __port)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(__port)
  {
    GPIO_InitStruct.Pin = DAC_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DAC_SCL_PORT, &GPIO_InitStruct);
  }
  else
  {
    GPIO_InitStruct.Pin = DSP_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DSP_SCL_PORT, &GPIO_InitStruct);
  }
  SCL_O(__port);
}
void SDA_in (_Bool __port)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(__port)
  {
    GPIO_InitStruct.Pin = DAC_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DAC_SDA_PORT, &GPIO_InitStruct);
  }
  else
  {
    GPIO_InitStruct.Pin = DSP_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DSP_SDA_PORT, &GPIO_InitStruct);
  }
}

void SDA_out (_Bool __port)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(__port)
  {
    GPIO_InitStruct.Pin = DAC_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DAC_SDA_PORT, &GPIO_InitStruct);
  }
  else
  {
    GPIO_InitStruct.Pin = DSP_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DSP_SDA_PORT, &GPIO_InitStruct);
  }
  SDA_O(__port);
}

void i2c_stop_cond (_Bool __port)
{
  uint16_t SCL, SDA;
  SCL_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SDA_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);

  SCL_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SDA_in(__port); 
  Delay_us(DSP_I2C_SOFT_DELAY);
    		
  i2c_frame_error=0;	
  SCL=SCL_I(__port);
  SDA=SDA_I(__port);
  if (SCL == 0) i2c_frame_error++; 
  if (SDA == 0) i2c_frame_error++;
  Delay_us(DSP_I2C_SOFT_DELAY*4);
}

void i2c_init (_Bool __port)
{
    i2c_stop_cond(__port);
    i2c_stop_cond(__port);
}

void i2c_start_cond (_Bool __port)
{
  SDA_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
}

void i2c_restart_cond (_Bool __port)
{
  SDA_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SDA_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
}

uint8_t i2c_send_byte (uint8_t data,_Bool __port)
{   
  uint8_t i;
  uint8_t ack=1;
  uint16_t SDA;   
  for (i=0;i<8;i++)
  {
    if (data & 0x80) 
    {
      SDA_in(__port);
    }
    else 
    {
      SDA_out(__port);
    }
    Delay_us(DSP_I2C_SOFT_DELAY);
    SCL_in(__port);
    Delay_us(DSP_I2C_SOFT_DELAY);
    SCL_out(__port);
    data<<=1;			
  }
  SDA_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SDA=SDA_I(__port);
  if (SDA==0x00) ack=1; else ack=0;
  SCL_out(__port);
  return ack;
}

uint8_t i2c_get_byte (uint8_t last_byte,_Bool __port)
{
  uint8_t i, res=0;
  uint16_t SDA;
  SDA_in(__port);

  for (i=0;i<8;i++)
  {
    res<<=1;
    SCL_in(__port);
    Delay_us(DSP_I2C_SOFT_DELAY);
    SDA_in(__port);
    SDA=SDA_I(__port);
    if (SDA==1)
    {
      res=res|0x01;
    }
    SCL_out(__port);
    Delay_us(DSP_I2C_SOFT_DELAY);
  }
  if (last_byte==0)
  {
    SDA_out(__port);
  }
  else
  {
    SDA_in(__port);
  }
  
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_in(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SCL_out(__port);
  Delay_us(DSP_I2C_SOFT_DELAY);
  SDA_in(__port);
  return res;
}


#endif