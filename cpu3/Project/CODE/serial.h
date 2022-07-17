/*
 * All rights reserved.
 * @file       		serial.c
 * @brief               ˫��ͨ�ų���ͷ�ļ�
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-08
 * @note
*/

#ifndef _serial_h
#define _serial_h

#include "headfile.h"

void Send_Init(void);
void Send_Process(uint8 rx_data);

#endif