


#include "audio_configuration.h"
#include "usbd_audio.h"
#include "SAI.h"

extern char LCD_NeedUpdate;
extern uint32_t LCD_I2S_AudioFrequency;
extern uint8_t LCD_I2S_AudioResolution;
extern char DSP_NeedUpdate;

static uint8_t AudioConfiguration = 0;
static uint8_t SyncSource = 0;


void SetAudioConfigDependedFuncs(AUDIO_SpeakerNode_t *speaker)
{
  speaker->SpeakerPlay = Play_SAIMaster;
  speaker->SpeakerPrepareData = 0;
}
//------------------------------------------------------------------------------
void Play_SAIMaster(uint16_t *Data, uint16_t Size, uint8_t ResByte)
{
  if (ResByte == 3)
    ResByte = 4;
  
  uint16_t TxSize = Size / CONFIG_2_0_SAI_COUNT / ResByte;

  SAI_MasterDMAPrepareTx(Data, TxSize);
  SAI_MasterDMAEnable();
}
//------------------------------------------------------------------------------
void Play_SAIMasterAndSlave(uint16_t *Data, uint16_t Size, uint8_t ResByte)
{
  if (ResByte == 3)
    ResByte = 4;
  
  uint16_t TxSize = Size / CONFIG_4_0_SAI_COUNT / ResByte;

  SAI_MasterDMAPrepareTx(&Data[0], TxSize);
  SAI_SlaveDMAPrepareTx(&Data[(ResByte / 2) * TxSize], TxSize);
  
  SAI_SlaveDMAEnable();
  SAI_MasterDMAEnable();
}
//------------------------------------------------------------------------------
void PrepareData_4_Chnls(uint8_t* AudioData, uint16_t Size, uint8_t ResInBytes)
{  
  uint8_t* SAISlaveData = malloc(Size / 2);
  if (!SAISlaveData)
  {
    Error_Handler();
  }

  if (ResInBytes == 3)
    ResInBytes = 4;
  
  uint8_t DataIncrement = ResInBytes * CONFIG_4_0_QUADRO_CHANNEL_COUNT;
  uint8_t BytesPerSAI = DataIncrement / CONFIG_4_0_SAI_COUNT;
  
  for (uint16_t i = 0; i < Size; i += DataIncrement)
  {
    uint16_t BaseAddr = i / CONFIG_4_0_SAI_COUNT;
    
    AudioData[BaseAddr] = AudioData[i];
    AudioData[BaseAddr + 1] = AudioData[i + 1];
    AudioData[BaseAddr + 2] = AudioData[i + 2];
    AudioData[BaseAddr + 3] = AudioData[i + 3];
    
    SAISlaveData[BaseAddr] = AudioData[i + BytesPerSAI];
    SAISlaveData[BaseAddr + 1] = AudioData[i + BytesPerSAI + 1];
    SAISlaveData[BaseAddr + 2] = AudioData[i + BytesPerSAI + 2];
    SAISlaveData[BaseAddr + 3] = AudioData[i + BytesPerSAI + 3];
    
    if (ResInBytes == 4)
    {
      AudioData[BaseAddr + 4] = AudioData[i + 4];
      AudioData[BaseAddr + 5] = AudioData[i + 5];
      AudioData[BaseAddr + 6] = AudioData[i + 6];
      AudioData[BaseAddr + 7] = AudioData[i + 7];

      SAISlaveData[BaseAddr + 4] = AudioData[i + BytesPerSAI + 4];
      SAISlaveData[BaseAddr + 5] = AudioData[i + BytesPerSAI + 5];
      SAISlaveData[BaseAddr + 6] = AudioData[i + BytesPerSAI + 6];
      SAISlaveData[BaseAddr + 7] = AudioData[i + BytesPerSAI + 7];
    }
  }

  memcpy(&AudioData[Size / CONFIG_4_0_SAI_COUNT], SAISlaveData, Size / CONFIG_4_0_SAI_COUNT);
  
  free(SAISlaveData);
}
//------------------------------------------------------------------------------
void AudioChangeFrequency(uint32_t AudioFrequency)
{
  SAI_MasterDisable();
  
  //disable DSP
  HAL_GPIO_WritePin(DSP_RESET_PORT, DSP_RESET_PIN,GPIO_PIN_RESET);
  //MCLK_Select_Freq(AudioFrequency);
  
  LCD_I2S_AudioFrequency=AudioFrequency;
  LCD_NeedUpdate=1;
  DSP_NeedUpdate=1;
  
    switch(AudioFrequency)
  {
    case 44100:
    case 48000:
    {
      SAI_MASTER->CR1 |= 1<<20;
    }
    break;
    case 88200:
    case 96000:
    {
      SAI_MASTER->CR1 &= ~(1<<20);
    }
    break;
  };
  
  MCLK_Select_Freq(AudioFrequency);
  
  if (SyncSource == EXTERNAL_SYNC)
    ExtSyncSelectSource(AudioFrequency);
  else
  {
    SAI_PLLSAIConfig(AudioFrequency);
    SAI_ChangeFrequency(AudioFrequency);
  }
  
  SAI_MasterEnable();
}
//------------------------------------------------------------------------------
void ExtSyncSelectSource(uint32_t AudioFrequency)
{
  
  
  
  //EXT_SYNC_SELECT_GPIO->ODR &= ~EXT_SYNC_SELECT_MASK;
  
  // mclk div set
  SAI_MasterDisable();
  
  LCD_I2S_AudioFrequency=AudioFrequency;
  //LCD_I2S_AudioResolution=AudioResolution;
  LCD_NeedUpdate=1;
   
  //MCLK_Select_Freq(AudioFrequency);
  
  SAI_MasterEnable();
  
  
  
  /*
  switch(AudioFrequency)
  {
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
      EXT_SYNC_SELECT_GPIO->ODR |= EXT_SYNC_SELECT_44100;
    break;
      
    case USB_AUDIO_CONFIG_FREQ_48_K:
    default:
      EXT_SYNC_SELECT_GPIO->ODR |= EXT_SYNC_SELECT_48000;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_88_K:
      EXT_SYNC_SELECT_GPIO->ODR |= EXT_SYNC_SELECT_88200;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_96_K:
      EXT_SYNC_SELECT_GPIO->ODR |= EXT_SYNC_SELECT_96000;
    break;
      
    case USB_AUDIO_CONFIG_FREQ_192_K:
      EXT_SYNC_SELECT_GPIO->ODR |= EXT_SYNC_SELECT_192000;
    break;
  }*/
  
  
}
//------------------------------------------------------------------------------
void AudioChangeResolution(uint8_t AudioResolution)
{
  //LCD_I2S_AudioFrequency=AudioFrequency;
  LCD_I2S_AudioResolution=AudioResolution;
  LCD_NeedUpdate=1;
  
  SAI_MasterDisable();
  SAI_Init(SAI_MASTER, AudioResolution);
  SAI_MasterDMAChangeDataSize(AudioResolution);
  SAI_MasterEnable();
  DSP_NeedUpdate=1;
}
//------------------------------------------------------------------------------
void AudioOutMute(uint8_t MuteFlag)
{
  //LCD_I2S_AudioFrequency=AudioFrequency;
  //LCD_I2S_AudioResolution=AudioResolution;
  LCD_NeedUpdate=1;
  SAI_MasterMute(MuteFlag);
}
//------------------------------------------------------------------------------
void AudioOutInit(uint32_t AudioFrequency, uint8_t AudioResolution)
{
  LCD_I2S_AudioFrequency=AudioFrequency;
  LCD_I2S_AudioResolution=AudioResolution;
  LCD_NeedUpdate=1;
  DSP_NeedUpdate=1;
  if (SyncSource == EXTERNAL_SYNC)
    SAI_ExternalSyncInit();
  else
    SAI_PLLSAIConfig(AudioFrequency);
  
  SAI_MasterGPIOInit();
  SAI_MasterDMAInit(AudioResolution);
  SAI_MasterInit(AudioResolution);
  
  if (SyncSource == EXTERNAL_SYNC)
    ExtSyncSelectSource(AudioFrequency);
  else
    SAI_ChangeFrequency(AudioFrequency);
  
  SAI_MasterEnable();
}
//------------------------------------------------------------------------------
void PlayDescriptionInit(AUDIO_Description_t *Description)
{
  Description->channels_count = CONFIG_2_0_STEREO_CHANNEL_COUNT;
  Description->channels_map = CONFIG_2_0_STEREO_CHANNEL_MAP;
    
  Description->resolution = CONFIG_RES_BYTE_24;//CONFIG_RES_BYTE_16;
  Description->frequency = CONFIG_2_0_FREQUENCY_DEFAULT;
  Description->audio_type = USBD_AUDIO_FORMAT_TYPE_PCM;
  Description->audio_volume_db_256 = VOLUME_SPEAKER_DEFAULT_DB_256;
  Description->audio_mute = 0;
}
//------------------------------------------------------------------------------
uint8_t GetAudioConfiguration(void)
{
  return AudioConfiguration;
}
//------------------------------------------------------------------------------
void MakeSerialNumber(uint32_t *Buffer)
{
  Buffer[0] = (*(uint32_t*)DEVICE_ID1) + (*(uint32_t*)DEVICE_ID3);
  Buffer[1] = (((*(uint32_t*)DEVICE_ID2) >> 16) + AudioConfiguration) << 16;
}
//------------------------------------------------------------------------------
void AudioConfig_Init(void)
{
  AudioConfiguration = AUDIO_CONFIG_2_0_STEREO;
  
  if(MCLK_EXT)
  {
    //EXT_SYNC_SELECT_GPIO->MODER |= (1 << (2 * EXT_SYNC_SELECT_1_PIN)) | (1 << (2 * EXT_SYNC_SELECT_2_PIN));
    SyncSource = EXTERNAL_SYNC;
  }
}
//------------------------------------------------------------------------------
void OUTClk_Init(void)
{
  uint32_t AudioFreq = CONFIG_2_0_FREQUENCY_DEFAULT;
  AudioOutInit(AudioFreq, CONFIG_RES_BIT_24);
}
//------------------------------------------------------------------------------
void ExtPowerDisable(void)
{
  POWER_DISABLE_GPIO->ODR |= 1 << POWER_DISABLE_PIN;
}
//------------------------------------------------------------------------------
void ConfigGPIOs_Init(void)
{

  POWER_DISABLE_GPIO->MODER |= 1 << (2 * POWER_DISABLE_PIN);
}
//------------------------------------------------------------------------------
void InitDelay(void)
{
  if ((CONFIG_DELAY_GPIO->IDR & (1 << CONFIG_DELAY_PIN)) == CONFIG_DELAY)
    HAL_Delay(INIT_DELAY);
}


