/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				zf_exti.c
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#ifndef _zf_exti_h
#define _zf_exti_h

#include "common.h"

#include "zf_gpio.h"

void		exti_interrupt_init		(PIN_enum pin, EXTITrigger_TypeDef trigger, uint8 priority);
void		exti_even_init			(PIN_enum pin, EXTITrigger_TypeDef trigger);
void		exti_interrupt_enable	(PIN_enum pin);
void		exti_interrupt_disable	(PIN_enum pin);
void		exti_even_enable		(PIN_enum pin);
void		exti_even_disable		(PIN_enum pin);

#endif