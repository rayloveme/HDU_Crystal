/*
 * All rights reserved.
 * @file       		encoder.c
 * @brief               ����������
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-28
 * @note
*/

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������ʼ��
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
//  @brief      ��ȡ��������ֵ
//  @param      void
//  @return     void��ʵ�ʸ�����L_C��R_C�У�
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
*  �������ƣ�int Read_Encoder(u8 TIMX)
*  ����˵������ȡ����������
*  ����˵����u8 TIMX��ʱ��
*  �������أ���������
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ECPULSE1 = Read_Encoder(3); //���� ĸ���ϱ�����3��С��ǰ��Ϊ��ֵ
*************************************************************************/
int Read_Encoder(u8 TIMX)
{
  int Encoder_TIM;
  switch(TIMX)
  {
  case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;//��������
  case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;//��������
  default:  Encoder_TIM=0;
  }
  return Encoder_TIM;
}