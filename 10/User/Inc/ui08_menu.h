#ifndef __ui08__menu__
#define __ui08__menu__

void udsp01_menu_init(uint32_t);

extern uint32_t DSP_Last_AudioFrequency;

#define dsp_menu_items_count            10
#define dsp_max_char_at_line            16
#define dsp_top_items_count             3
#define dsp_menu_DSP_items_count        13
#define dsp_menu_EQ_items_count         67
#define dsp_menu_SET_items_count        7

unsigned char dsp_menu_items_titles[][16]={
"LPF Freq","LPF Gain","LPF Q","LPF Bypass",
"LPF Phase","VOL L Cor","VOL R Cor","PhatStereo",
"PS Freq","PS LVL","Noise","Noise LVL 1","Noise LVL 2"
};

unsigned char eq_menu_items_titles[][16]={
"EQ Type","EQ Together","Tone Bass LVL","Tone Bass Freq",
"Tone Treb Level","Tone Treb Freq","Tone Phase","EQ 20Hz Q",
"EQ 20Hz Bst","EQ 27Hz Q","EQ 27Hz Bst","EQ 35Hz Q",
"EQ 35Hz Bst","EQ 43Hz Q","EQ 43Hz Bst","EQ 51Hz Q",
"EQ 51Hz Bst","EQ 64Hz Q","EQ 64Hz Bst","EQ 80Hz Q",
"EQ 80Hz Bst","EQ 100Hz Q","EQ 100Hz Bst","EQ 125Hz Q","EQ 125Hz Bst",
"EQ 160Hz Q","EQ 160Hz Bst","EQ 200Hz Q","EQ 200Hz Bst",
"EQ 250Hz Q","EQ 250Hz Bst","EQ 315Hz Q","EQ 315Hz Bst",
"EQ 400Hz Q","EQ 400Hz Bst","EQ 500Hz Q","EQ 500Hz Bst",
"EQ 630Hz Q","EQ 630Hz Bst","EQ 800Hz Q","EQ 800Hz Bst",
"EQ 1000Hz Q","EQ 1000Hz Bst","EQ 1250Hz Q","EQ 1250Hz Bst",
"EQ 2000Hz Q","EQ 2000Hz Bst","EQ 2500Hz Q","EQ 2500Hz Bst",
"EQ 3150Hz Q","EQ 3150Hz Bst","EQ 4000Hz Q","EQ 4000Hz Bst",
"EQ 5000Hz Q","EQ 5000Hz Bst","EQ 6300Hz Q","EQ 6300Hz Bst",
"EQ 8000Hz Q","EQ 8000Hz Bst","EQ 10kHz Q","EQ 10kHz Bst",
"EQ 12.5kHz Q","EQ 12.5kHz Bst","EQ 16kHz Q","EQ 16kHz Bst",
"EQ 20kHz Q","EQ 20kHz Bst",
};

unsigned char set_menu_items_titles[][16]={
"Mute Type","Volume Type","DAC Type",
"DAC Filter","DAC Inv R","DAC Inv L","AK4490(3) SC",
};

struct menu_item
{
  unsigned char type;
  unsigned char *text;
  unsigned char selected_index;
  unsigned char count;
  char *items_text[dsp_max_char_at_line];
  _Bool enabled;
};

struct _top_items
{
  unsigned char *title;
  struct menu_item *items;
} top_items;

struct _menu_top_level
{
  struct menu_item top_items[dsp_top_items_count];
  
} menu_top_level;

void udsp01_menu_init(uint32_t freq)
{
  for(unsigned char i=0;i<dsp_top_items_count;i++)
  {
    switch(i)
    {
    case 0:
      {
        // dsp menu
        //menu_top_level.items[i].type=0;
      }
      break;
    case 1:
      {
        //eq menu
        // freq control
      }
      break;
    case 2:
      {
        // set menu
      }
      break;
    }
  }
};

#endif