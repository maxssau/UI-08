#ifndef __eeprom__c__
#define __eeprom__c__

#include "eeprom.h"
#include "i2c_soft.h"

#ifndef false
#define false 0
#endif

char EEPROM_Read_Byte(char chip_address,int data_address)
{
  _Bool __bus=false;
  char __tmp=0;
  i2c_start_cond(__bus);
  i2c_send_byte(chip_address,__bus);
  __tmp=i2c_get_byte(1,__bus);
  i2c_stop_cond(__bus);
}

void EEPROM_Write_Byte(char chip_address, int data_address, char data)
{
  _Bool __bus=false;
  i2c_start_cond(__bus);
  i2c_send_byte(chip_address,__bus);
  i2c_send_byte((data_address & 0xFF00)>>8,__bus);
  i2c_send_byte(data_address & 0xFF,__bus);
  i2c_send_byte(data,__bus);
  i2c_stop_cond(__bus);
}

#endif