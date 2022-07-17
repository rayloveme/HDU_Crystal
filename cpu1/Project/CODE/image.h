/*
 * All rights reserved.
 * @file       		image.h
 * @brief               imageͷ�ļ�
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-12-02
 * @note
 */

#ifndef _image_h
#define _image_h

#include "headfile.h"

#define ROW 64
#define COL 128
#define DOMAIN_NUMBER 4 //���Ѱ����ͨ������

struct Domain //��ͨ��
{
    uint8 x;                // x����
    uint8 y;                // y����
    int16 area;             //���
    int16 last_area;        //��һ�����
    int16 area_change_rate; //����仯��
};

extern uint8 image_binr[ROW][COL];

extern struct Domain domain[DOMAIN_NUMBER];
uint8 Beacon_Find_Bin(uint8 image[ROW][COL]);

void Image_Binarization(uint8 image[ROW][COL], uint8 image_binr[ROW][COL], uint8 value);
uint8 Domain_Find_Bin(uint8 image[ROW][COL], uint8 height, uint8 width);
void Image_Get(void);

#endif