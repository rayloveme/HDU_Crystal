#ifndef SWJ_H_
#define SWJ_H_

#include "headfile.h"

//需要修改的地方
#define sw_write_byte(dat) uart_putchar(UART_4, dat) //串口发送字节
//#define  sw_write_buffer(dat,len)  uart_putbuff(UART_4,dat,len)//串口发送数组
#define sw_write_buffer(dat, len) seekfree_wireless_send_buff(dat, len)

/*
 * 修改说明:
 * sw_write_byte 去找串口库中的发送字节函数
 * sw_write_buffer 去找 *无线串口 库 中的发送数组函数

 *
 * 如果使用的逐飞的库 和 逐飞的无线模块 sw_write_buffer这个注意一下
 * */

//串口

void put_int32(uint8 name, int dat);
void put_float(uint8 name, float dat);
void sendimg(uint8 *image, uint8 width, uint8 height);
// void sendimg_line( uint8 *image, uint8 width, uint8 height,uint8 *line);
void sendimg_zoom(uint8 *image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height);
void sendimg_binary(uint8 *image, uint8 width, uint8 height, uint8 otu);
void sendimg_binary_zoom(uint8 *image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height, uint8 otu);
void sendimg_binary_CHK(uint8 *image, uint8 width, uint8 height, uint8 otu, uint8 chk);
void sendline_clear(uint8 color, uint8 width, uint8 height);
void sendline_xy(uint8 *line_zx, uint8 *line_yx, uint32 len);
void sendline(uint8 color, uint8 *buff, uint32 len);
void sendline2(uint8 color, uint8 *linex, uint8 *liney, uint32 len);
// wifi
void sendimg_WIFI(uint8 *image, uint8 width, uint8 height);
void sendimg_WIFI_binary_CHK(uint8 *image, uint8 width, uint8 height, uint8 otu, uint8 chk);
void put_int32_WIFI(uint8 name, int dat);
void put_float_WIFI(uint8 name, float dat);
// void sendimg_WIFI_ZOOM( uint8* image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height);

//内部调用
uint16 swj_CRC(uint8 *Buf, uint8 CRC_sta, uint8 CRC_CNT);
int32 ByteToInt(int8 *ndsk);
float ByteToFloat(unsigned char *byteArry);
#endif