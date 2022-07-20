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

extern uint8 beacon_list[405],frame,beacon_check_frame,beacon_flag;
extern uint8 Down_Point_flag;
extern uint32 beacon_x,last_beacon_x,beacon_area,beacon_area_last;
extern uint32 beacon_y,last_beacon_y;
extern uint32 down_point,cut_point,turn_kp,turn_speed;
extern int16 leftpwm,rightpwm,area_change_rate;
extern uint16 angle_set;
extern int16 speed_set;
extern int16 turn_pwm;
extern uint32 angle_test,speed_test;
extern uint8 pid_flag,cut_flag;
extern uint32 run_mode;

extern float  speed_set_now;
extern uint8 spe_flag;
extern uint32 beacon_x_2,beacon_y_2,beacon_area_2;
extern uint8 beacon_flag_2,beacon_list_2[405];

extern uint8 L_flag,R_flag;

extern uint32 jiansu_t_max;

void All_Init(void);
void Main_Control(void);
void Beacon_List_Init(void);
void Param_Cfg(void);
void Beacon_List_2_Init(uint8 dir);


extern uint8 ENVENT;









#endif