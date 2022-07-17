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

struct Pid direction, direction_2;
struct Pid speed_cl, gyro_pid;
struct Pid upright, upr_help;

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
//  @brief      位置式pid计算(直立环、速度环)
//  @param      pid     Pid变量地址
//  @param      act     当前状态值
//  @param      set     设定状态值
//  @return     void
//  Sample usage:       PosPid_Cal(&position,beacon_x,60);
//-------------------------------------------------------------------------------------------------------------------
#define I_LIMIT 500
int LocPid_Cal_Upr(struct Pid *pid, int act, int set)
{
    pid->err_1 = pid->err;
    pid->err = set - act;
    pid->inter += pid->err;

    int16 piout = pid->Ki / 1000.0 * (pid->inter);

    if (piout > 500 || piout < -500)
    {
        piout = 0;
    }

    // piout = Int_Range_Protect(piout, -I_LIMIT, I_LIMIT);

    //    piout=0;
    pid->value = pid->Kp / 100.0 * (pid->err) - pid->Kd / 100.0 * (pid->err - pid->err_1) + piout;

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);

    return pid->value;
}

int LocPid_Cal_Spe(struct Pid *pid, int act, int set)
{
    pid->err_1 = pid->err;
    pid->err = set - act;
    pid->inter += pid->err;

    //    if((pid->err < 300) && (pid->err > -300))
    //    {
    //        pid->err=0;
    //    }

    int16 piout = pid->Ki / 1000.0 * (pid->inter);

    if (piout > 500 || piout < -500)
    {
        piout = 0;
    }

    // piout = Int_Range_Protect(piout, -I_LIMIT, I_LIMIT);

    //    piout=0;
    pid->value = pid->Kp / 100.0 * (pid->err) - pid->Kd / 100.0 * (pid->err - pid->err_1) + piout;

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);

    return pid->value;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      位置式pid计算(转向环)
//  @param      pid     Pid变量地址
//  @param      act     当前状态值
//  @param      set     设定状态值
//  @return     void
//  Sample usage:       PosPid_Cal(&position,beacon_x,60);
//-------------------------------------------------------------------------------------------------------------------
#define I_LIMIT_DIR 2000
int LocPid_Cal_Dir(struct Pid *pid, int act, int set)
{
    pid->err_1 = pid->err;
    pid->err = set - act;
    pid->inter += pid->err;

    int16 piout = pid->Ki / 10000.0 * (pid->inter);

    piout = Int_Range_Protect(piout, -I_LIMIT_DIR, I_LIMIT_DIR);
    //    piout=0;
    pid->value = pid->Kp / 100.0 * (pid->err) - pid->Kd / 1000.0 * icm_gyro_z + piout;

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);

    return pid->value;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      增量式pid计算
//  @param      pid     Pid变量地址
//  @param      act     当前状态值
//  @param      set     设定值
//  @return     void
//  Sample usage:       	IncPid_Cal(&gyro_pid, icm_gyro_y, 0 + pidout);
//-------------------------------------------------------------------------------------------------------------------
int IncPid_Cal(struct Pid *pid, int act, int set)
{
    static int pid_temp = 0;
    pid->err_2 = pid->err_1;
    pid->err_1 = pid->err;
    pid->err = set - act;

    if ((pid->err < 400) && (pid->err > -400))
        pid->err = 0;

    pid_temp = pid->Kp / 100.0 * (pid->err - pid->err_1) + pid->Ki / 1000.0 * pid->err + pid->Kd / 100.0 * (pid->err - 2 * pid->err_1 + pid->err_2);
    pid->value += pid_temp;

    pid->value = Int_Range_Protect(pid->value, -6000, 6000);

    return pid->value;
}
