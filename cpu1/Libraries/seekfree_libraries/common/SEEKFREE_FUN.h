/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2018,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file       		SEEKFREE_FUN.c
* @company	   		�ɶ���ɿƼ����޹�˾
* @author     		��ɿƼ�(QQ3184284598)
* @version    		�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao   		https://seekfree.taobao.com/
* @date       		2019-04-30
********************************************************************************************************************/

#ifndef _SEEKFREE_FUN_h
#define _SEEKFREE_FUN_h

#include "common.h"

#define myabs(x)			((x>=0)?(x):(-x))
#define limit(x,y)			((x>y)?(y):((x<-y)?(-y):(x)))
#define limit_ab(x,a,b)		((x<a)?(a):((x>b)?(b):(x)))

void  my_delay(volatile long t);
int str_to_int (char *str);
void int_to_str (char *str, int number);
float str_to_float (char *str);
void float_to_str (char *str, float number, uint8 point_bit);

#endif
