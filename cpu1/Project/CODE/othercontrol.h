/*
 * All rights reserved.
 * @file       		othercontrol.h
 * @brief              其他控制程序头文�?
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-27
 * @note
*/

#ifndef _othercontrol_h
#define _othercontrol_h

#include "headfile.h"

extern uint8 Motor_Limit_Ratio;

int32 Int_Range_Protect(int32 duty, int32 min, int32 max);
uint32 Uint_Range_Protect(uint32 duty, uint32 min, uint32 max);
void PWM_dynamic_limit(uint8 dir);
void If_Find_Beacon(void);
void Cut_Set(uint8 dir, uint8 mode);
void Jiansu_Judge(void);
uint8 Beacon_2_Confirm(void);

void Speed_Control(uint16 speed, uint8 time);


#endif