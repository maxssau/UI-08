
#include <math.h>

#include "usb_audio.h"
#include "audio_configuration.h"
#include "usbd_audio_if.h"
#include "usbd_desc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

#include "eeprom.h"

#include "udsp01.h"

#include "i2c_soft.h"
_Bool I2C_port_active;

#include "dac_ak4490.h"

#include "st7735.h"

#include "dsp8b.h"
#include "dsp8b_gray.h"

#include "eq8b.h"
#include "eq8b_gray.h"

#include "set8b.h"
#include "set8b_gray.h"

#include "stat8b.h"
#include "stat8b_gray.h"

#include "ui08_menu.h"

#define __debug 1

#define DAC_AK4490 1

void DAC_write_volume_l(double dBGain);
void DAC_write_volume_r(double dBGain);
void Screen_Draw_DSP_Menu(unsigned char);
void __debug_screen_enc(char __enc);

void SIGMA_WRITE_REGISTER_INTEGER(int address, int32_t pData);
void SIGMA_WRITE_REGISTER_FLOAT(int address, double pData);
void SIGMASTUDIOTYPE_REGISTER_CONVERT(int32_t fixpt_val, uint8_t dest[4]);
int32_t SIGMASTUDIOTYPE_FIXPOINT_CONVERT(double);
int SIGMASTUDIOTYPE_FIXPOINT_CONVERT(double value);

void DSP_write_volume_r(double dBGain);
void DSP_write_volume_l(double dBGain);
void DSP_write_temb_lpf(double freq,double dbGain);
void Screen_DrawVolume(void);

void DSP_Mute(bool Mute);
void DAC_Mute(bool Mute);
char Encoder_Action(void);

int __tmp=0;

void DSP_Natural_Sound(bool);

void uDSP01_ButtonActions(int Screen, unsigned short ButtonState);


#ifdef __debug

int32_t __debug_gpiob_moder;
int32_t __debug_gpiob_otyper;
int32_t __debug_gpiob_ospeedr;
int32_t __debug_gpiob_pupdr;
int32_t __debug_gpiob_afr0;
int32_t __debug_gpiob_afr1;

int32_t __debug_gpioa_moder;
int32_t __debug_gpioa_otyper;
int32_t __debug_gpioa_ospeedr;
int32_t __debug_gpioa_pupdr;
int32_t __debug_gpioa_afr0;
int32_t __debug_gpioa_afr1;

int32_t __debug_rcc_ahb1enr;
int32_t __debug_rcc_ahb2enr;
int32_t __debug_rcc_apb1enr;
int32_t __debug_rcc_cr;
int32_t __debug_rcc_cfgr;
int32_t __debug_rcc_pllcfgr;
int32_t __debug_i2c3_cr1;
int32_t __debug_i2c3_cr2;
int32_t __debug_i2c3_ccr;
int32_t __debug_i2c3_trise;
int32_t __debug_i2c3_dr;
int32_t __debug_i2c3_oar1;
int32_t __debug_i2c3_oar2;
int32_t __debug_i2c3_sr1;
int32_t __debug_i2c3_sr2;

int32_t __debug_time3_ccer;
int32_t __debug_time3_ccmr1;
int32_t __debug_time3_smcr;
int32_t __debug_time3_cr1;
int32_t __debug_time3_cr2;
int32_t __debug_time3_sr;

#endif

int menu_current_item;



double dsp_volume_l=0;
double dsp_volume_r=0;


int LCD_NeedUpdate=1;
bool Screen_NeedUpdate=true;
uint32_t LCD_I2S_AudioFrequency=0;
uint8_t LCD_I2S_AudioResolution=0;
char DSP_NeedUpdate=0;
char LCD_UpdateInProgress=0;

bool Mute=false;
bool Mute_last=false;
int Mute_btn_state_last=0;

bool Natural_Sound=false;

uint32_t DSP_Last_AudioFrequency=0;

int Screen_Current=0;
int Screen_Selected_Item=0;
int Screen_Setting=0;

char __buff[256]; 

bool Screen_Temb_Edit_HPF_Active=false;
bool Screen_Temb_Edit_LPF_Active=false;
bool Screen_Nat_Active=false;
bool Screen_HP_out=false;

void Buttons_Check(void);

void Screen_Draw(int);
void Screen_Draw_Top_Bar(int);
void Screen_Draw_Bot_Bar(int);

int uDSP01_CTRL_BTN_ENC=0;
int uDSP01_CTRL_BTN_ENC_last=1;

int uDSP01_CTRL_BTN_1=0;
int uDSP01_CTRL_BTN_1_last=1;

int uDSP01_CTRL_BTN_2=0;
int uDSP01_CTRL_BTN_2_last=1;

int uDSP01_CTRL_BTN_3=0;
int uDSP01_CTRL_BTN_3_last1;

int uDSP01_CTRL_BTN_4=0;
int uDSP01_CTRL_BTN_4_last=1;



uint32_t ENC_Button_Delay=100;
uint32_t ENC_Button_tick_last=0;
uint32_t ENC_Jog_tick_last=0;

uint32_t BTN_ctrl_tick_last=0;
uint32_t BTN_ctrl1_tick_last=0;
uint32_t BTN_ctrl2_tick_last=0;
uint32_t BTN_ctrl3_tick_last=0;
uint32_t BTN_ctrl4_tick_last=0;


int ERR_I2C=0;

USBD_HandleTypeDef USBD_Device;
extern USBD_AUDIO_InterfaceCallbacksfTypeDef audio_class_interface;

// i2c
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;
SPI_HandleTypeDef ST7735_SPI_PORT;
uint32_t __encoder_data,__encoder_data_last=1;

void SystemClock_Config(void);
void Init_Encoder(void);
void LCD_Update(void);
void GPIO_Init(void);
void SIGMA_WRITE_REGISTER_BLOCK4(int devAddress, int address,unsigned int length, uint8_t *pData);
void SIGMA_WRITE_REGISTER_BLOCK1(int devAddress, int address,unsigned int length, uint8_t *pData);
void SIGMA_WRITE_REGISTER_BLOCK2(int devAddress, int address,unsigned int length, uint8_t *pData);

void SIGMA_WRITE_REGISTER_BLOCK(int devAddress, int address,unsigned int length, uint8_t *pData);


void DSP_Update(void);
void DAC_Update(void);
void default_download_IC96(void);
void default_download_IC48(void);
void Init_ST7735(void);
void uDSP01_CTRL_BRD_Init(void);
void default_download_IC44(void);
void default_download_IC48(void);
void default_download_IC88(void);
void default_download_IC96(void);


//dac_4490 __ak4490;

char DAC_InitData[]={134,34,0,255,255,0,0,0,0,0};

//char DAC_InitData[]={0x8F,0xA,0,0xff,0xff,0x80,130,0,0,0,0};

unsigned short udsp01_btn_status=0;
unsigned short udsp01_btn_status_last=0;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_Encoder_InitTypeDef encoder;
TIM_HandleTypeDef timer;

int err_count;
int err_count_over=0;
int err_success_writes=0;

#include "2444_IC44.h"
#include "2444_IC44_PARAM.h"
#include "2448_IC48.h"
#include "2448_IC48_PARAM.h"
#include "2488_IC88.h"
#include "2488_IC88_PARAM.h"
#include "2496_IC96.h"
#include "2496_IC96_PARAM.h"

void uDSP01_CTRL_BRD_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = uDSP01_CTRL_BTN_1_pin | uDSP01_CTRL_BTN_2_pin | uDSP01_CTRL_BTN_ENC_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(uDSP01_CTRL_BTN_1_port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin=0;
  GPIO_InitStruct.Pin = uDSP01_CTRL_BTN_3_pin | uDSP01_CTRL_BTN_4_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(uDSP01_CTRL_BTN_3_port, &GPIO_InitStruct);  
}




void SIGMA_WRITE_REGISTER_BLOCK(int devAddress, int address,unsigned int length, uint8_t *pData)
{
  I2C_port_active=false;
  i2c_start_cond(I2C_port_active);  
  if(i2c_send_byte(devAddress,I2C_port_active))
  {
    err_success_writes++;
  }
  else
  {
    err_count++;
  };
  if(i2c_send_byte((address & 0xFF00)>>8,I2C_port_active))
  {
    err_success_writes++;
  }
  else
  {
    err_count++;
  };
  if(i2c_send_byte(address & 0xFF,I2C_port_active))
  {
    err_success_writes++;
  }
  else
  {
    err_count++;
  };
  
  for(unsigned int i=0;i<length;i++)
  {
    if(i2c_send_byte(pData[i],I2C_port_active))
    {
      err_success_writes++;
    }
    else
    {
      err_count++;
    };
  }
  
  i2c_stop_cond(I2C_port_active);
}

int main(void)
{
  HAL_Init();

  USB_I2S_Init();

  __HAL_RCC_I2C3_CLK_ENABLE();
  __HAL_RCC_I2C1_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_SPI3_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  I2C_port_active=false;
  i2c_init(I2C_port_active);
  I2C_port_active=true;
  i2c_init(I2C_port_active);
  
  uDSP01_CTRL_BRD_Init();
  Init_ST7735();
  ST7735_Init();
  
  //HAL_GPIO_WritePin(DSP_RESET_PORT, DSP_RESET_PIN,GPIO_PIN_SET);
  HAL_Delay(DSP_RESET_PAUSE);
  
  ST7735_FillRectangle(0,0,160,19,0x0);
  
  Init_Encoder();
  

  USBD_Init(&USBD_Device, &AUDIO_Desc, 0);
  //InitDelay();
  //USB
  //аудио конфигурация
  AudioConfig_Init();
  OUTClk_Init();
  //USB
  
  USBD_RegisterClass(&USBD_Device, USBD_AUDIO_CLASS);
  USBD_AUDIO_RegisterInterface(&USBD_Device, &audio_class_interface);
  USBD_Start(&USBD_Device);
  
  LCD_NeedUpdate=1;
  
  ST7735_FillRectangle(0,0,160,128,0xffff);
  Screen_Draw(Screen_Current);
  
  while (1)
  {
    
    __WFI();
    if(LCD_NeedUpdate==1)
    {
      LCD_Update();
      LCD_NeedUpdate=0;
    };
    
    if(DSP_NeedUpdate==1)
    {
      DSP_Update();
      DSP_NeedUpdate=0;
    }
    
    Buttons_Check();
    
    
    
        /*
      Encoder button pressed, change screen global
      Overall 4 screens: stat, dsp, eq, opt
    */
    
    if(HAL_GetTick()-ENC_Button_tick_last>ENC_Button_Delay)
    {
      if (uDSP01_CTRL_BTN_ENC==GPIO_PIN_RESET)
      {
        if(uDSP01_CTRL_BTN_ENC_last==GPIO_PIN_SET)
        {
          // screen change
          uDSP01_CTRL_BTN_ENC_last=GPIO_PIN_RESET;
          
          Screen_Current++;
          if(Screen_Current>3)
          {
            Screen_Current=0;
          }
          menu_current_item=0;
          Screen_Setting=0;
          Screen_Draw(Screen_Current);
        } 
      };
      uDSP01_CTRL_BTN_ENC_last=uDSP01_CTRL_BTN_ENC;
      ENC_Button_tick_last=HAL_GetTick();
    }
    
    //read btn status
    
    /*
      mute 
      btn1      0xd
      btn2      0xb
      btn3      0x7
  */
    
    /*udsp01_btn_status=0;
    if(HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_1_port,uDSP01_CTRL_BTN_1_pin)==GPIO_PIN_SET)
    {
      udsp01_btn_status=udsp01_btn_status+1;
    };
    if(HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_2_port,uDSP01_CTRL_BTN_2_pin)==GPIO_PIN_SET)
    {
      udsp01_btn_status=udsp01_btn_status+2;
    };  
    if(HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_3_port,uDSP01_CTRL_BTN_3_pin)==GPIO_PIN_SET)
    {
      udsp01_btn_status=udsp01_btn_status+4;
    };
    if(HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_4_port,uDSP01_CTRL_BTN_4_pin)==GPIO_PIN_SET)
    {
      udsp01_btn_status=udsp01_btn_status+8;
    };
    
    //sprintf(__buff, "Btn st=0x%x     ",udsp01_btn_status);
    //ST7735_WriteString(10,30,__buff,Font_11x18, ST7735_RED, ST7735_BLACK);
    
    // buttons action
    if(udsp01_btn_status_last!=udsp01_btn_status)
    {
      if(HAL_GetTick()-BTN_ctrl_tick_last>uDSP01_Ctrl_Button_Timeout)
      {
        
        // update button actions
        uDSP01_ButtonActions(Screen_Current, udsp01_btn_status);
        udsp01_btn_status_last=udsp01_btn_status;
        BTN_ctrl_tick_last=HAL_GetTick();
      }
    }
    */
    
    
    /*if(udsp01_btn_status!=udsp01_btn_status_last)
    {
      sprintf(__buff, "Btn st=0x%x",udsp01_btn_status);
      ST7735_WriteString(10,30,__buff,Font_11x18, ST7735_RED, ST7735_BLACK);
      udsp01_btn_status_last=udsp01_btn_status;
    }*/
    char __enc_state=Encoder_Action();
    if(__enc_state!=0)
    {
      switch(Screen_Current)
      {
      case 0:
        {
        }
        break;
      case 1:
        {
          sprintf(__buff, "ENC=%i",__enc_state);
          ST7735_WriteString(1,82,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
          //dsp menu
          switch(__enc_state)
          {
          case 0:
            {
              // no action
            }
            break;
          case 1:
            {
              // up menu
              menu_current_item++;
              if(menu_current_item>12)
              {
                menu_current_item=12;
              }
            }
            break;
          case 255:
            {
              // down menu
              menu_current_item--;
              if(menu_current_item<0)
              {
                menu_current_item=0;
              }
            }
            break;
          };
          
          // plot menu
          Screen_Draw_DSP_Menu(menu_current_item);
          
        }
        break;
      case 2:
        {
        }
        break;
      case 3:
        {
        }
        break;
      }
    }
  
    if(Screen_NeedUpdate)
    {
      Screen_NeedUpdate=false;
      Screen_Draw(Screen_Current);
    }
  }
}

char Encoder_Action()
{
  char res=0;
  __encoder_data = TIM3->CNT;
      
    if(__encoder_data!=__encoder_data_last)
    {
      if(__encoder_data>__encoder_data_last)
      {
        if(__encoder_data_last<10 & __encoder_data>65000)
        {
          res=-1;
        }
        else
        {
          res=1;
        }
      }
      else
      {
        if(__encoder_data_last<10 & __encoder_data>65000)
        {
          res=1;
        }
        else
        {
          res=-1;
        }
      }
    }
    else
    {
      
      res=0;
    }
    __encoder_data_last=__encoder_data;
    return res;
      
    /*  if(Screen_Current==0)
      {
        if(Screen_Temb_Edit_LPF_Active==false & Screen_Temb_Edit_HPF_Active==false)
        {
          double __delta=0.5;
          
          uint32_t __tick=HAL_GetTick()-ENC_Jog_tick_last;
          
          //__delta=200*(1/__tick);
          
          if(__tick<ENC_JOG_TIME_1)
          {
            __delta=1;
          }
          
          if(__tick<ENC_JOG_TIME_2 & __tick>=ENC_JOG_TIME_1)
          {
            __delta=0.5;
          }
          
          if(__tick>ENC_JOG_TIME_3)
          {
            __delta=0.5;
          }
          
          if(__encoder_data_last>__encoder_data)
          {
            if(__encoder_data_last<10 & __encoder_data>65000)
            {
              dsp_volume_r-=__delta;
              dsp_volume_l-=__delta;
            }
            dsp_volume_r-=__delta;
            dsp_volume_l-=__delta;
          }
          else
          {
            if(__encoder_data_last<10 & __encoder_data>65000)
            {
              dsp_volume_r+=__delta;
              dsp_volume_l+=__delta;
            }
            dsp_volume_r+=__delta;
            dsp_volume_l+=__delta;
          }
          
          if(dsp_volume_r>0)
          {
            dsp_volume_r=0;
          }
          
          if(dsp_volume_r<-127)
          {
            dsp_volume_r=-127;
          }
          
          if(dsp_volume_l>0)
          {
            dsp_volume_l=0;
          }
          
          if(dsp_volume_l<-127)
          {
            dsp_volume_l=-127;
          }
          
          __encoder_data_last=__encoder_data;
          //test mode - only volume
          
          DAC_write_volume_r(dsp_volume_r);
          DAC_write_volume_l(dsp_volume_l);
        }
        Screen_DrawVolume();
        ENC_Jog_tick_last=HAL_GetTick();
        
      }
    }  */
    
      


};

void __debug_screen_enc(char __enc)
{
    switch(Screen_Current)
      {
      case 0:
        {
          //info screen
        }
        break;
      case 1:
        {
          //dsp screen
          sprintf(__buff, "enc: %d    ",__enc);
          ST7735_WriteString(1,30,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
        }
        break;
      case 2:
        {
          //eq screen
        }
        break;
      case 3:
        {
          // set screen
        }
        break;
      }
};

void Init_ST7735(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = MCLK_SCALE_PIN | DSP_PLL_MODE_0_PIN | ST7735_RES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MCLK_SCALE_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = ST7735_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_DC_GPIO_Port, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = ST7735_LED_Pin | DSP_RESET_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_LED_GPIO_Port, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  
  ST7735_SPI_PORT.Instance = SPI3;
  ST7735_SPI_PORT.Init.Mode = SPI_MODE_MASTER;
  ST7735_SPI_PORT.Init.Direction = SPI_DIRECTION_1LINE;
  ST7735_SPI_PORT.Init.DataSize = SPI_DATASIZE_8BIT;
  ST7735_SPI_PORT.Init.CLKPolarity = SPI_POLARITY_LOW;
  ST7735_SPI_PORT.Init.CLKPhase = SPI_PHASE_1EDGE;
  ST7735_SPI_PORT.Init.NSS = SPI_NSS_SOFT;
  ST7735_SPI_PORT.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  ST7735_SPI_PORT.Init.FirstBit = SPI_FIRSTBIT_MSB;
  ST7735_SPI_PORT.Init.TIMode = SPI_TIMODE_DISABLED;
  ST7735_SPI_PORT.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  ST7735_SPI_PORT.Init.CRCPolynomial = 10;
  HAL_SPI_Init(&ST7735_SPI_PORT);
  
}

void Init_Encoder()
{
  //timer 3 setup
  //PC6

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  TIM3->CR1=0;
  TIM3->CCMR1=0;
  TIM3->CCER=0;
  TIM3->SMCR=0;
  
  TIM3->CR1|=(10<<8);
  
  //TIM3->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F;
  
  TIM3->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F;
  
  TIM3->CCMR1 |= 0xF0;
  
  TIM3->CCER |= TIM_CCER_CC1P;
  TIM3->CCER |= TIM_CCER_CC2P;

  TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;
  TIM3->CCMR1 |= TIM_CCMR1_CC2S_0;
  TIM3->SMCR |= 3;

  TIM3->ARR = 65535;
  TIM3->EGR=1;
  TIM3->CR1 |= TIM_CR1_CEN;

}


void USB_I2S_Init(void)
{
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_InitTick(TICK_INT_PRIORITY);
  
  //HSE, PLL 168 MHz
  FLASH->ACR = FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;
  RCC->CR |= RCC_CR_HSEON;
  while((RCC->CR & RCC_CR_HSERDY) == 0);
    
  RCC->PLLCFGR = RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | \
                 RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_8 | RCC_PLLCFGR_PLLM_3;
    
  RCC->CFGR = RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4;
  
  RCC->CFGR|=(1<<7);
    
  RCC->CR |= RCC_CR_PLLON;
  while((RCC->CR & RCC_CR_PLLRDY) == 0);
  
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL);
  
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
  while(((RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN) != RCC_AHB1ENR_GPIOAEN)
     || ((RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN) != RCC_AHB1ENR_GPIOBEN)
     || ((RCC->AHB1ENR & RCC_AHB1ENR_GPIODEN) != RCC_AHB1ENR_GPIODEN)
     || ((RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN) != RCC_AHB1ENR_GPIOCEN));
  
  RCC->APB1ENR|=(1<<RCC_APB1ENR_TIM3EN_Pos);
  RCC->APB1ENR|=(1<<RCC_APB1ENR_SPI3EN_Pos);

  ConfigGPIOs_Init();
}

//------------------------------------------------------------------------------
void Error_Handler(void)
{
   
}
//------------------------------------------------------------------------------
void USBD_error_handler(void)
{
  Error_Handler();
}

void LCD_Update(void)
{
  /*char __buff[128];
  sprintf(__buff,"%i bit %i kHz",LCD_I2S_AudioResolution,LCD_I2S_AudioFrequency/1000);
  ST7735_WriteString(10,50,__buff,Font_11x18, ST7735_GREEN, ST7735_BLACK);*/
  Screen_NeedUpdate=1;
}

void GPIO_Init(void)
{
  POWER_DISABLE_GPIO->MODER |= 1 << (2 * POWER_DISABLE_PIN);
}

void DSP_Update()
{
  I2C_port_active=false;
  if(DSP_Last_AudioFrequency!=LCD_I2S_AudioFrequency)
  {
    err_success_writes=0;
    err_count=0;
    err_count_over=0;
    
    HAL_GPIO_WritePin(DSP_RESET_PORT, DSP_RESET_PIN,GPIO_PIN_RESET);
    MCLK_Select_Freq(LCD_I2S_AudioFrequency);
    
    // power up DSP
    
    HAL_Delay(DSP_RESET_PAUSE);
    HAL_GPIO_WritePin(DSP_RESET_PORT, DSP_RESET_PIN,GPIO_PIN_SET);
    HAL_Delay(DSP_RESET_PAUSE);
    
    DSP_Last_AudioFrequency=LCD_I2S_AudioFrequency;
    
    switch(LCD_I2S_AudioFrequency)
    {
      case 44100:
      {
        default_download_IC44();
      }
      break;
      case 48000:
      {
        default_download_IC48();
      }
      break;
    case 88200:
      {
        default_download_IC88();
      }
      break;
      case 96000:
      {
        default_download_IC88();
      }
      break;
    }
    
    DAC_Update();
    
    /*char __buff[128];
    sprintf(__buff,"Freq:%i",LCD_I2S_AudioFrequency);
    ST7735_WriteString(10,70,__buff,Font_11x18, ST7735_MAGENTA, ST7735_BLACK);*/
  
  }
}

void uDSP01_ButtonActions(int Screen, unsigned short ButtonState)
{
  switch(Screen_Current)
  {
  case 0:
    {
      //inf screen
    }break;
  case 1:
    {
      //dsp screen
      //menu_current_item
      // draw dsp menu
      
      switch(ButtonState)
      {
      case 0xd:
        {
          // btn SEL
          
        }break;
      case 0xb:
        {
          // btn -
        }break;
      case 0x7:
        {
          //btn +
        }break;
      }
      Screen_Draw_DSP_Menu(menu_current_item);
      
    }break;
  case 2:
    {
      //eq screen
    }break;
  case 3:
    {
      //set screen
    }break;
  };
}

void Screen_Draw(int screen)
{
  ST7735_FillRectangle(0,21,160,104,0xffff);
  Screen_Draw_Top_Bar(screen);
  Screen_Draw_Bot_Bar(screen);
  for(int i=0;i<160;i++)
  {
    ST7735_DrawPixel(i,20,ST7735_COLOR565(24,48,24));
    ST7735_DrawPixel(i,106,ST7735_COLOR565(24,48,24));
    if(screen==0)
    {
      if(i<86)
      {
        ST7735_DrawPixel(100,20+i,ST7735_COLOR565(24,48,24));
      }
    }
  }
  switch(screen)
  {
  case 0:
    {
      // status screen
      char __buff[32];
      sprintf(__buff,"%i/%i",LCD_I2S_AudioResolution,LCD_I2S_AudioFrequency/1000);
      ST7735_WriteString(102,22,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      
      if(Screen_HP_out)
      {
        ST7735_FillRectangle(108,41,33,18,0xffff);
        sprintf(__buff,"HP");
        ST7735_WriteString(119,41,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      }
      else
      {
        ST7735_FillRectangle(108,41,33,18,0xffff);
        sprintf(__buff,"Line");
        ST7735_WriteString(108,41,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      }
      
      if(Screen_Nat_Active)
      {
        sprintf(__buff,"Nat");
        ST7735_FillRectangle(114,60,33,18,0xffff);
        ST7735_WriteString(114,60,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      }
      else
      {
        ST7735_FillRectangle(114,60,33,18,0xffff);
        sprintf(__buff,"FX");
        ST7735_WriteString(119,60,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      }
      
      if(Mute)
      {
        sprintf(__buff,"Mute");
        ST7735_WriteString(108,79,__buff,Font_11x18, ST7735_WHITE, ST7735_RED);
      }
      else
      {
        ST7735_FillRectangle(108,79,44,18,0xffff);
      }
      
      Screen_DrawVolume();     
      
    }break;
    
  case 1:
    {
      // dsp screen
      
    }break;
  case 2:
    {
      //eq screen
    }break;
  case 3:
    {
      //set screen
    }
    break;
    
  };
  
};

void Screen_Draw_DSP_Menu(unsigned char item)
{
  //clear field
  ST7735_FillRectangle(0,21,160,103,0xffff);
  
  if(item==0)
  {
    //sprintf(__buff,dsp_menu_items_titles[0]);
    ST7735_WriteString(1,23,dsp_menu_items_titles[0],Font_11x18, ST7735_WHITE, ST7735_BLUE);
    //sprintf(__buff,dsp_menu_items_titles[1]);
    ST7735_WriteString(1,43,dsp_menu_items_titles[1],Font_11x18, ST7735_BLUE, ST7735_WHITE);
    //sprintf(__buff,dsp_menu_items_titles[2]);
    ST7735_WriteString(1,63,dsp_menu_items_titles[2],Font_11x18, ST7735_BLUE, ST7735_WHITE);
  }
  else
  {
    //last item
    if(item==12)
    {
      sprintf(__buff,dsp_menu_items_titles[10]);
      ST7735_WriteString(1,23,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      sprintf(__buff,dsp_menu_items_titles[11]);
      ST7735_WriteString(1,43,__buff,Font_11x18, ST7735_WHITE, ST7735_BLUE);
      sprintf(__buff,dsp_menu_items_titles[12]);
      ST7735_WriteString(1,63,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
    }
    else
    {
      sprintf(__buff,dsp_menu_items_titles[item-1]);
      ST7735_WriteString(1,23,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      sprintf(__buff,dsp_menu_items_titles[item]);
      ST7735_WriteString(1,43,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
      sprintf(__buff,dsp_menu_items_titles[item+1]);
      ST7735_WriteString(1,63,__buff,Font_11x18, ST7735_WHITE, ST7735_BLUE);
    };
  };
  
};

void Screen_Draw_Top_Bar(int screen)
{
  
  // small eeprom test
  
  
  
  char __buff[32];
  //ST7735_FillRectangle(0,0,160,33,0xffff);
  switch(screen)
  {
    
    case 0:
    {
      sprintf(__buff,"INF");
      ST7735_WriteString(3,1,__buff,Font_11x18, ST7735_MAGENTA, ST7735_WHITE);
      sprintf(__buff,"DSP");
      ST7735_WriteString(43,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"EQ");
      ST7735_WriteString(91,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"SET");
      ST7735_WriteString(123,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
  
      /*ST7735_DrawImage(4,0,32,32,image_data_stat8b);
      ST7735_DrawImage(44,0,32,32,image_data_eq8b_gray);
      ST7735_DrawImage(84,0,32,32,image_data_dsp8b_gray);
      ST7735_DrawImage(124,0,32,32,image_data_set8b_gray);*/
      
      
    }break;
  case 1:
    {
      sprintf(__buff,"INF");
      ST7735_WriteString(3,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"DSP");
      ST7735_WriteString(43,1,__buff,Font_11x18, ST7735_MAGENTA, ST7735_WHITE);
      sprintf(__buff,"EQ");
      ST7735_WriteString(91,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"SET");
      ST7735_WriteString(123,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);

      /*ST7735_DrawImage(4,0,32,32,image_data_stat8b_gray);
      ST7735_DrawImage(44,0,32,32,image_data_eq8b);
      ST7735_DrawImage(84,0,32,32,image_data_dsp8b_gray);
      ST7735_DrawImage(124,0,32,32,image_data_set8b_gray);*/
    } break;
  case 2:
    {
      sprintf(__buff,"INF");
      ST7735_WriteString(3,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"DSP");
      ST7735_WriteString(43,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"EQ");
      ST7735_WriteString(91,1,__buff,Font_11x18, ST7735_MAGENTA, ST7735_WHITE);
      sprintf(__buff,"SET");
      ST7735_WriteString(123,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      /*ST7735_DrawImage(4,0,32,32,image_data_stat8b_gray);
      ST7735_DrawImage(44,0,32,32,image_data_eq8b_gray);
      ST7735_DrawImage(84,0,32,32,image_data_dsp8b);
      ST7735_DrawImage(124,0,32,32,image_data_set8b_gray);*/
    } break;
  case 3:
    {
      sprintf(__buff,"INF");
      ST7735_WriteString(3,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"DSP");
      ST7735_WriteString(43,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"EQ");
      ST7735_WriteString(91,1,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      sprintf(__buff,"SET");
      ST7735_WriteString(123,1,__buff,Font_11x18, ST7735_MAGENTA, ST7735_WHITE);
      /*ST7735_DrawImage(4,0,32,32,image_data_stat8b_gray);
      ST7735_DrawImage(44,0,32,32,image_data_eq8b_gray);
      ST7735_DrawImage(84,0,32,32,image_data_dsp8b_gray);
      ST7735_DrawImage(124,0,32,32,image_data_set8b);*/
    } break;
  }
}

void Screen_Draw_Bot_Bar(int screen)
{
    /*
  bool Screen_Temb_Edit_HPF_Active=false;
  bool Screen_Temb_Edit_LPF_Active=false;
  bool Screen_Nat_Active=false;

  */
  
  switch(screen)
  {
    case 0:
    {
      char __buff[32];
      sprintf(__buff,"LPF");
      
      if(Screen_Temb_Edit_LPF_Active)
      {
        ST7735_WriteString(3,108,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
      }
      else
      {
        ST7735_WriteString(3,108,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      }
      
      sprintf(__buff,"HPF");
      
      if(Screen_Temb_Edit_HPF_Active)
      {
        ST7735_WriteString(69,108,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
      }
      else
      {
        ST7735_WriteString(69,108,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      }
      
      
      
      if(Screen_Nat_Active)
      {
        sprintf(__buff,"NAT");
        ST7735_WriteString(125,108,__buff,Font_11x18, ST7735_WHITE, ST7735_BLUE);
      }
      else
      {
        sprintf(__buff,"NAT");
        ST7735_WriteString(125,108,__buff,Font_11x18, ST7735_COLOR565(24,48,24), ST7735_WHITE);
      }
      
    }
    break;
  }
}

void Screen_DrawVolume()
{
  char __buff[32];
  if(Screen_Temb_Edit_HPF_Active | Screen_Temb_Edit_LPF_Active)
  {
    if(Screen_Temb_Edit_LPF_Active)
    {
      sprintf(__buff,"bass");
      ST7735_WriteString(28,22,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
    }
    else
    {
      sprintf(__buff,"tre");
    ST7735_WriteString(37,22,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
    }
  }
  else
  {
    sprintf(__buff,"vol");
    ST7735_WriteString(37,22,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
  }
  if(dsp_volume_r==0)
  {
    sprintf(__buff,"  %.1fdb",dsp_volume_r);
  }
  else
  {
    if(dsp_volume_r<-9.9)
    {
      sprintf(__buff,"%.1fdb",dsp_volume_r);
    }
    else
    {
      sprintf(__buff," %.1fdb",dsp_volume_r);
    }
  }
  if(Screen_Temb_Edit_HPF_Active | Screen_Temb_Edit_LPF_Active)
  {
    ST7735_WriteString(5,55,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);
  }
  else
  {
    ST7735_WriteString(5,55,__buff,Font_11x18, ST7735_BLUE, ST7735_WHITE);
  }
}

void MCLK_Select_Freq(uint32_t AF)
{
  if(AF==44100)
  {
    HAL_GPIO_WritePin(MCLK_SCALE_PORT, MCLK_SCALE_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DSP_PLL_MODE_0_PORT, DSP_PLL_MODE_0_PIN,GPIO_PIN_SET);
  }
  
  if(AF==48000)
  {
    HAL_GPIO_WritePin(MCLK_SCALE_PORT, MCLK_SCALE_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(DSP_PLL_MODE_0_PORT, DSP_PLL_MODE_0_PIN,GPIO_PIN_SET);
  }
  
  if(AF==88200)
  {
    HAL_GPIO_WritePin(MCLK_SCALE_PORT, MCLK_SCALE_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DSP_PLL_MODE_0_PORT, DSP_PLL_MODE_0_PIN,GPIO_PIN_RESET);
  }
  
  if(AF==96000)
  {
    HAL_GPIO_WritePin(MCLK_SCALE_PORT, MCLK_SCALE_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(DSP_PLL_MODE_0_PORT, DSP_PLL_MODE_0_PIN,GPIO_PIN_RESET);
  }
}

void DAC_write_volume_r(double dBGain)
{
  
}

void DAC_write_volume_l(double dBGain)
{
  int __gain=(int)dBGain*(-2);
  if(255-__gain<0)
  {
    DAC_InitData[3]=0;
  }
  else
  {
    DAC_InitData[3]=255-__gain;
  }
  err_success_writes=0;
  I2C_port_active=true;
  i2c_start_cond(I2C_port_active);
  if(i2c_send_byte(DAC_I2C_ADDRESS,I2C_port_active))
  {
    err_success_writes++;
  }
  if(i2c_send_byte(3,I2C_port_active))
  {
    err_success_writes++;
  }
  if(i2c_send_byte(DAC_InitData[4],I2C_port_active))
  {
    err_success_writes++;
  }
  i2c_stop_cond(I2C_port_active);
}


void DSP_write_volume_r(double dBGain)
{
    double linearGain = pow(10, dBGain / 20);
    switch(LCD_I2S_AudioFrequency)
    {
    case 44100:
      {
        
      }
      break;
    case 96000:
      {
        SIGMA_WRITE_REGISTER_FLOAT(MOD_VOL_R_96_GAIN1940ALGNS2_ADDR, linearGain);
      }
      break;
    }
    
}

void DSP_write_volume_l(double dBGain)
{
    double linearGain = pow(10, dBGain / 20);
    SIGMA_WRITE_REGISTER_FLOAT(MOD_VOL_L_96_GAIN1940ALGNS1_ADDR, linearGain);
}

void DSP_write_temb_lpf(double freq,double dbGain)
{

}

void SIGMA_WRITE_REGISTER_INTEGER(int address, int32_t pData) 
{
  uint8_t byte_data[4];
  SIGMASTUDIOTYPE_REGISTER_CONVERT(pData, byte_data);
  SIGMA_WRITE_REGISTER_BLOCK(DSP_I2C_ADDR,address, 4, byte_data);
}


void SIGMASTUDIOTYPE_REGISTER_CONVERT(int32_t fixpt_val, uint8_t dest[4]) 
{
  dest[0] = (fixpt_val >> 24) & 0xFF;
  dest[1] = (fixpt_val >> 16) & 0xFF;
  dest[2] = (fixpt_val >> 8) & 0xFF;
  dest[3] = (fixpt_val) & 0xFF;
}

int SIGMASTUDIOTYPE_FIXPOINT_CONVERT (double value)
{
  return (int32_t)(value * (0x01 << 23)) & 0xFFFFFFF;
}

void SIGMA_WRITE_REGISTER_FLOAT(int address, double pData) 
{
  //int32_t __temp=SIGMASTUDIOTYPE_FIXPOINT_CONVERT(pData);
  SIGMA_WRITE_REGISTER_INTEGER(address, (int32_t)(pData * (0x01 << 23)) & 0xFFFFFFF);
}

void Buttons_Check()
{
  
    char __buff[32];
    // encoder
    
    // BUTTON CHECK
    udsp01_btn_status=0;
    
    if (HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_1_port,uDSP01_CTRL_BTN_1_pin))
    {
      udsp01_btn_status=udsp01_btn_status+1<<0;
    };
    if (HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_2_port,uDSP01_CTRL_BTN_2_pin))
    {
      udsp01_btn_status=udsp01_btn_status+1<<1;
    };
    if (HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_3_port,uDSP01_CTRL_BTN_3_pin))
    {
      udsp01_btn_status=udsp01_btn_status+1<<2;
    };
    if (HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_4_port,uDSP01_CTRL_BTN_4_pin))
    {
      udsp01_btn_status=udsp01_btn_status+1<<3;
    };
    uDSP01_CTRL_BTN_ENC=HAL_GPIO_ReadPin(uDSP01_CTRL_BTN_ENC_port,uDSP01_CTRL_BTN_ENC_pin);
    
    /*sprintf(__buff,"0x%x",udsp01_btn_status);
    ST7735_WriteString(0,80,__buff,Font_11x18, ST7735_RED, ST7735_WHITE);*/
    
    // check button, only one button pressed is true
    
    switch(udsp01_btn_status)
    {
      // mute button
      case 0x68:
      {
        if(udsp01_btn_status_last!=0x68)
        {
          //invert state
          if(Mute)
          {
            Mute=false;  
          }
          else
          {
            Mute=true;
          }
          DSP_Mute(Mute);
          DAC_Mute(Mute);
        }
      }
      break;
      
      
      case 0x48:
      {
        //btn1
        switch(Screen_Current)
        {
          case 0:
            {
            }break;
          case 1:
            {
            }break;
          case 2:
            {
            }
            break;
          case 3:
            {
            }break;
        }    
      }
      break;
      
      case 0x28:
      {
        //btn2
        switch(Screen_Current)
        {
          case 0:
            {
            }break;
          case 1:
            {
            }break;
          case 2:
            {
            }
            break;
          case 3:
            {
            }break;
        }   
      }
      break;
      
      case 0x14:
      {
        //btn3
        
        switch(Screen_Current)
        {
          case 0:
          {
            //Natural_Sound
            if(udsp01_btn_status_last!=0x14)
            {
              uint8_t byte_data[4];
              byte_data[3]=__tmp;
              //SIGMA_WRITE_REGISTER_BLOCK(DSP_I2C_ADDR,MOD_OUT_SEL_44_DCINPALG1_ADDR, 4, byte_data);
              __tmp=__tmp+1;
              if(__tmp>3)
              {
                __tmp=0;
              }
              if(Natural_Sound)
              {
                Natural_Sound=false;
              }
              else
              {
                Natural_Sound=true;
              }
              Screen_Nat_Active=Natural_Sound;
              DSP_Natural_Sound(Natural_Sound);
            }
          }break;
          
        case 1:
          {
            //dsp screen
          }break;
        case 2:
          {
            //eq screen
          }break;
        case 3:
          {
            //set screen
          }break;
        }
      }
      break;
      
      default:
        //no actions for multiplying press buttons
    }
    
    if(udsp01_btn_status_last!=udsp01_btn_status)
    {
      Screen_NeedUpdate=true;
    }
    udsp01_btn_status_last=udsp01_btn_status;
}

void DSP_Mute(bool Mute)
{
  
}

void DSP_Natural_Sound(bool Natural_Sound)
{
  
}

/*
Программный МУТЕ через регистр ДАК
*/


void DAC_Mute(bool Mute)
{
  if(DAC_AK4490)
  {
    AK4490_SetMute(Mute);
  }
}

/*
Обновление регистров ЦАП. Отправляется на 1 байт больше, т.к. требуется сбросить бит RESET
*/

void DAC_Update()
{
  err_success_writes=0;
  I2C_port_active=true;
  for(int i=0;i<11;i++)
  {
    i2c_start_cond(I2C_port_active);
    if(i2c_send_byte(DAC_I2C_ADDRESS,I2C_port_active))
    {
       err_success_writes++;
    }
    if(i!=10)
    {
      if(i2c_send_byte(i,I2C_port_active))
      {
        err_success_writes++;
      }
      if(i2c_send_byte(DAC_InitData[i],I2C_port_active))
      {
        err_success_writes++;
      }
    }
    else
    {
      if(i2c_send_byte(0,I2C_port_active))
      {
        err_success_writes++;
      }
      if(i2c_send_byte(DAC_InitData[0]+1,I2C_port_active))
      {
        err_success_writes++;
      }
    }
    i2c_stop_cond(I2C_port_active);
  }
  i2c_stop_cond(I2C_port_active);
}