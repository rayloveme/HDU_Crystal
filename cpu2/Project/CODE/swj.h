#ifndef SWJ_H_
#define SWJ_H_

#include "headfile.h"

//需要修改的地方
#define  sw_write_byte(dat)  uart_putchar(UART_4,dat)//串口发送字节
#define  sw_write_buffer(dat,len)  uart_putbuff(UART_4,dat,len)//串口发送数组



/*
 * 修改说明:
 * sw_write_byte 去找串口库中的发送字节函数
 * sw_write_buffer 去找 *无线串口 库 中的发送数组函数

 *
 * 如果使用的逐飞的库 和 逐飞的无线模块 sw_write_buffer这个注意一下
 * */

//串口


void sendimg( uint8 *image, uint8 width, uint8 height);
void sendimg_zoom(uint8* image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height);
void sendimg_binary(uint8* image, uint8 width, uint8 height,uint8 otu);
void sendimg_binary_zoom(uint8* image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height,uint8 otu);
void sendimg_binary_CHK(uint8* image, uint8 width, uint8 height,uint8 otu,uint8 chk);
#endif