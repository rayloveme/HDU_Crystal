/*
 * All rights reserved.
 * @file       		main.c
 * @brief               主函数
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-26
 * @note                亿言丁真——鉴定为：淳淳的纯纯
 */

#include "headfile.h"
int main(void)
{
    All_Init();
    menu_flag = 1; //菜单标志位
    while (1)
    {
        Main_Control();
        if (menu_flag)
        {
            Key_Operation();
            Show_Control();
        }
    }
}
//发车后菜单关闭