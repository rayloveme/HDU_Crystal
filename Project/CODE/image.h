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

extern uint8   image_binr[ROW][COL];
extern uint8   row_find[ROW];



void Image_Binarization(uint8 image[ROW][COL],uint8 image_binr[ROW][COL],uint8 value);
uint8 Beacon_Find_Bin(uint8 image[ROW][COL],uint8 height,uint8 width);
void Image_Get(void);
void Beacon_Row_Find(void);
uint8 Beacon_Find_Bin2(void);












#endif