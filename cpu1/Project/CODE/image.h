/*
 * All rights reserved.
 * @file       		image.h
 * @brief               imageÍ·ÎÄ¼þ
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



extern uint8 image_binr[ROW][COL];

uint8 Beacon_Find_Bin(uint8 image[ROW][COL]);

void Image_Binarization(uint8 image[ROW][COL], uint8 image_binr[ROW][COL], uint8 value);
void Image_Get(void);

#endif