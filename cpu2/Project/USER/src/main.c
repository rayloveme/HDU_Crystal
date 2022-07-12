/*
 * All rights reserved.
 * @file       		main.c
 * @brief               主函数
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-08
 * @note             cpu2
 */

#include "headfile.h"
int main(void)
{
    All_Init();
    while (1)
    {
        Main_Control();
    }
}
//发车后菜单关闭