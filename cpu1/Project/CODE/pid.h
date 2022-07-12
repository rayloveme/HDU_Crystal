/*
 * All rights reserved.
 * @file       		pid.h
 * @brief               pidÍ·ÎÄ¼þ
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-18
 * @note
*/

#ifndef _PID_h
#define _PID_h

#include "headfile.h"

struct Pid        //Pid
{
    uint32 Kp;
    uint32 Ki;
    uint32 Kd;
    int err;
    int err_1;
    int err_2;
    int inter;
    int value;
};

extern struct Pid speed_cl,gyro_pid;
extern struct Pid direction,upright,direction_2;

uint8 Pid_Init(struct Pid* pid);
int LocPid_Cal(struct Pid* pid, int act, int set);
int IncPid_Cal(struct Pid* pid, int act, int set);
int LocPid_Cal_Dir(struct Pid *pid, int act, int set);
#endif
