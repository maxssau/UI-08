#ifndef __uDSP_01__c
#define __uDSP_01__c

#include "udsp01.h"

void uDSP_Set_default_val(struct uDSP_Settings *__set)
{
  __set->Nat_Active=1; // no FX sound
  __set->DAC_filter=0; // Super Slow (AK449X)
  __set->DAC_inv_L=0;
  __set->DAC_inv_R=0;
  __set->BIN_Sel=0;
  __set->DAC_Sound_Control=0;
  __set->DAC_vol_l=0;
  __set->DSP_vol_l=0;
  __set->DAC_vol_r=0;
  __set->DSP_vol_r=0;
  __set->EQ_Sel=0; // eq disable
  __set->HW_vol_l=0;
  __set->HW_vol_r=0;
  __set->LPF_1_en=0; // disable
  __set->LPF_1_freq=22000;
  __set->LPF_1_gain=0;
  __set->LPF_1_q=1.41;
  __set->LPF_1_phase=0; // no inversion
  __set->Noise_L_en=0;
  __set->Noise_L_1_vol=-40;
  __set->Noise_L_2_vol=-40;
  __set->Noise_R_en=0;
  __set->Noise_R_1_vol=-40;
  __set->Noise_R_2_vol=-40;
  __set->Noise_Mix_L_1=0;
  __set->Noise_Mix_L_2=0;
  __set->Noise_Mix_R_1=0;
  __set->Noise_Mix_R_2=0;
  __set->OUT_Sel=0; // disable phat
  __set->Phat_freq=1000;
  __set->Phat_gain=-3;
  __set->Tone_L_active=0;
  __set->Tone_R_active=0;
  __set->Tone_Treble_L_volume=0;
  __set->Tone_Treble_R_volume=0;
  __set->Tone_Bass_L_volume=0;
  __set->Tone_Bass_R_volume=0;
  __set->Tone_Sel=0;
  
  
}

#endif