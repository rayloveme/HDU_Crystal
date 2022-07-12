/*
 * All rights reserved.
 * @file       		buzzer.c
 * @brief               ������
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-07
 * @note
 */

#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������ʼ��
//  @param      void
//  @return     void
//  Sample usage:       void Buzzer_Init(void);
//-------------------------------------------------------------------------------------------------------------------
void Buzzer_Init(void)
{
    gpio_init(G2,GPO,1,GPO_PUSH_PULL);
}
