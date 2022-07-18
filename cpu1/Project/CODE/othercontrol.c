/*
 * All rights reserved.
 * @file       		othercontrol.h
 * @brief              涓€浜涘埆鐨勬帶锟??
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-27
 * @note
 */

#include "headfile.h"

//鍏ㄥ眬鍙橀噺鍖?
uint8 Motor_Limit_Ratio = 4;
float k_z = 0.1; //瑙掗€熷害璧锋姂鍒惰浆鍚戠殑浣滅敤

//-------------------------------------------------------------------------------------------------------------------
//  @brief      int闄愬箙
//  @param      duty	闄愬箙鍊?
//  @param      min		鏈€灏忓€?
//  @param      max		鏈€澶у€?
//  @return     duty 	闄愬箙鍚庤緭鍑?
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
//  @brief      uint闄愬箙
//  @param      duty	闄愬箙鍊?
//  @param      min		鏈€灏忓€?
//  @param      max		鏈€澶у€?
//  @return     duty 	闄愬箙鍚庤緭鍑?
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
//  @brief      鐢垫満杈撳嚭鍔ㄦ€侀檺骞?
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
//  @brief      杞悜鍋忓樊婊戝姩婊ゆ尝
//  @param      error	杞悜鍋忓樊
//  @return     turn_error 婊ゆ尝鍚庡亸宸?
//  @note
//  Sample usage:       PWM_dynamic_limit();
//-------------------------------------------------------------------------------------------------------------------
int16 Turn_Error_Filter(int16 error) //杞悜鎺у埗婊戝姩杈撳嚭婊ゆ尝
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
//  @brief      鍒囩伅
//  @param      DIR   1宸﹁浆
//  @return     void
//  Sample usage:       Cut_Set(1);
//-------------------------------------------------------------------------------------------------------------------
void Cut_Set(uint8 DIR)
{
	if (DIR)
		turn_pwm = turn_speed;
	else
		turn_pwm = -turn_speed;
}

void Jiansu_Judge(void)
{
	if (angle_final > (2500 - 47 * beacon_y_2))
		Down_Point_flag = 1;
//	else
//		Down_Point_flag = 0;
}
