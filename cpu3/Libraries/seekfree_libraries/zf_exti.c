/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
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

#include "zf_exti.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief		EXTI �жϳ�ʼ��
// @param		pin				ѡ�� EXTI ����
// @param		trigger			ѡ�񴥷����źŷ�ʽ [EXTI_Trigger_Rising/EXTI_Trigger_Falling/EXTI_Trigger_Rising_Falling]
// @param		priority		ѡ����ж����ȼ� ��Χ [0-7]
// @return		void
// Sample usage:				exti_interrupt_init(A0, EXTI_Trigger_Rising, 0x01);
//-------------------------------------------------------------------------------------------------------------------
void exti_interrupt_init (PIN_enum pin, EXTITrigger_TypeDef trigger, uint8 priority)
{
	EXTI_InitTypeDef EXTI_InitStructure;														// EXTI ���ýṹ��

	gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);												// ��ʼ��ѡ�е�����

	RCC->APB2ENR |= RCC_APB2ENR_EXTI;
	SYSCFG_EXTILineConfig(((pin&0xf0) >> 4), (pin&0x0f));										// �����ö�Ӧ�� GPIO ���� EXTI ����ʹ��
	EXTI_StructInit(&EXTI_InitStructure);														// ��ȡĬ�ϵ� EXTI ����
	EXTI_InitStructure.EXTI_Line = 0x00000001 << (pin&0x0f);									// ���ö�Ӧ�� LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;											// �����ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = trigger;													// ���ô�����ʽ
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;													// ʹ��
	EXTI_Init(&EXTI_InitStructure);																// ��ʼ�� EXTI

	if((pin&0x0f) < 1)
		nvic_init(EXTI0_IRQn, priority, ENABLE);												// EXTI0 ��һ���ж�
	else if((pin&0x0f) < 2)
		nvic_init(EXTI1_IRQn, priority, ENABLE);												// EXTI1 ��һ���ж�
	else if((pin&0x0f) < 3)
		nvic_init(EXTI2_IRQn, priority, ENABLE);												// EXTI2 ��һ���ж�
	else if((pin&0x0f) < 4)
		nvic_init(EXTI3_IRQn, priority, ENABLE);												// EXTI3 ��һ���ж�
	else if((pin&0x0f) < 5)
		nvic_init(EXTI4_IRQn, priority, ENABLE);												// EXTI4 ��һ���ж�
	else if((pin&0x0f) < 10)
		nvic_init(EXTI9_5_IRQn, priority, ENABLE);												// EXTI5_9 ��һ���ж�
	else
		nvic_init(EXTI15_10_IRQn, priority, ENABLE);											// EXTI10_15 ��һ���ж�
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		EXTI �¼���ʼ��
// @param		pin				ѡ�� EXTI ����
// @param		trigger			ѡ�񴥷����źŷ�ʽ [EXTI_Trigger_Rising/EXTI_Trigger_Falling/EXTI_Trigger_Rising_Falling]
// @return		void
// Sample usage:				exti_even_init(A0,EXTI_Trigger_Rising);
//-------------------------------------------------------------------------------------------------------------------
void exti_even_init (PIN_enum pin, EXTITrigger_TypeDef trigger)
{
	EXTI_InitTypeDef EXTI_InitStructure;														// EXTI ���ýṹ��

	gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);												// ��ʼ��ѡ�е�����

	SYSCFG_EXTILineConfig(((pin&0xf0) >> 4), (pin&0x0f));										// �����ö�Ӧ�� GPIO ���� EXTI ����ʹ��
	EXTI_StructInit(&EXTI_InitStructure);														// ��ȡĬ�ϵ� EXTI ����
	EXTI_InitStructure.EXTI_Line = (pin&0x0f);													// ���ö�Ӧ�� LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;												// �����¼�ģʽ
	EXTI_InitStructure.EXTI_Trigger = trigger;													// ���ô�����ʽ
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;													// ʹ��
	EXTI_Init(&EXTI_InitStructure);																// ��ʼ�� EXTI
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		EXTI �ж�ʹ��
// @param		pin				ѡ�� EXTI ����
// @return		void
// Sample usage:				exti_interrupt_enable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_interrupt_enable (PIN_enum pin)
{
	EXTI->IMR |= (0x00000001 << (pin&0x0f));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		EXTI �ж�ʧ��
// @param		pin				ѡ�� EXTI ����
// @return		void
// Sample usage:				exti_interrupt_disable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_interrupt_disable (PIN_enum pin)
{
	EXTI->IMR &= ~(0x00000001 << (pin&0x0f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief		EXTI �¼�ʹ��
//  @param		pin				ѡ�� EXTI ����
//  @return		void
//  Sample usage:				exti_even_enable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_even_enable (PIN_enum pin)
{
	EXTI->EMR |= (0x00000001 << (pin&0x0f));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		EXTI �¼�ʧ��
// @param		pin				ѡ�� EXTI ����
// @return		void
// Sample usage:				exti_even_disable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_even_disable (PIN_enum pin)
{
	EXTI->EMR &= ~(0x00000001 << (pin&0x0f));
}
