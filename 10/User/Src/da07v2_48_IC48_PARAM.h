/*
 * File:           G:\cloud\manager\Электроника\ЦАП\DA-07\V2\DSP\48k\da07v2_48_IC48_PARAM.h
 *
 * Created:        Thursday, March 26, 2020 10:33:17 PM
 * Description:    da07v2_48:IC48 parameter RAM definitions.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright ©2020 Analog Devices, Inc. All rights reserved.
 */
#ifndef __DA07V2_48_IC48_PARAM_H__
#define __DA07V2_48_IC48_PARAM_H__


/* Module SW vol 1_2 - Single SW slew vol (adjustable)*/
#define MOD_SWVOL1_2_COUNT                             2
#define MOD_SWVOL1_2_DEVICE                            "IC48"
#define MOD_SWVOL1_2_ALG0_TARGET_ADDR                  0
#define MOD_SWVOL1_2_ALG0_TARGET_FIXPT                 0x0026A7C7
#define MOD_SWVOL1_2_ALG0_TARGET_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.301995172040202)
#define MOD_SWVOL1_2_ALG0_TARGET_TYPE                  SIGMASTUDIOTYPE_FIXPOINT
#define MOD_SWVOL1_2_ALG0_STEP_ADDR                    1
#define MOD_SWVOL1_2_ALG0_STEP_FIXPT                   0x00000800
#define MOD_SWVOL1_2_ALG0_STEP_VALUE                   SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000244140625)
#define MOD_SWVOL1_2_ALG0_STEP_TYPE                    SIGMASTUDIOTYPE_FIXPOINT

/* Module SW vol 1 - Single SW slew vol (adjustable)*/
#define MOD_SWVOL1_COUNT                               2
#define MOD_SWVOL1_DEVICE                              "IC48"
#define MOD_SWVOL1_ALG0_TARGET_ADDR                    2
#define MOD_SWVOL1_ALG0_TARGET_FIXPT                   0x0026A7C7
#define MOD_SWVOL1_ALG0_TARGET_VALUE                   SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.301995172040202)
#define MOD_SWVOL1_ALG0_TARGET_TYPE                    SIGMASTUDIOTYPE_FIXPOINT
#define MOD_SWVOL1_ALG0_STEP_ADDR                      3
#define MOD_SWVOL1_ALG0_STEP_FIXPT                     0x00000800
#define MOD_SWVOL1_ALG0_STEP_VALUE                     SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000244140625)
#define MOD_SWVOL1_ALG0_STEP_TYPE                      SIGMASTUDIOTYPE_FIXPOINT

/* Module Phat-Stereo1 - Phat-Stereo*/
#define MOD_PHAT_STEREO1_COUNT                         2
#define MOD_PHAT_STEREO1_DEVICE                        "IC48"
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401SPREADLEVEL_ADDR 4
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401SPREADLEVEL_FIXPT 0x005A9DF7
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401SPREADLEVEL_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.707945784384138)
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401SPREADLEVEL_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401ALPHASPREAD_ADDR 5
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401ALPHASPREAD_FIXPT 0x000F9924
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401ALPHASPREAD_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.121861049856833)
#define MOD_PHAT_STEREO1_ALG0_PHATSTEREOALG19401ALPHASPREAD_TYPE SIGMASTUDIOTYPE_FIXPOINT

#endif
