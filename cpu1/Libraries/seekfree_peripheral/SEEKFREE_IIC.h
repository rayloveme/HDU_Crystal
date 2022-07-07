/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2018,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				SEEKFREE_IIC.h
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.32.4 or MDK 5.28
* @Taobao			https://seekfree.taobao.com/
* @date				2020-11-23
* @note
* 					���߶��壺
* 					------------------------------------
* 					ģ��ܽ�			��Ƭ���ܽ�
* 					SCL					�鿴 SEEKFREE_SCL �궨��
* 					SDA					�鿴 SEEKFREE_SDA �궨��
* 					------------------------------------
********************************************************************************************************************/

#ifndef _SEEKFREE_IIC_h
#define _SEEKFREE_IIC_h

#include "common.h"

#include "zf_gpio.h"
#include "zf_systick.h"

// ��� IIC ����
#define SEEKFREE_SCL	B13															// ����SCL����  ���������Ϊ����IO
#define SEEKFREE_SDA	B15															// ����SDA����  ���������Ϊ����IO

#define SDA				((gpio_group[(SEEKFREE_SDA&0xf0)>>4]->IDR & (((uint16_t)0x0001) << (SEEKFREE_SDA&0x0f)))?1:0)
#define SDA0()			GPIO_PIN_RESET (SEEKFREE_SDA)								// IO������͵�ƽ
#define SDA1()			GPIO_PIN_SET (SEEKFREE_SDA)									// IO������ߵ�ƽ
#define SCL0()			GPIO_PIN_RESET (SEEKFREE_SCL)								// IO������͵�ƽ
#define SCL1()			GPIO_PIN_SET (SEEKFREE_SCL)									// IO������ߵ�ƽ
//#define DIR_OUT()		gpio_dir(SEEKFREE_SDA, GPO, GPO_PUSH_PULL)					// �������
//#define DIR_IN()		gpio_dir(SEEKFREE_SDA, GPI, GPO_PUSH_PULL)					// ���뷽��

#define SEEKFREE_ACK	1															// ��Ӧ��
#define SEEKFREE_NACK	0															// ��Ӧ��

typedef enum IIC																	// IIC ģ��
{
	SIMIIC,
	SCCB
} IIC_type;

void	simiic_delay_set		(uint16 time);
void	simiic_ack_main			(uint8 ack_main);
void	simiic_write_reg		(uint8 dev_add, uint8 reg, uint8 dat);
void	simiic_write_regs		(uint8 dev_add, uint8 reg, uint8 *dat, uint8 num);
uint8	simiic_read_reg			(uint8 dev_add, uint8 reg, IIC_type type);
void	simiic_read_regs		(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 num, IIC_type type);
void	simiic_init				(void);

#endif
