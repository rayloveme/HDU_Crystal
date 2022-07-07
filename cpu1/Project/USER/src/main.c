/*
 * All rights reserved.
 * @file       		main.c
 * @brief               ������
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-26
 * @note                ���Զ��桪������Ϊ�������Ĵ���
 */

#include "headfile.h"
int main(void)
{
    All_Init();
    menu_flag = 1; //�˵���־λ
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
//������˵��ر�