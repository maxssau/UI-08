// dac 4490 routines

#ifndef __ak4490__
#define __ak4490__

#include "dac_ak4490.h"
#include "i2c_soft.h"
#include "audio_configuration.h"

#ifndef true
  #define true 1
#endif

unsigned char DAC4490_InitData[]={134,2,1,255,255,1,0,0,0,0};

void AK4490_Init()
{
  
}

void AK4490_SetVol(unsigned char vol_l,unsigned char vol_r)
{
  char __gain_l=0;
  char __gain_r=0;
  
  if(vol_l<127)
  {
    __gain_l=255-vol_l*2;
  }
  
  if(vol_r<127)
  {
    __gain_r=255-vol_r*2;
  }
  
  i2c_start_cond(true);
  i2c_send_byte(DAC_I2C_ADDRESS,true);
  i2c_send_byte(3,true);
  i2c_send_byte(__gain_l,true);
  i2c_send_byte(__gain_r,true);
  i2c_stop_cond(true);
  
}

void AK4490_SetMute(_Bool __mute)
{
  i2c_start_cond(true);
  i2c_send_byte(DAC4490_I2C_ADDRESS,true);
  i2c_send_byte(1,true);
  if(__mute)
  {
    i2c_send_byte(DAC4490_InitData[1] + 1,true);
  }
  else
  {
    i2c_send_byte(DAC4490_InitData[1] & 0xFE,true);
  }
  i2c_stop_cond(true);
}


void AK4490_SetFilter(unsigned char __filter)
{
  switch(__filter)
  {
    // super slow - default for dsp
    case 0:
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] | 0x1; // set sslow bit
      DAC4490_InitData[1]=DAC4490_InitData[1] & ~(1<<5); //reset SD bit
      DAC4490_InitData[2]=DAC4490_InitData[2] & 0xFE; // reset slow bit
    }
    break;
    
    // Sharp roll-off filter
    case 1:
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & 0xFE; // reset sslow bit
      DAC4490_InitData[1]=DAC4490_InitData[1] & ~(1<<5); //reset SD bit
      DAC4490_InitData[2]=DAC4490_InitData[2] & 0xFE; // reset slow bit
    }
    break;
    
    // Slow roll-off filter
    case 2:
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & 0xFE; // reset sslow bit
      DAC4490_InitData[1]=DAC4490_InitData[1] & ~(1<<5); //reset SD bit
      DAC4490_InitData[2]=DAC4490_InitData[2] | 0x1; // set slow bit
    }
    break;
    
    // Short delay sharp roll off filter
    case 3:
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & 0xFE; // reset sslow bit
      DAC4490_InitData[1]=DAC4490_InitData[1] | (1<<5); //set SD bit
      DAC4490_InitData[2]=DAC4490_InitData[2] & 0xFE; // reset slow bit
    }
    break;
    
    //
    case 4:
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & 0xFE; // reset sslow bit
      DAC4490_InitData[1]=DAC4490_InitData[1] | (1<<5); //set SD bit
      DAC4490_InitData[2]=DAC4490_InitData[2] | 0x1; // set slow bit
    }
    break;
    
  default:
    {
      //if error - skip
    }
  }
  
  // update regs
  i2c_start_cond(true);
  i2c_send_byte(DAC4490_I2C_ADDRESS,true);
  i2c_send_byte(1,true);
  i2c_send_byte(DAC4490_InitData[1],true);
  i2c_send_byte(DAC4490_InitData[2],true);
  i2c_stop_cond(true);
  i2c_start_cond(true);
  i2c_send_byte(DAC4490_I2C_ADDRESS,true);
  i2c_send_byte(5,true);
  i2c_send_byte(DAC4490_InitData[5],true);
  i2c_stop_cond(true);
}


void AK4490_Set_SoundQual(unsigned char __set)
{
  if(__set<4)
  {
    DAC4490_InitData[8]=__set;
    
    //update reg
    i2c_start_cond(true);
    i2c_send_byte(DAC4490_I2C_ADDRESS,true);
    i2c_send_byte(8,true);
    i2c_send_byte(DAC4490_InitData[8],true);
    i2c_stop_cond(true);
  }
};

void AK4490_Set_RL_Inv(unsigned char __inv_l,unsigned char __inv_r)
{
  // check values
  if(__inv_l<2 && __inv_r<2)
  {
    if(__inv_l==1)
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] | 0x80; // set invl bit
    }
    else
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & ~(0x80); // reset invl bit
    }
    
    if(__inv_r==1)
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] | 0x40; // set invl bit
    }
    else
    {
      DAC4490_InitData[5]=DAC4490_InitData[5] & ~(0x40); // reset invl bit
    }
    
    //update reg
    i2c_start_cond(true);
    i2c_send_byte(DAC4490_I2C_ADDRESS,true);
    i2c_send_byte(5,true);
    i2c_send_byte(DAC4490_InitData[5],true);
    i2c_stop_cond(true);
  }
  
};

#endif