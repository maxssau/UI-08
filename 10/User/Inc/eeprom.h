#ifndef __eeprom__h__
#define __eeprom__h__

#define EEPROM_ADDRESS

char EEPROM_Read_Byte(char chip_address,int data_address);
void EEPROM_Write_Byte(char chip_address, int data_address, char data);
void EEPROM_Write_Array(char chip_address, int data_address, char *data,unsigned int length);


#endif