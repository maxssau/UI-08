/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2019
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/






#ifndef __USB_AUDIO_DESCRIPTORS_H
#define __USB_AUDIO_DESCRIPTORS_H



#define   CONFIG_2_0_STEREO_DESCRIPTOR_SIZE      (128 + 58+3)
#define   CONFIG_2_0_STEREO_AC_TOTAL_SIZE        40

#define   CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE   (119)

#define   CONFIG_3_1_DESCRIPTOR_SIZE             (127 + 55)
#define   CONFIG_3_1_AC_TOTAL_SIZE               42

#define   CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE      (127 + 55)
#define   CONFIG_4_0_QUADRO_AC_TOTAL_SIZE        42

#define   CONFIG_TERMINAL_INPUT_ID               0x12
#define   CONFIG_UNIT_FEATURE_ID                 0x16
#define   CONFIG_TERMINAL_OUTPUT_ID              0x14

#define   CONFIG_AUDIO_STREAMING_INTERFACE       1
#define   CONFIG_AUDIO_EP_OUT                    0x01
#define   CONFIG_AUDIO_EP_SYNC                   0x81
#define   CONFIG_AUDIO_FEEDBACK_REFRESH          0x07





uint8_t* GetProductString(void);



#endif // __USB_AUDIO_DESCRIPTORS_H


