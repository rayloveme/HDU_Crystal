/*
 * All rights reserved.
 * @file       		othercontrol.h
 * @brief              一些别的控�?
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-27
 * @note
 */

#include "headfile.h"

//全局变量区
uint8 Motor_Limit_Ratio = 5;
float k_z=0.1;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      int限幅
//  @param      duty	限幅值
//  @param      min		最小值
//  @param      max		最大值
//  @return     duty 	限幅后输出
//  @note
//  Sample usage:       Int_Range_Protect();
//-------------------------------------------------------------------------------------------------------------------
int32 Int_Range_Protect(int32 duty, int32 min, int32 max)
{
	if (duty >= max)
	{
		return max;
	}
	if (duty <= min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      uint限幅
//  @param      duty	限幅值
//  @param      min		最小值
//  @param      max		最大值
//  @return     duty 	限幅后输出
//  @note
//  Sample usage:       Uint_Range_Protect();
//-------------------------------------------------------------------------------------------------------------------
uint32 Uint_Range_Protect(uint32 duty, uint32 min, uint32 max)
{
	if (duty >= max)
	{
		return max;
	}
	if (duty <= min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机输出动态限幅
//  @param      void
//  @return     void
//  @note
//  Sample usage:       PWM_dynamic_limit();
//-------------------------------------------------------------------------------------------------------------------
void PWM_dynamic_limit(void)
{
	leftpwm = Int_Range_Protect(leftpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
	rightpwm = Int_Range_Protect(rightpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      转向偏差滑动滤波
//  @param      error	转向偏差
//  @return     turn_error 滤波后偏差
//  @note
//  Sample usage:       PWM_dynamic_limit();
//-------------------------------------------------------------------------------------------------------------------
int16 Turn_Error_Filter(int16 error) //转向控制滑动输出滤波
{
	int16 turn_error;
	static int16 pre_turn_error[4];
	pre_turn_error[3] = pre_turn_error[2];
	pre_turn_error[2] = pre_turn_error[1];
	pre_turn_error[1] = pre_turn_error[0];
	pre_turn_error[0] = error;
	turn_error = pre_turn_error[0] * 0.4 + pre_turn_error[1] * 0.3 + pre_turn_error[2] * 0.2 + pre_turn_error[3] * 0.1;
	return turn_error;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      判断是否有灯并找到坐标
//  @param      void
//  @return     void
//  Sample usage:       If_Find_Beacon();
//-------------------------------------------------------------------------------------------------------------------
void If_Find_Beacon(void)
{
    if (Beacon_Find_Bin(image_binr,64,128) == 0)
    {
        beacon_check_frame++;
        if (beacon_check_frame > frame)
            beacon_flag = 0;
        else
        {
            beacon_x=last_beacon_x;
            beacon_y=last_beacon_y;
        }
    }
    else
    {
        beacon_check_frame = 0;
        last_beacon_x=beacon_x;
        last_beacon_y=beacon_y;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      切灯
//  @param      DIR   1左转
//  @return     void
//  Sample usage:       Cut_Set(1);
//-------------------------------------------------------------------------------------------------------------------
void Cut_Set(uint8 DIR)
{
    if(DIR)
       direction.value=turn_speed;
//           +k_z*icm_gyro_z;
    else
       direction.value=-turn_speed;
//           -k_z*icm_gyro_z;
}