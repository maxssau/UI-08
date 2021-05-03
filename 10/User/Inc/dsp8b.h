
/*******************************************************************************
* image
* filename: unsaved
* name: dsp8b
*
* preset name: Цветное R5G6B5
* data block size: 16 bit(s), uint16_t
* RLE compression enabled: no
* conversion type: Color, not_used not_used
* bits per pixel: 16
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <stdint.h>



static const uint16_t image_data_dsp8b[1024] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0xe7fd, 0xc7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0xe7fd, 0xc7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x2afe, 0xe7fd, 0x2bfe, 0xe8fd, 0x09fe, 0x09fe, 0xe8fd, 0x2afe, 0xe7fd, 0x2afe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x6dfe, 0x99ff, 0x4bfe, 0x79ff, 0x6dfe, 0x14ff, 0x14ff, 0x6dfe, 0x79ff, 0x4bfe, 0x99ff, 0x6dfe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x67ed, 0xabb4, 0x53ad, 0x6aac, 0x33ad, 0x8bac, 0xf0ac, 0xf0ac, 0x8bac, 0x33ad, 0x6aac, 0x53ad, 0xabb4, 0x67ed, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x6dfe, 0xabb4, 0xe739, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0x2842, 0xe739, 0xabb4, 0x4dfe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0x2afe, 0x99ff, 0x53ad, 0x2842, 0x8e73, 0xcf7b, 0xcf7b, 0xcf7b, 0xcf7b, 0xcf7b, 0xcf7b, 0xcf7b, 0xcf7b, 0x0c63, 0x0842, 0x12a5, 0x38f7, 0x0afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x4bfe, 0x6aac, 0x2842, 0xef7b, 0xb294, 0x9294, 0xb294, 0x9294, 0x9294, 0x9294, 0x3184, 0x6e6b, 0xcb5a, 0x0842, 0x6aac, 0x2afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0x2bfe, 0x79ff, 0x32ad, 0x2842, 0xef7b, 0xb294, 0x9294, 0xb294, 0x518c, 0x5184, 0x3184, 0x8e73, 0xec5a, 0xcb52, 0x0842, 0x12ad, 0x37f7, 0x0afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x6dfe, 0x8bac, 0x2842, 0xcf7b, 0x518c, 0x5184, 0x518c, 0x1084, 0x1084, 0x6e6b, 0xec5a, 0xeb5a, 0xcb5a, 0x0842, 0x8bac, 0x4dfe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x09fe, 0x14ff, 0xf0ac, 0x2842, 0xcf7b, 0x1084, 0x1084, 0x1084, 0x1084, 0x6e6b, 0xec5a, 0xeb5a, 0xeb5a, 0xcb5a, 0x0842, 0xcfac, 0xd3fe, 0x09fe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x09fe, 0x14ff, 0xf0ac, 0x2842, 0xcf7b, 0x1084, 0x1084, 0x1084, 0x6e6b, 0xec5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xcb5a, 0x0842, 0xcfac, 0xd3fe, 0x09fe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x6dfe, 0x8bac, 0x2842, 0xcf7b, 0x1084, 0x1084, 0x6e6b, 0xec5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xcb5a, 0x0842, 0x8bac, 0x4dfe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0x2afe, 0x79ff, 0x33ad, 0x2842, 0xcf7b, 0x1084, 0x6e6b, 0xec5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xcb5a, 0x0842, 0x12ad, 0x37f7, 0x0afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x4bfe, 0x6aac, 0x2842, 0xcf7b, 0x6e6b, 0xec5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xeb5a, 0xcb5a, 0x0842, 0x6aac, 0x2afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xc7fd, 0x2afe, 0x99ff, 0x53ad, 0x2842, 0x0c63, 0xcb5a, 0xcb52, 0xcb5a, 0xcb5a, 0xcb5a, 0xcb5a, 0xcb5a, 0xcb5a, 0xab52, 0x0842, 0x12a5, 0x38f7, 0x0afe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x6dfe, 0xabb4, 0xe739, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842, 0xe739, 0xabb4, 0x4dfe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x67ed, 0xabb4, 0x12a5, 0x6aac, 0x12ad, 0x8bac, 0xcfac, 0xcfac, 0x8bac, 0x12ad, 0x6aac, 0x12a5, 0xabb4, 0x67ed, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 
    0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0x4dfe, 0x38f7, 0x2afe, 0x37f7, 0x4dfe, 0xd3fe, 0xd3fe, 0x4dfe, 0x37f7, 0x2afe, 0x38f7, 0x4dfe, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe8fd, 0x0afe, 0xe7fd, 0x0afe, 0xe8fd, 0x09fe, 0x09fe, 0xe8fd, 0x0afe, 0xe7fd, 0x0afe, 0xe8fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xe7fd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};


