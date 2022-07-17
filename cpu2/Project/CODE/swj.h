#ifndef SWJ_H_
#define SWJ_H_

#include "headfile.h"

//��Ҫ�޸ĵĵط�
#define sw_write_byte(dat) uart_putchar(UART_4, dat) //���ڷ����ֽ�
//#define  sw_write_buffer(dat,len)  uart_putbuff(UART_4,dat,len)//���ڷ�������
#define sw_write_buffer(dat, len) seekfree_wireless_send_buff(dat, len)

/*
 * �޸�˵��:
 * sw_write_byte ȥ�Ҵ��ڿ��еķ����ֽں���
 * sw_write_buffer ȥ�� *���ߴ��� �� �еķ������麯��

 *
 * ���ʹ�õ���ɵĿ� �� ��ɵ�����ģ�� sw_write_buffer���ע��һ��
 * */

//����

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

//�ڲ�����
uint16 swj_CRC(uint8 *Buf, uint8 CRC_sta, uint8 CRC_CNT);
int32 ByteToInt(int8 *ndsk);
float ByteToFloat(unsigned char *byteArry);
#endif