#ifndef __uDSP_01__h
#define __uDSP_01__h

struct uDSP_Settings
{
  // ctrl settings
  
  unsigned char Nat_Active;
  
  // volume controls
  unsigned char DAC_vol_r;
  unsigned char DAC_vol_l;
  unsigned char DAC_filter;
  unsigned char DAC_Sound_Control;
  unsigned char DAC_inv_L;
  unsigned char DAC_inv_R;
  
  float DSP_vol_l;
  float DSP_vol_r;
  unsigned int HW_vol_l;
  unsigned HW_vol_r;
  unsigned char vol_type;
  
  //bass & treble
  unsigned char Tone_L_active;
  unsigned char Tone_R_active;
  float Tone_Treble_L_volume;
  float Tone_Treble_R_volume;
  float Tone_Bass_L_volume;
  float Tone_Bass_R_volume;
  
  // DSP Settings
  float LPF_1_freq;
  float LPF_1_gain;
  float LPF_1_q;
  float LPF_1_en;
  float LPF_1_phase;
  
  float EQ_L_1_q[15];
  float EQ_L_1_boost[15];
  float EQ_L_1_gain[15];
  
  float EQ_L_2_q[15];
  float EQ_L_2_boost[15];
  float EQ_L_2_gain[15];
  
  float EQ_R_1_q[15];
  float EQ_R_1_boost[15];
  float EQ_R_1_gain[15];
  
  float EQ_R_2_q[15];
  float EQ_R_2_boost[15];
  float EQ_R_2_gain[15];
  
  unsigned char EQ_Sel;
  
  unsigned char BIN_Sel;
  unsigned char OUT_Sel;
  
  float Phat_freq;
  float Phat_gain;
  
  unsigned char Noise_L_en;
  unsigned char Noise_R_en;
  
  float Noise_L_1_vol;
  float Noise_L_2_vol;
  
  float Noise_R_1_vol;
  float Noise_R_2_vol;
  
  float Noise_Mix_L_1;
  float Noise_Mix_L_2;
  
  float Noise_Mix_R_1;
  float Noise_Mix_R_2;
  
  unsigned char Tone_Sel;
  
};


void uDSP_Set_default_val(struct uDSP_Settings *__set);


#endif