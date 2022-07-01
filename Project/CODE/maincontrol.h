/*
 * All rights reserved.
 * @file       		maincontrol.h
 * @brief               主控制程序头文件
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-15
 * @note
*/

#ifndef _maincontrol_h
#define _maincontrol_h

#include "headfile.h"



#define std_ANGLE -1300
#define high_ANGLE -1300
#define low_ANGLE -1300



extern uint8 beacon_list[405],frame,beacon_check_frame,beacon_flag;
extern uint8 Down_Point_flag,run_mode;
extern uint32 beacon_x,last_beacon_x,beacon_area,beacon_area_last;
extern uint32 beacon_y,last_beacon_y;
extern uint32 down_point,cut_point,turn_kp,turn_speed;
extern int16 leftpwm,rightpwm,area_change_rate;
extern uint16 angle_set;
extern int16 speed_set;

extern uint32 angle_test,speed_test;
extern uint8 pid_flag;


void All_Init(void);
void Main_Control(void);
void Beacon_List_Init(void);
void Param_Cfg(void);











#endif