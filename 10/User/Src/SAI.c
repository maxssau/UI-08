
#include "SAI.h"
#include "stm32f4xx_hal_cortex.h"
#include "usb_audio_constants.h"

static uint16_t LastTransferSize = 0;

#ifdef __debug
uint32_t __debug_sai_cr1=0;
#endif

void SAI_PLLSAIConfig(uint32_t AudioFrequency)
{
  RCC->CR &= ~RCC_CR_PLLSAION;
  while((RCC->CR & RCC_CR_PLLSAIRDY) == RCC_CR_PLLSAIRDY);
  
  switch(AudioFrequency)
  {
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
    {
      RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_1 | (0x1AD << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
      RCC->DCKCFGR |= 0x12 << RCC_DCKCFGR_PLLSAIDIVQ_Pos;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_48_K:
    {
      RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_0 | RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | (0x158 << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
      RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVQ;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_88_K:
    {
      RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_1 | (0x1AD << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
      RCC->DCKCFGR |= 0x12 << RCC_DCKCFGR_PLLSAIDIVQ_Pos;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_96_K:
    {
      RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_0 | RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | (0x158 << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
      RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVQ;
    }
    break;
    
    
  default:
    {
      RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_0 | RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | (0x158 << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
      RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVQ;
    }
  }
  /*if(AudioFrequency == USB_AUDIO_CONFIG_FREQ_44_1_K)
  {
    RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_1 | (0x1AD << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
    RCC->DCKCFGR |= 0x12 << RCC_DCKCFGR_PLLSAIDIVQ_Pos; 
  }
  else //48, 96, 192
  {
    RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_0 | RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | \
                      (0x158 << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
    
    RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVQ;
  }*/
  
  RCC->CR |= RCC_CR_PLLSAION;
  while((RCC->CR & RCC_CR_PLLSAIRDY) != RCC_CR_PLLSAIRDY);
}
//------------------------------------------------------------------------------
void SAI_ChangeFrequency(uint32_t AudioFrequency)
{
  SAI_MASTER->CR1 &= ~SAI_xCR1_MCKDIV;
  
  uint32_t NewMCKDIV = 0;
  
  switch(AudioFrequency)
  {
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
    {
      NewMCKDIV = (0) << SAI_xCR1_MCKDIV_Pos;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_48_K:
    {
      //NewMCKDIV = (2 - (AudioFrequency / 48000 / 2)) << SAI_xCR1_MCKDIV_Pos;
      NewMCKDIV = (0) << SAI_xCR1_MCKDIV_Pos;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_88_K:
    {
      //NewMCKDIV = (2 - (AudioFrequency / 88200 / 2)) << SAI_xCR1_MCKDIV_Pos;
      NewMCKDIV = (0) << SAI_xCR1_MCKDIV_Pos;
    }
    break;
    case USB_AUDIO_CONFIG_FREQ_96_K:
    {
      NewMCKDIV = (0) << SAI_xCR1_MCKDIV_Pos;
    }
    break;
  }
   
  SAI_MASTER->CR1 |= NewMCKDIV;
  
#ifdef __debug
__debug_sai_cr1=SAI_MASTER->CR1;  
#endif
}
//------------------------------------------------------------------------------
void SAI_ExternalSyncInit(void)
{
  EXT_SYNC_GPIO->MODER |= (2 << (2 * EXT_SYNC_PIN));
  EXT_SYNC_GPIO->AFR[1] |= (EXT_SYNC_AF << (4 * (EXT_SYNC_PIN - 8)));
  RCC->DCKCFGR |= RCC_DCKCFGR_SAI1SRC_0 | RCC_DCKCFGR_SAI1SRC_1;
  
}
//------------------------------------------------------------------------------
uint16_t SAI_GetLastTransferSize(void)
{
  return LastTransferSize;
}
//------------------------------------------------------------------------------
uint16_t SAI_GetRemainingTxSize(void)
{
  return SAI_MASTER_DMA_STREAM->NDTR;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAPrepareTx(uint16_t *Data, uint16_t Size)
{
  SAI_DMAPrepareTx(SAI_MASTER_DMA_STREAM, Data, Size);
  LastTransferSize = Size;
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAPrepareTx(uint16_t *Data, uint16_t Size)
{
  SAI_DMAPrepareTx(SAI_SLAVE_DMA_STREAM, Data, Size);
}
//------------------------------------------------------------------------------
void SAI_DMAPrepareTx(DMA_Stream_TypeDef *DMAStream, uint16_t *Data, uint16_t Size)
{
  DMAStream->NDTR = Size;
  DMAStream->M0AR = (uint32_t)(&Data[0]);
  DMAStream->CR |= DMA_SxCR_EN;
}
//------------------------------------------------------------------------------
void SAI_MasterEnable()
{
  SAI_Enable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void SAI_SlaveEnable()
{
  SAI_Enable(SAI_SLAVE);
}
//------------------------------------------------------------------------------
void SAI_Enable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 |= SAI_xCR1_SAIEN;
  while((SAIBlock->CR1 & SAI_xCR1_SAIEN) != SAI_xCR1_SAIEN);
}
//------------------------------------------------------------------------------
void SAI_MasterMute(uint8_t MuteFlag)
{
  SAI_Mute(SAI_MASTER, MuteFlag);
}
//------------------------------------------------------------------------------
void SAI_SlaveMute(uint8_t MuteFlag)
{
  SAI_Mute(SAI_SLAVE, MuteFlag);
}
//------------------------------------------------------------------------------
// 1 - mute, 0 - unmute
void SAI_Mute(SAI_Block_TypeDef *SAIBlock, uint8_t MuteFlag)
{
  if (MuteFlag)
    SAIBlock->CR2 |= SAI_xCR2_MUTE;
  else
    SAIBlock->CR2 &= ~SAI_xCR2_MUTE;
}
//------------------------------------------------------------------------------
void SAI_MasterDisable()
{
  SAI_Disable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void SAI_SlaveDisable()
{
  SAI_Disable(SAI_SLAVE);
}
//------------------------------------------------------------------------------
void SAI_Disable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 &= ~SAI_xCR1_SAIEN;
  while((SAIBlock->CR1 & SAI_xCR1_SAIEN) == SAI_xCR1_SAIEN);
}
//------------------------------------------------------------------------------
void SAI_MasterInit(uint8_t AudioResolution)
{
  RCC->APB2ENR |= RCC_APB2ENR_SAI1EN;
  while((RCC->APB2ENR & RCC_APB2ENR_SAI1EN) != RCC_APB2ENR_SAI1EN);
  
  SAI_Disable(SAI_MASTER);
  //SAI_MASTER->CR1 = SAI_xCR1_MCKDIV_1;
  SAI_Init(SAI_MASTER, AudioResolution);
}
//------------------------------------------------------------------------------
void SAI_SlaveInit(uint8_t AudioResolution)
{
  SAI_Disable(SAI_SLAVE);
  SAI_SLAVE->CR1 = SAI_xCR1_MODE_1 | SAI_xCR1_SYNCEN_0;
  SAI_Init(SAI_SLAVE, AudioResolution);
}
//------------------------------------------------------------------------------
void SAI_Init(SAI_Block_TypeDef *SAIBlock, uint8_t AudioResolution)
{
SAIBlock->CR2 = SAI_xCR2_FTH_0;

  SAIBlock->FRCR = SAI_xFRCR_FSOFF | SAI_xFRCR_FSDEF;
  
  SAIBlock->CR1 &= ~(SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0);
  
  if (AudioResolution == 16)
  {
    //SAIBlock->FRCR |= (0x1F << SAI_xFRCR_FSALL_Pos) | (0x3F << SAI_xFRCR_FRL_Pos);
    SAIBlock->FRCR |= (0x0F << SAI_xFRCR_FSALL_Pos) | (0x1F << SAI_xFRCR_FRL_Pos);
    SAIBlock->CR1 |= SAI_xCR1_DS_2;
    SAIBlock->SLOTR = (((1 << 0) | (1 << 1)) << SAI_xSLOTR_SLOTEN_Pos) | (0x01 << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_0;
  }
  else
  {
    //SAIBlock->FRCR |= (0x3F << SAI_xFRCR_FSALL_Pos) | (0x7F << SAI_xFRCR_FRL_Pos);
    SAIBlock->FRCR |= (0x1F << SAI_xFRCR_FSALL_Pos) | (0x3F << SAI_xFRCR_FRL_Pos);
    SAIBlock->CR1 |= SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0;
    SAIBlock->SLOTR = (((1 << 0) | (1 << 1)) << SAI_xSLOTR_SLOTEN_Pos) | (0x01 << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_1;
  } 

  SAIBlock->CR1 |= SAI_xCR1_OUTDRIV;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAEnable(void)
{
  SAI_DMAEnable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAEnable(void)
{
  SAI_DMAEnable(SAI_SLAVE);
}
//------------------------------------------------------------------------------
void SAI_DMAEnable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 |= SAI_xCR1_DMAEN;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAInit(uint8_t AudioResolution)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  while((RCC->AHB1ENR & RCC_AHB1ENR_DMA2EN) != RCC_AHB1ENR_DMA2EN);
  
  SAI_DMAInit(SAI_MASTER_DMA_STREAM, AudioResolution);
  
  SAI_MASTER_DMA_STREAM->CR |= DMA_SxCR_TCIE;
  SAI_MASTER_DMA_STREAM->PAR = (uint32_t)(&(SAI_MASTER->DR));
  
  HAL_NVIC_SetPriority(SAI_MASTER_DMA_IRQ, SAI_IRQ_PRIORITY, 0);
  HAL_NVIC_EnableIRQ(SAI_MASTER_DMA_IRQ);    
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAInit(uint8_t AudioResolution)
{
  SAI_DMAInit(SAI_SLAVE_DMA_STREAM, AudioResolution);
  SAI_SLAVE_DMA_STREAM->PAR = (uint32_t)(&(SAI_SLAVE->DR));
}
//------------------------------------------------------------------------------
void SAI_DMAInit(DMA_Stream_TypeDef *DMAStream, uint8_t AudioResolution)
{  
  DMAStream->CR = DMA_SxCR_PL_1 | DMA_SxCR_MINC | DMA_SxCR_DIR_0;
  
  if (AudioResolution == 16)
    DMAStream->CR |= DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0;
  else
    DMAStream->CR |= DMA_SxCR_MSIZE_1 | DMA_SxCR_PSIZE_1;
      
  DMAStream->FCR = DMA_SxFCR_DMDIS | DMA_SxFCR_FTH;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAChangeDataSize(uint8_t Resolution)
{
  SAI_DMAChangeDataSize(SAI_MASTER_DMA_STREAM, Resolution);
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAChangeDataSize(uint8_t Resolution)
{
  SAI_DMAChangeDataSize(SAI_SLAVE_DMA_STREAM, Resolution);
}
//------------------------------------------------------------------------------
void SAI_DMAChangeDataSize(DMA_Stream_TypeDef *DMAStream, uint8_t Resolution)
{ 
  //SAI_DMAChangeDataSize вызывается в прерывании по окончанию передачи (TC)
  //поток уже неактивен, поэтому можно изменять регистр CR.
    
  DMAStream->CR &= ~(DMA_SxCR_MSIZE_Msk | DMA_SxCR_PSIZE_Msk);
  
  if (Resolution == 16)
    DMAStream->CR |= DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0;
  else
    DMAStream->CR |= DMA_SxCR_MSIZE_1 | DMA_SxCR_PSIZE_1;
}
//------------------------------------------------------------------------------
void SAI_MasterGPIOInit(void)
{
  SAI_MASTER_MCLK_GPIO->MODER |= (2 << (2 * SAI_MASTER_MCK_PIN));
  SAI_MASTER_MCLK_GPIO->AFR[0] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * SAI_MASTER_MCK_PIN));
  SAI_MASTER_MCLK_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_MCK_PIN));
  
  SAI_MASTER_SCK_FS_GPIO->MODER |= (2 << (2 * SAI_MASTER_SCK_PIN)) | (2 << (2 * SAI_MASTER_FS_PIN));
  SAI_MASTER_SCK_FS_GPIO->AFR[1] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_SCK_PIN - 8))) | \
                                  (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_FS_PIN - 8)));
  
  SAI_MASTER_SCK_FS_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_SCK_PIN)) | (3 << (2 * SAI_MASTER_FS_PIN));

  SAI_MASTER_SD_GPIO->MODER |= (2 << (2 * SAI_MASTER_SD_PIN));
  SAI_MASTER_SD_GPIO->AFR[1] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_SD_PIN - 8)));
  SAI_MASTER_SD_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_SD_PIN));
}
//------------------------------------------------------------------------------
void SAI_SlaveGPIOInit(void)
{
  SAI_SLAVE_SD_GPIO->MODER |= (2 << (2 * SAI_SLAVE_SD_PIN));
  SAI_SLAVE_SD_GPIO->AFR[0] |= (SAI_SLAVE_SD_AF << (4 * SAI_SLAVE_SD_PIN));
  SAI_SLAVE_SD_GPIO->OSPEEDR |= (3 << (2 * SAI_SLAVE_SD_PIN));
}





