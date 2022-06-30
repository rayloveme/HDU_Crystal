/*
 * All rights reserved.
 * @file       		encoder.c
 * @brief               编码器函数
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-28
 * @note
*/

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器初始化
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Encoder_Init();
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Init(void)
{
    tim_encoder_init(TIM_3,TIM_3_ENC1_B04,TIM_3_ENC2_B05);
    tim_encoder_init(TIM_4,TIM_4_ENC1_B06,TIM_4_ENC2_B07);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取编码器数值
//  @param      void
//  @return     void（实际赋到了L_C与R_C中）
//  @note
//  Sample usage:       Get_Encoder()
//-------------------------------------------------------------------------------------------------------------------
vint16 L_C,R_C;
void Get_Encoder(void)
{
    R_C=tim_encoder_get_count(TIM_3);
    tim_encoder_rst(TIM_3);
    L_C=-1*tim_encoder_get_count(TIM_4);
    tim_encoder_rst(TIM_4);
}



/*************************************************************************
*  函数名称：int Read_Encoder(u8 TIMX)
*  功能说明：读取编码器计数
*  参数说明：u8 TIMX定时器
*  函数返回：脉冲数量
*  修改时间：2020年3月10日
*  备    注：ECPULSE1 = Read_Encoder(3); //左电机 母板上编码器3，小车前进为负值
*************************************************************************/
int Read_Encoder(u8 TIMX)
{
  int Encoder_TIM;
  switch(TIMX)
  {
  case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;//编码器用
  case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;//编码器用
  default:  Encoder_TIM=0;
  }
  return Encoder_TIM;
}