/*
 * All rights reserved.
 * @file       		motor.c
 * @brief      		电机驱动函数
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		20220-04-06
 * @note
*/

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机初始化
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Motor_Init();
//-------------------------------------------------------------------------------------------------------------------
void Motor_Init(void)
{
    pwm_init(TIM_5,TIM_5_CH1_A00,12000,0);
    pwm_init(TIM_5,TIM_5_CH2_A01,12000,0);
    pwm_init(TIM_5,TIM_5_CH3_A02,12000,0);
    pwm_init(TIM_5,TIM_5_CH4_A03,12000,0);
    pwm_enable(TIM_5);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      左轮驱动
//  @param      pwm 占空比0——PWM_DUTY_MAX(10000)
//  @return     void
//  @note
//  Sample usage:       L_Contorl();
//-------------------------------------------------------------------------------------------------------------------
void L_Contorl(int pwm)
{
    if(pwm>9500)//上限幅
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,9500);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,0);
    }
    else if(pwm>700) //正转死区电压
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,pwm);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,0);
    }
    else if(pwm>0)
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,700);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,0);
    }
    else if(pwm>-800) //反转死区电压
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,0);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,800);
    }
    else if(pwm>=-9500)
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,0);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,-pwm);
    }
    else//下限幅
    {
        pwm_duty_updata(TIM_5,TIM_5_CH1_A00,0);
        pwm_duty_updata(TIM_5,TIM_5_CH2_A01,9500);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      右轮驱动
//  @param      pwm 占空比0——PWM_DUTY_MAX(10000)
//  @return     void
//  @note
//  Sample usage:       R_Contorl();
//-------------------------------------------------------------------------------------------------------------------
void R_Contorl(int pwm)
{
    if(pwm>9500)//上限幅
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,9500);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,0);
    }
    else if(pwm>800)   //正转死区电压
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,pwm);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,0);
    }
    else if(pwm>0)
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,800);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,0);
    }
    else if(pwm>=-800) //反转死区电压
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,0);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,800);
    }
    else if(pwm>=-9500)
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,0);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,-pwm);
    }
    else//下限幅
    {
        pwm_duty_updata(TIM_5,TIM_5_CH3_A02,0);
        pwm_duty_updata(TIM_5,TIM_5_CH4_A03,9500);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设定电机转速
//  @param      Lpwm    左轮PWM
//  @param      Rpwm    右轮PWM
//  @return     void
//  @note
//  Sample usage:       Motor_Set(5000,5000);
//-------------------------------------------------------------------------------------------------------------------
void Motor_Set(int Lpwm,int Rpwm)
{
    L_Contorl(Lpwm);
    R_Contorl(-Rpwm);
}