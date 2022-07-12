/*
 * All rights reserved.
 * @file       		buzzer.c
 * @brief               ·äÃùÆ÷
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-07
 * @note
 */

#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ·äÃùÆ÷³õÊ¼»¯
//  @param      void
//  @return     void
//  Sample usage:       void Buzzer_Init(void);
//-------------------------------------------------------------------------------------------------------------------
void Buzzer_Init(void)
{
    gpio_init(G2,GPO,1,GPO_PUSH_PULL);
}
