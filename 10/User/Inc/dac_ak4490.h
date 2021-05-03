#ifndef __dac__ak4490__
#define __dac__ak4490__ 1

void AK4490_Init(void);
void AK4490_SetVol(unsigned char vol_l,unsigned char vol_r);
void AK4490_SetMute(_Bool __mute);
void AK4490_SetFilter(unsigned char __filter);
void AK4490_Set_SoundQual(unsigned char __set);
void AK4490_Set_RL_Inv(unsigned char __inv_l,unsigned char __inv_r);

#endif