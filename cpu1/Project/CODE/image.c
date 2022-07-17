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
//  @brief      图像数组二值化
//  @param      image[ROW][COL]         原图像数组
//  @param      image_binr[ROW][COL]    二值化后图像数组(多个r是因为tmd重复了)
//  @param      value                   二值化阈值
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

struct Domain domain[DOMAIN_NUMBER];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      搜索连通域
//  @param      image[ROW][COL]         二值化后的图像数组
//  @param      height                  高度
//  @param      width                   宽度
//  @return     找到1 没找到0
//  Sample usage:       Beacon_Find_Bin(image_binr,64,128);
//-------------------------------------------------------------------------------------------------------------------
uint8 Domain_Find_Bin(uint8 image[ROW][COL], uint8 height, uint8 width)
{

    int16 i = 0;
    int16 j = 0;
    uint8 area = 0;
    uint8 domain_count = 0;
    uint8 left, up, right, down;
    uint8 find_flag = 0;
    uint8 line_area = 0;      //记录当前行面积
    uint8 last_line_area = 0; //记录上一行面积

    for (i = height - 1; i >= 0; i--)
    {
        line_area = 0;
        for (j = 0; j < width; j++)
        {
            if (image[i][j] == 1)
            {
                if (find_flag == 0)
                {
                    find_flag = 1;
                    left = j;
                    down = i;
                }
                up = i;
                right = j;
                line_area++;
                area++;
            }
        }

        if ((last_line_area > 0 && line_area == 0) || (i == 0 && line_area != 0))
        {
            if (domain_count < DOMAIN_NUMBER)
            {
                beacon_flag = 1;

                domain[domain_count].last_area = domain[domain_count].area;
                domain[domain_count].area = area;
                domain[domain_count].area_change_rate = domain[domain_count].area - domain[domain_count].last_area;
                domain[domain_count].x = (left + right) >> 1;
                domain[domain_count].y = (up + down) >> 1;

                domain_count++;
                left = 0;
                right = 0;
                up = 0;
                down = 0;
                area = 0;
            }
            else
            {
                //目前默认第一个连通域是灯
                beacon_x = domain[0].x;
                beacon_y = domain[0].y;
                beacon_area = domain[0].area;
                return 1;
            }
        }
        last_line_area = line_area;
    }
    if (find_flag == 0)
    {
        //未找到连通域，则清空数据
        beacon_x = 404;
        beacon_y = 404;
        beacon_area = 0;
        return 0;
    }
    beacon_x = domain[0].x;
    beacon_y = domain[0].y;
    beacon_area = domain[0].area;
    if (domain_count < DOMAIN_NUMBER)
    {
        for (uint8 n = 0; n < DOMAIN_NUMBER - domain_count; n++)
        {
            domain[domain_count + n].area = 0;
            domain[domain_count + n].x = 404;
            domain[domain_count + n].y = 404;
        }
    }
    return 1;
}

uint8 Beacon_Find_Bin(uint8 image[ROW][COL])
{
    int16 i = 0;
    int16 j = 0;
    uint8 area = 0;
    uint8 left, up, right, down;
    uint8 find_flag = 0;
    uint8 line_area = 0;      //记录当前行面积
    uint8 last_line_area = 0; //记录上一行面积

    uint8 row_dipingxian = ROW;

    if (angle_final < 1230)
    {
        row_dipingxian = 64;
    }
    else if (angle_final < 1500)
    {
        row_dipingxian = 45;
    }
    else if (angle_final < 1700)
    {
        row_dipingxian = 40;
    }
    else if (angle_final < 1850)
    {
        row_dipingxian = 35;
    }
    else if (angle_final < 2150)
    {
        row_dipingxian = 30;
    }
    else if (angle_final < 2350)
    {
        row_dipingxian = 25;
    }
    else if (angle_final < 2600)
    {
        row_dipingxian = 20;
    }
    else if (angle_final < 2750)
    {
        row_dipingxian = 17;
    }
    else
    {
        row_dipingxian = 0;
    }

    for (i = ROW - 1; i >= row_dipingxian; i--)
    {
        line_area = 0;
        for (j = 0; j < COL; j++)
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
        if ((last_line_area > 0 && line_area == 0) || (i == 0 && line_area != 0))
            break;
        last_line_area = line_area;
    }
    if (area > 0)
    {
        beacon_area = area;
        beacon_x = (left + right) >> 1;
        beacon_y = (up + down) >> 1;
        beacon_flag = 1;
        return 1;
    }
    if (find_flag == 0)
    {
        //未找到灯标，则清空等表面积和数据
        beacon_x = 404;
        beacon_y = 404;
        beacon_area = 0;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从总钻风获取图像
//  @param      void
//  @return     void
//  Sample usage:       Image_Get();
//-------------------------------------------------------------------------------------------------------------------
void Image_Get(void)
{
    if (mt9v03x_finish_flag)
    {
        Image_Binarization(mt9v03x_image, image_binr, 100);
        //            Blink_Img_Fliter();
        mt9v03x_finish_flag = 0;
    }
}
