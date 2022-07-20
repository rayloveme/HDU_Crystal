/*
 * All rights reserved.
 * @file       		othercontrol.h
 * @brief              涓€浜涘埆鐨勬帶�????
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-27
 * @note
 */

#include "headfile.h"

//鍏ㄥ眬鍙橀噺鍖?
uint8 Motor_Limit_Ratio = 4;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      int闄愬�??
//  @param      duty	闄愬箙鍊?
//  @param      min		鏈€灏忓�???
//  @param      max		鏈€澶у€?
//  @return     duty 	闄愬箙鍚庤緭�???
//  @note
//  Sample usage:       Int_Range_Protect();
//-------------------------------------------------------------------------------------------------------------------
int32 Int_Range_Protect(int32 duty, int32 min, int32 max)
{
	if (duty >= max)
	{
		return max;
	}
	if (duty < min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      uint闄愬�??
//  @param      duty	闄愬箙鍊?
//  @param      min		鏈€灏忓�???
//  @param      max		鏈€澶у€?
//  @return     duty 	闄愬箙鍚庤緭�???
//  @note
//  Sample usage:       Uint_Range_Protect();
//-------------------------------------------------------------------------------------------------------------------
uint32 Uint_Range_Protect(uint32 duty, uint32 min, uint32 max)
{
	if (duty >= max)
	{
		return max;
	}
	if (duty < min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      鐢垫満杈撳嚭鍔ㄦ€侀檺骞?
//  @param      dir 1 right/0 left
//  @return     void
//  @note
//  Sample usage:       PWM_dynamic_limit();
//-------------------------------------------------------------------------------------------------------------------
void PWM_dynamic_limit(uint8 dir)
{
	//	if (dir)
	//	//����RIght
	//	{
	//		leftpwm = Int_Range_Protect(leftpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
	//		rightpwm = Int_Range_Protect(rightpwm, -1000 * Motor_Limit_Ratio, 0);
	//	}
	//	else
	//	{
	//		leftpwm = Int_Range_Protect(leftpwm, -1000 * Motor_Limit_Ratio, 0);
	//		rightpwm = Int_Range_Protect(rightpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
	//	}

	leftpwm = Int_Range_Protect(leftpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
	rightpwm = Int_Range_Protect(rightpwm, -1000 * Motor_Limit_Ratio, 1000 * Motor_Limit_Ratio);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      鍒ゆ柇鏄惁鏈夌伅骞舵壘鍒板潗鏍?
//  @param      void
//  @return     void
//  Sample usage:       If_Find_Beacon();
//-------------------------------------------------------------------------------------------------------------------
void If_Find_Beacon(void)
{

	if (Beacon_Find_Bin(image_binr) == 0)
	// if (Domain_Find_Bin(image_binr, 64, 128) == 0)
	{
		beacon_check_frame++;
		if (beacon_check_frame > frame)
			beacon_flag = 0;
		else
		{
			beacon_x = last_beacon_x;
			beacon_y = last_beacon_y;
		}
	}
	else
	{
		beacon_check_frame = 0;
		last_beacon_x = beacon_x;
		last_beacon_y = beacon_y;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      鍒囩�??
//  @param      DIR   1宸﹁�??
//  @return     void
//  Sample usage:       Cut_Set(1);
//-------------------------------------------------------------------------------------------------------------------
int16 turn_delta = 2;
void Cut_Set(uint8 dir, uint8 mode)
{
	if (mode)
	{
		spe_flag = 0;
		angle_set = 2500;
		turn_speed = 500;

		if (dir)
			turn_pwm = -turn_speed;
		else
			turn_pwm = turn_speed;
	}
	else
	{
		turn_pwm += turn_delta;
		turn_pwm = Int_Range_Protect(turn_pwm, 50, turn_speed);

		if (dir)
		{
			turn_pwm = -turn_speed;
		}
		else
		{
			turn_pwm = turn_speed;
		}
	}
}

void Jiansu_Judge(void)
{ //根据不同速度 角度 y坐标进行耦合 多尝�?
	if (L_C + R_C > 1200)
	{
		if (beacon_y > 40)
		{
			Down_Point_flag = 1;
			return;
		}
		if (beacon_y_2 > 0)
		{
			Down_Point_flag = 1;
			return;
		}
	}

	else
	{
		;
	}
}

uint8 Beacon_2_Confirm(void)
{
	if (angle_final < 930)
	{
		beacon_flag_2 = 0;
		return 0;
	}
	else if (angle_final < 1085)
	{
		if (beacon_y_2 < 45)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else if (angle_final < 1250)
	{
		if (beacon_y_2 < 40)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else if (angle_final < 1460)
	{
		if (beacon_y_2 < 35)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else if (angle_final < 1670)
	{
		if (beacon_y_2 < 30)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else if (angle_final < 1870)
	{
		if (beacon_y_2 < 25)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else if (angle_final < 2110)
	{
		if (beacon_y_2 < 20)
		{
			beacon_flag_2 = 0;
			return 0;
		}
	}
	else
		return 1;
	return 0;
}

void Speed_Control(uint16 speed, uint8 time)
{
	speed_set = speed;
	jiansu_t_max = time;
}