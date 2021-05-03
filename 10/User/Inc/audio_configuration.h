/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/




#ifndef __AUDIO_CONFIGURATION_H
#define __AUDIO_CONFIGURATION_H


#include "board.h"
#include "audio_node.h"
#include "usb_audio_constants.h"
#include "audio_speaker_node.h"

#define MCLK_EXT                        1
#define MCLK_256fs                      0
#define MCLK_512fs                      1

#define MCLK_SCALE_PORT                 GPIOB
#define MCLK_SCALE_PIN                  GPIO_PIN_1

#define DSP_PLL_MODE_0_PORT             GPIOB
#define DSP_PLL_MODE_0_PIN              GPIO_PIN_15

#define DSP_RESET_PORT                  GPIOA
#define DSP_RESET_PIN                   GPIO_PIN_0

#define DSP_SCL_PORT                    GPIOA
#define DSP_SCL_PIN                     GPIO_PIN_8

#define DSP_SDA_PORT                    GPIOB
#define DSP_SDA_PIN                     GPIO_PIN_4

#define DAC_SCL_PORT                    GPIOB
#define DAC_SCL_PIN                     GPIO_PIN_6

#define DAC_SDA_PORT                    GPIOB
#define DAC_SDA_PIN                     GPIO_PIN_7

#define DAC_I2C_ADDRESS                 0x24
#define DAC4490_I2C_ADDRESS             0x24

#define DSP_RESET_PAUSE                 200             // reset time of DSP
#define DSP_TIMEOUT                     40
#define DSP_I2C_ERRORS_COUNT_MAX        100
#define DSP_I2C_BLOCK_SIZE              60
#define DSP_I2C_SOFT_DELAY              1
#define DSP_I2C_ADDR                    0x68

#define DSP_DEFAULT_VAL                 0

#define ENC_JOG_TIME_1                  2
#define ENC_JOG_TIME_2                  10
#define ENC_JOG_TIME_3                  50



#define uDSP01_CTRL_BTN_ENC_pin         GPIO_PIN_8
#define uDSP01_CTRL_BTN_ENC_port        GPIOC

#define uDSP01_CTRL_BTN_1_pin           GPIO_PIN_13
#define uDSP01_CTRL_BTN_1_port          GPIOC

#define uDSP01_CTRL_BTN_2_pin           GPIO_PIN_14
#define uDSP01_CTRL_BTN_2_port          GPIOC

#define uDSP01_CTRL_BTN_3_pin           GPIO_PIN_14
#define uDSP01_CTRL_BTN_3_port          GPIOB

#define uDSP01_CTRL_BTN_4_pin           GPIO_PIN_13
#define uDSP01_CTRL_BTN_4_port          GPIOB

#define uDSP01_Ctrl_Button_Timeout      100

#define   USE_USB_AUDIO_CLASS_10                 1

#define   ALTERNATE_SETTING_16_BIT               1
#define   ALTERNATE_SETTING_24_BIT               2

#define   CONFIG_RES_BIT_16                      16
#define   CONFIG_RES_BYTE_16                     2

#define   CONFIG_RES_BIT_24                      24
#define   CONFIG_RES_BYTE_24                     3

#define   CONFIG_RES_BIT_32                      32
#define   CONFIG_RES_BYTE_32                     4


#define   CONFIG_2_0_STEREO_CHANNEL_COUNT        2
#define   CONFIG_2_0_STEREO_CHANNEL_MAP          0x03
#define   CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT    4
#define   CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT    4
#define   CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT    1
#define   CONFIG_2_0_STEREO_16_BIT_MAX_PACKET    ((192 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_2_0_STEREO_24_BIT_MAX_PACKET    ((96 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_24)
#define   CONFIG_2_0_STEREO_32_BIT_MAX_PACKET    ((96 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_32)
#define   CONFIG_2_0_SAI_COUNT                   1
#define   CONFIG_2_0_FREQUENCY_DEFAULT           USB_AUDIO_CONFIG_FREQ_96_K
#define   CONFIG_2_0_32BIT_FREQUENCY_DEFAULT     USB_AUDIO_CONFIG_FREQ_96_K

#define   CONFIG_3_1_CHANNEL_COUNT               4
#define   CONFIG_3_1_CHANNEL_MAP                 0x0F
#define   CONFIG_3_1_16_BIT_FREQ_COUNT           3
#define   CONFIG_3_1_24_BIT_FREQ_COUNT           2
#define   CONFIG_3_1_16_BIT_MAX_PACKET           ((96 + 2) * CONFIG_3_1_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_3_1_24_BIT_MAX_PACKET           ((48 + 2) * CONFIG_3_1_CHANNEL_COUNT * CONFIG_RES_BYTE_24)

#define   CONFIG_4_0_QUADRO_CHANNEL_COUNT        4
#define   CONFIG_4_0_QUADRO_CHANNEL_MAP          0x33
#define   CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT    3
#define   CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT    2
#define   CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET    ((96 + 2) * CONFIG_4_0_QUADRO_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET    ((48 + 2) * CONFIG_4_0_QUADRO_CHANNEL_COUNT * CONFIG_RES_BYTE_24)
#define   CONFIG_4_0_SAI_COUNT                   2

#define   DEVICE_ID1                             ((uint32_t)0x1FFF7A10)
#define   DEVICE_ID2                             ((uint32_t)0x1FFF7A14)
#define   DEVICE_ID3                             ((uint32_t)0x1FFF7A18)

#define   USB_AUDIO_CONFIG_SAI_MAX_COUNT         CONFIG_4_0_SAI_COUNT
#define   USB_AUDIO_CONFIG_PLAY_BUFFER_SIZE      ((1024 * 10) * USB_AUDIO_CONFIG_SAI_MAX_COUNT)

#define   AUDIO_CONFIG_2_0_STEREO_32_BIT         0
#define   AUDIO_CONFIG_2_0_STEREO                1
#define   AUDIO_CONFIG_3_1                       2
#define   AUDIO_CONFIG_4_0_QUADRO                3

#define   EXTERNAL_SYNC                          1


void SetAudioConfigDependedFuncs(AUDIO_SpeakerNode_t *speaker);

void Play_SAIMaster(uint16_t *Data, uint16_t Size, uint8_t ResByte);

void Play_SAIMasterAndSlave(uint16_t *Data, uint16_t Size, uint8_t ResByte);

void PrepareData_4_Chnls(uint8_t* AudioData, uint16_t Size, uint8_t ResInBytes);

void AudioChangeFrequency(uint32_t AudioFrequency);

void ExtSyncSelectSource(uint32_t AudioFrequency);

void AudioChangeResolution(uint8_t AudioResolution);

void AudioOutMute(uint8_t MuteFlag);

void AudioOutInit(uint32_t AudioFrequency, uint8_t AudioResolution);

void PlayDescriptionInit(AUDIO_Description_t *Description);

uint8_t GetAudioConfiguration(void);

void MakeSerialNumber(uint32_t *Buffer);

void AudioConfig_Init(void);

void OUTClk_Init(void);

void ExtPowerDisable(void);

void ConfigGPIOs_Init(void);

void InitDelay(void);

void MCLK_Select_Freq(uint32_t);


#endif // __AUDIO_CONFIGURATION_H

