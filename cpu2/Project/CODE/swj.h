#ifndef SWJ_H_
#define SWJ_H_

#include "headfile.h"

//��Ҫ�޸ĵĵط�
#define  sw_write_byte(dat)  uart_putchar(UART_4,dat)//���ڷ����ֽ�
#define  sw_write_buffer(dat,len)  uart_putbuff(UART_4,dat,len)//���ڷ�������



/*
 * �޸�˵��:
 * sw_write_byte ȥ�Ҵ��ڿ��еķ����ֽں���
 * sw_write_buffer ȥ�� *���ߴ��� �� �еķ������麯��

 *
 * ���ʹ�õ���ɵĿ� �� ��ɵ�����ģ�� sw_write_buffer���ע��һ��
 * */

//����


void sendimg( uint8 *image, uint8 width, uint8 height);
void sendimg_zoom(uint8* image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height);
void sendimg_binary(uint8* image, uint8 width, uint8 height,uint8 otu);
void sendimg_binary_zoom(uint8* image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height,uint8 otu);
void sendimg_binary_CHK(uint8* image, uint8 width, uint8 height,uint8 otu,uint8 chk);
#endif