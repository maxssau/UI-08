/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#ifndef __BOARD_H
#define __BOARD_H


#include "stm32f446xx.h"

//USB
#define   USB_FS_GPIO                      GPIOA
#define   USB_FS_DM_PIN                    11
#define   USB_FS_DP_PIN                    12
#define   USB_FS_PINS_AF                   10
//SAI1 - master
#define   SAI_MASTER                       SAI1_Block_B
#define   SAI_MASTER_MCLK_GPIO             GPIOC
#define   SAI_MASTER_MCK_PIN               0
#define   SAI_MASTER_SCK_FS_GPIO           GPIOB
#define   SAI_MASTER_SCK_PIN               12
#define   SAI_MASTER_FS_PIN                9
#define   SAI_MASTER_SD_GPIO               GPIOA
#define   SAI_MASTER_SD_PIN                9
#define   SAI_MASTER_MCLK_SCK_SD_FS_AF     6
#define   SAI_MASTER_DMA_STREAM            DMA2_Stream5
#define   SAI_MASTER_DMA_CHANNEL           0
#define   SAI_MASTER_DMA_IRQ               DMA2_Stream5_IRQn
//SAI2 - slave
#define   SAI_SLAVE                        SAI1_Block_A
#define   SAI_SLAVE_SD_GPIO                GPIOB
#define   SAI_SLAVE_SD_PIN                 2
#define   SAI_SLAVE_SD_AF                  6
#define   SAI_SLAVE_DMA_STREAM             DMA2_Stream1
#define   SAI_SLAVE_DMA_CHANNEL            0
//#define   SAI_SLAVE_DMA_IRQ                DMA2_Stream1_IRQn

#define   CONFIG_1_GPIO                    GPIOB
#define   CONFIG_1_PIN                     7
#define   CONFIG_2_GPIO                    GPIOC
#define   CONFIG_2_PIN                     5
#define   CONFIG_3_GPIO                    GPIOC
#define   CONFIG_3_PIN                     6
#define   EXT_SYNC_SELECT_GPIO             GPIOB
#define   EXT_SYNC_SELECT_1_PIN            13
#define   EXT_SYNC_SELECT_2_PIN            15
#define   EXT_SYNC_SELECT_MASK             ((1 << EXT_SYNC_SELECT_1_PIN) | (1 << EXT_SYNC_SELECT_2_PIN))
#define   EXT_SYNC_SELECT_44100            0
#define   EXT_SYNC_SELECT_88200            0
#define   EXT_SYNC_SELECT_48000            (1 << EXT_SYNC_SELECT_1_PIN)
#define   EXT_SYNC_SELECT_96000            (1 << EXT_SYNC_SELECT_2_PIN)
#define   EXT_SYNC_SELECT_192000           EXT_SYNC_SELECT_MASK
#define   EXT_SYNC_GPIO                    GPIOC
#define   EXT_SYNC_PIN                     9
#define   EXT_SYNC_AF                      5
#define   OUT_CLK_CONFIG_1_GPIO            GPIOC
#define   OUT_CLK_CONFIG_1_PIN             7
#define   OUT_CLK_CONFIG_2_GPIO            GPIOA
#define   OUT_CLK_CONFIG_2_PIN             15
#define   OUT_CLK_CONFIG_3_GPIO            GPIOC
#define   OUT_CLK_CONFIG_3_PIN             10

#define   POWER_DISABLE_GPIO               GPIOC
#define   POWER_DISABLE_PIN                12

#define   CONFIG_DELAY_GPIO                GPIOC
#define   CONFIG_DELAY_PIN                 4

#define   CONFIG_PIN_1_MASK                (1 << 0)
#define   CONFIG_PIN_2_MASK                (1 << 1)
#define   CONFIG_PINS_MASK                 (CONFIG_PIN_1_MASK | CONFIG_PIN_2_MASK)

#define   OUT_CLK_CONFIG_1                 ((1 << OUT_CLK_CONFIG_1_PIN) | (1 << OUT_CLK_CONFIG_3_PIN))
#define   OUT_CLK_CONFIG_2                 (1 << OUT_CLK_CONFIG_3_PIN)
#define   OUT_CLK_CONFIG_3                 (1 << OUT_CLK_CONFIG_1_PIN)
#define   OUT_CLK_CONFIG_4                 0

#define   CONFIG_DELAY                     0

#define   INIT_DELAY                       15000 //ms


void USB_I2S_Init(void);


#endif //__BOARD_H


