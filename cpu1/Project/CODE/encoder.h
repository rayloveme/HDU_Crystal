/*
 * All rights reserved.
 * @file       		encoder.h
 * @brief               ±àÂëÆ÷Í·ÎÄ¼þ
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-28
 * @note
*/

#ifndef _encoder_h
#define _encoder_h

#include "headfile.h"

extern vint16 L_C,R_C;

void Encoder_Init(void);
void Get_Encoder(void);
int Read_Encoder(u8 TIMX);
void EncInit (void);





#endif