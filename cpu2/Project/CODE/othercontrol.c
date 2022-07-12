/*
 * All rights reserved.
 * @file       		othercontrol.h
 * @brief              一些别的控�??
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-27
 * @note
 */

#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      int限幅
//  @param      duty	限幅�?
//  @param      min		最小�?
//  @param      max		最大�?
//  @return     duty 	限幅后输�?
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
//  @param      duty	限幅�?
//  @param      min		最小�?
//  @param      max		最大�?
//  @return     duty 	限幅后输�?
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
//  @brief      判断是否有灯并找到坐�?
//  @param      void
//  @return     void
//  Sample usage:       If_Find_Beacon();
//-------------------------------------------------------------------------------------------------------------------
void If_Find_Beacon(void)
{
    if (Domain_Find_Bin(image_binr,64,128) == 0)
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