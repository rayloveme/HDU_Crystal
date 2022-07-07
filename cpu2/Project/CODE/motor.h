/*
 * All rights reserved.
 * @file       		motor.h
 * @brief               电机头文件
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-28
 * @note
*/

#ifndef _motor_h
#define _motor_h

#include "headfile.h"

void Motor_Init(void);
void L_Contorl(int pwm);
void R_Contorl(int pwm);
void Motor_Set(int Lpwm,int Rpwm);


#endif