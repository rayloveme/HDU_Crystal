/*
 * All rights reserved.
 * @file       		image.c
 * @brief
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-18
 * @note
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͼ�������ֵ��
//  @param      image[ROW][COL]         ԭͼ������
//  @param      image_binr[ROW][COL]    ��ֵ����ͼ������(���r����Ϊtmd�ظ���)
//  @param      value                   ��ֵ����ֵ
//  @return     void
//  Sample usage:       Image_Binarization(image,image_binr,255);
//-------------------------------------------------------------------------------------------------------------------
uint8 image_binr[ROW][COL];
void Image_Binarization(uint8 image[ROW][COL], uint8 image_binr[ROW][COL], uint8 value)
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            if (image[i][j] >= value)
                image_binr[i][j] = 1;
            else
                image_binr[i][j] = 0;
        }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���gg���ű���ҷ�
//  @param      image[ROW][COL]         ��ֵ�����ͼ������
//  @param      height                  �߶�
//  @param      width                   ���
//  @return     �ҵ�1 û�ҵ�0
//  Sample usage:       Beacon_Find_Bin(image_binr,64,128);
//-------------------------------------------------------------------------------------------------------------------
uint8 Beacon_Find_Bin(uint8 image[ROW][COL], uint8 height, uint8 width)
{
    uint8 i = 0;
    uint8 j = 0;
    uint8 area = 0;
    uint8 left, up, right, down;
    uint8 find_flag = 0;
    uint8 line_area = 0;      //��¼��ǰ�����
    uint8 last_line_area = 0; //��¼��һ�����
    for (i = height - 1; i > 0; i--)
    {
        line_area = 0;
        for (j = 0; j < width; j++)
        {
            if (image[i][j] == 1 && find_flag == 0)
            {
                left = j;
                down = i;
                find_flag = 1;
            }
            if (image[i][j] == 1)
            {
                area++;
                up = i;
                right = j;
                line_area++;
            }
        }
        if (last_line_area > 0 && line_area == 0)
            break;
        last_line_area = line_area;
    }
    if (area > 0)
    {
        beacon_area_last=beacon_area;
        beacon_area = area;
        area_change_rate=beacon_area-beacon_area_last;
        beacon_x = (left + right) >> 1;
        beacon_y = (up + down) >> 1;
        beacon_flag = 1;
        return 1;
    }
    if (find_flag == 0)
    {
        //δ�ҵ��Ʊ꣬����յȱ����������
        beacon_x = 404;
        beacon_y = 404;
        beacon_area = 0;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������ȡͼ��
//  @param      void
//  @return     void
//  Sample usage:       Image_Get();
//-------------------------------------------------------------------------------------------------------------------
void Image_Get(void)
{
    if (mt9v03x_finish_flag)
    {
        Image_Binarization(mt9v03x_image, image_binr, 110);
        //            Blink_Img_Fliter();
        mt9v03x_finish_flag = 0;
    }
}
