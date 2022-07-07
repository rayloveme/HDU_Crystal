/*
 * All rights reserved.
 * @file       		pid.c
 * @brief               pid控制器程序
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-18
 * @note
 */

#include "headfile.h"

struct Pid direction, upright;
struct Pid speed_cl, gyro_pid;
struct Pid upr_help;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pid初始化
//  @param      pid     Pid变量地址
//  @return     0       表示初始化成功
//  Sample usage:       IncPid_L1_Init(&upright);
//-------------------------------------------------------------------------------------------------------------------
uint8 Pid_Init(struct Pid *pid)
{
    pid->Kp = 0;
    pid->Ki = 0;
    pid->Kd = 0;
    pid->err = 0;
    pid->err_1 = 0;
    pid->err_2 = 0;
    pid->inter = 0;
    pid->value = 0;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      位置式pid计算
//  @param      pid     Pid变量地址
//  @param      act     当前状态值
//  @param      set     设定状态值
//  @return     void
//  Sample usage:       PosPid_Cal(&position,beacon_x,60);
//-------------------------------------------------------------------------------------------------------------------
int LocPid_Cal(struct Pid *pid, int act, int set)
{
    pid->err_1 = pid->err;
    pid->err = set - act;
    pid->inter += pid->err;

    
    pid->value = pid->Kp / 100.0 * (pid->err) + pid->Kd / 100.0 * (pid->err - pid->err_1) + pid->Ki / 100.0 * (pid->inter);

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);


    return pid->value;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      增量式pid计算
//  @param      pid     Pid变量地址
//  @param      act     当前状态值
//  @param      set     设定值(目标速度)
//  @return     void
//  Sample usage:       	IncPid_Cal(&gyro_pid, icm_gyro_y, 0 + pidout);
//-------------------------------------------------------------------------------------------------------------------
int IncPid_Cal(struct Pid *pid, int act, int set)
{
    static int pid_temp = 0;
    //    pid->err_2 = pid->err_1;
    pid->err_1 = pid->err;
    pid->err = set - act;

    if ((pid->err < 800) && (pid->err > -800))
        pid_temp = 0;
    else
        pid_temp = pid->Kp / 100.0 * (pid->err - pid->err_1) + pid->Ki / 100.0 * pid->err;
    //               + pid->Kd/100.0 * (pid->err - 2*pid->err_1 + pid->err_2);
    pid->value += pid_temp;

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);

    return pid->value;
}
