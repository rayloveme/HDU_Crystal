/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				zf_gpio.h
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#ifndef _zf_gpio_h
#define _zf_gpio_h

#include "common.h"

typedef enum																					// ö�ٶ˿ڷ���	��ö�ٶ��岻�����û��޸�
{
	GPI = 0x00,																					// ����ܽ�����
	GPO = 0x03,																					// ����ܽ����
}GPIODIR_enum;

typedef enum																					// ö�ٶ˿�ģʽ	��ö�ٶ��岻�����û��޸�
{
	GPI_ANAOG_IN		= 0x00,																	// ����ܽ�ģ������
	GPI_FLOATING_IN		= 0x04,																	// ����ܽŸ�������
	GPI_PULL_DOWN		= 0x28,																	// ����ܽ���������
	GPI_PULL_UP		= 0x48,															// ����ܽ���������

	GPO_PUSH_PULL		= 0x00,																	// ����ܽ��������
	GPO_OPEN_DTAIN		= 0x04,																	// ����ܽſ�©���
	GPO_AF_PUSH_PUL		= 0x08,																	// ����ܽŸ����������
	GPO_AF_OPEN_DTAIN	= 0x0C,																	// ����ܽŸ��ÿ�©���
}GPIOMODE_enum;

typedef enum																					// ö�ٶ˿ڸ���	��ö�ٶ��岻�����û��޸�
{
	GPIO_AF0 = 0x00,																			// ���Ÿ��ù���ѡ��  0
	GPIO_AF1 = 0x01,																			// ���Ÿ��ù���ѡ��  1
	GPIO_AF2 = 0x02,																			// ���Ÿ��ù���ѡ��  2
	GPIO_AF3 = 0x03,																			// ���Ÿ��ù���ѡ��  3
	GPIO_AF4 = 0x04,																			// ���Ÿ��ù���ѡ��  4
	GPIO_AF5 = 0x05,																			// ���Ÿ��ù���ѡ��  5
	GPIO_AF6 = 0x06,																			// ���Ÿ��ù���ѡ��  6
	GPIO_AF7 = 0x07,																			// ���Ÿ��ù���ѡ��  7
	GPIO_AF8 = 0x08,																			// ���Ÿ��ù���ѡ��  8
	GPIO_AF9 = 0x09,																			// ���Ÿ��ù���ѡ��  9
	GPIO_AF10 = 0x0A,																			// ���Ÿ��ù���ѡ�� 10
	GPIO_AF11 = 0x0B,																			// ���Ÿ��ù���ѡ�� 11
	GPIO_AF12 = 0x0C,																			// ���Ÿ��ù���ѡ�� 12
	GPIO_AF13 = 0x0D,																			// ���Ÿ��ù���ѡ�� 13
	GPIO_AF14 = 0x0E,																			// ���Ÿ��ù���ѡ�� 14
	GPIO_AF15 = 0x0F,																			// ���Ÿ��ù���ѡ�� 15
}GPIOAF_enum;

typedef enum																					// ö�ٶ˿ڵ�ƽ	��ö�ٶ��岻�����û��޸�
{
	GPIO_LOW = 0,																				// ����ܽų�ʼ����ƽΪ��
	GPIO_HIGH = 1,																				// ����ܽų�ʼ����ƽΪ��
}GPIOLEVEL_enum;

#define GPIO_PIN_RESET(x)	gpio_group[(x>>4)]->BRR  |= ((uint16_t)0x0001 << (x & 0x0F))		//GPIO��λ
#define GPIO_PIN_SET(x)		gpio_group[(x>>4)]->BSRR  |= ((uint16_t)0x0001 << (x & 0x0F))		//GPIO��λ

extern GPIO_TypeDef *gpio_group[8];

void		gpio_init		(PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum mode);
void		afio_init		(PIN_enum pin, GPIODIR_enum dir, GPIOAF_enum af, GPIOMODE_enum mode);
void		gpio_set		(PIN_enum pin, uint8 dat);
uint8		gpio_get		(PIN_enum pin);
void		gpio_dir		(PIN_enum pin, GPIODIR_enum dir, GPIOMODE_enum mode);
void		gpio_toggle		(PIN_enum pin);

#endif