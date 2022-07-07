/*
 * All rights reserved.
 * @file       		imu.h
 * @brief               惯性测量单元头文件
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-30
 * @note
*/

#ifndef _IMU_h
#define _IMU_h

#include "headfile.h"

extern int16 angle;
extern int16 angle_final;
//extern float ang_acc,ang_gyro,ang;
void angel_cacul(void);

void IMU_Init(void);
void IMU_Get(void);
void Complementary_Filter(void);
void Kalman_Filter(float angle_m,float gyro_m);
#endif