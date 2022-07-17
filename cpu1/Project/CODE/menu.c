/*
 * All rights reserved.
 * @file       		menu.c
 * @brief      		OLED菜单
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-15
 * @note
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      所有按键初始化
//  @param      void
//  @return     void
//  Sample usage:       Key_Init();
//-------------------------------------------------------------------------------------------------------------------
void Key_Init(void)
{
    gpio_init(G2, GPI, 1, GPI_PULL_UP);
    gpio_init(G3, GPI, 1, GPI_PULL_UP);
    gpio_init(G4, GPI, 1, GPI_PULL_UP);
    gpio_init(G5, GPI, 1, GPI_PULL_UP);
    gpio_init(G6, GPI, 1, GPI_PULL_UP);
    gpio_init(G7, GPI, 1, GPI_PULL_UP);
    gpio_init(G8, GPI, 1, GPI_PULL_UP);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      按键操作函数
//  @param      void
//  @return     void
//  Sample usage:       Key_Operation();
//-------------------------------------------------------------------------------------------------------------------
uint32 menu_flag = 1;       //菜单有效标志位
uint8 showMenuFlag = 0;     // Menu mode
uint8 menu_button_flag = 0; //每次按键刷新全屏
void Key_Operation(void)
{
    if (KEY1 == 0)
    {
        systick_delay_ms(80);
        if (KEY1 == 0)
        {
            showMenuFlag++; //翻页
            if (showMenuFlag == PAGE_NUMBER)
                showMenuFlag = 0;
            menu_button_flag = 1;
            //            oled_fill(0x00);
        }
    }
    if (showMenuFlag == 1)
    { //显示菜单
        if (KEY_DOWN == 0)
        {
            systick_delay_ms(50);
            if (KEY_DOWN == 0 && menu_pointer->down != NULL)
            {
                //                oled_fill(0x00);
                menu_button_flag = 1;
                menu_pointer = menu_pointer->down;
            }
        }
        else if (KEY_UP == 0)
        {
            systick_delay_ms(50);
            if (KEY_UP == 0 && menu_pointer->up != NULL)
            {
                //                oled_fill(0x00);
                menu_button_flag = 1;
                menu_pointer = menu_pointer->up;
            }
        }
        else if (KEY_LEFT == 0)
        {
            systick_delay_ms(50);
            if (KEY_LEFT == 0)
                if (*(menu_pointer->value) > 0)
                    *(menu_pointer->value) = *(menu_pointer->value) - 1;
        }
        else if (KEY_RIGHT == 0)
        {
            systick_delay_ms(50);
            if (KEY_RIGHT == 0)
                if (*(menu_pointer->value) < 65535)
                    *(menu_pointer->value) = *(menu_pointer->value) + 1;
        }
        else if (KEY_ENTER == 0)
        {
            systick_delay_ms(50);
            if (KEY_ENTER == 0)
                ;
            Flash_Write();
        }
    }
    else
    { //运行状态

        //放入按键操作代码
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      菜单显示函数
//  @param      void
//  @return     void
//  Sample usage:       Show_Control();
//-------------------------------------------------------------------------------------------------------------------
void Show_Control(void)
{
    if (showMenuFlag == 2)
    {
        if (menu_button_flag == 1)
        {
            oled_fill(0x00);
            menu_button_flag = 0;
        }

        // gpio_set(B0,1);
        //        oled_p6x8str(52, 0, "MENU 2");

        //        oled_dis_bmp(64,128,mt9v03x_image[0],100);
        oled_dis_bmpr(64, 128, image_binr[0]);
        //        if(beacon_x!=404)
        //
        //            Draw_Beacon(beacon_x,beacon_y);

        //        oled_dis_bmpr(64,128,image_blink[0]);
    }
    else if (showMenuFlag == 1)
    {
        if (menu_button_flag == 1)
        {
            oled_fill(0x00);
            menu_button_flag = 0;
        }
        oled_p6x8str(52, 0, "MENU 1");
        struct sMenu *temp = menu_pointer;
        for (uint8 i = 1; i < 8; i++)
        {
            if (temp == NULL)
                break;
            oled_p6x8str(0, i, (int8 *)(temp->name));
            oled_int16(80, i, (int16)(*(int *)temp->value));
            temp = temp->down;
        }
    }
    else if (showMenuFlag == 0)
    {
        if (menu_button_flag == 1)
        {
            oled_fill(0x00);
            menu_button_flag = 0;
        }
        oled_p6x8str(52, 0, "MENU 0");

        oled_int16(0, 1, icm_gyro_y);
        oled_int16(0, 2, gyro_pid.Kp);
        oled_int16(0, 3, gyro_pid.Kd);
        oled_int16(0, 4, gyro_pid.value);
        oled_int16(0, 6, leftpwm);
        oled_int16(0, 7, rightpwm);

        oled_int16(46, 1, angle_final);
        oled_int16(46, 2, angle_set);
        oled_int16(46, 4, upright.Kp);
        oled_int16(46, 5, upright.Ki);
        oled_int16(46, 6, upright.Kd);
        oled_int16(46, 7, upright.value);

        oled_int16(90, 1, L_C + R_C);
        oled_int16(90, 2, speed_set);
        oled_int16(90, 4, speed_cl.Kp);
        oled_int16(90, 5, speed_cl.Ki);
        oled_int16(90, 6, speed_cl.Kd);
        oled_int16(90, 7, speed_cl.value);
    }
    else
    {
        if (menu_button_flag == 1)
        {
            oled_fill(0x00);
            menu_button_flag = 0;
        }

        oled_p6x8str(52, 0, "MENU 3");

        oled_int16(0, 1, beacon_x);
        oled_int16(0, 2, beacon_y);
        oled_int16(0, 3, beacon_list[beacon_y]);
        oled_int16(0, 5, direction.Kp);
        oled_int16(0, 6, direction.Kd);
        oled_int16(0, 7, direction.value);

        oled_int16(46, 1, beacon_x_2);
        oled_int16(46, 2, beacon_y_2);
        oled_int16(46, 3, beacon_list_2[beacon_x_2]);
        oled_int16(46, 5, direction_2.Kp);
        oled_int16(46, 6, direction_2.Kd);
        oled_int16(46, 7, direction_2.value);

        oled_int16(90, 1, icm_gyro_z);

        oled_int16(90, 3, angle_final);
        oled_int16(90, 4, beacon_x);
        oled_int16(90, 5, beacon_y);



    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化菜单
//  @param      void
//  @return     void
//  Sample usage:       Menu_Init();
//  note:
//-------------------------------------------------------------------------------------------------------------------
Menu PID_menu[MENU_NUMBER];
PMenu menu_pointer = &PID_menu[0];
void Menu_Init(void)
{
    Menu_Item_Init(&PID_menu[0], NULL, &PID_menu[1], "Spe_Kp", &speed_cl.Kp);
    Menu_Item_Init(&PID_menu[1], &PID_menu[0], &PID_menu[2], "Spe_Ki", &speed_cl.Ki);
    Menu_Item_Init(&PID_menu[2], &PID_menu[1], &PID_menu[3], "SPe_Kd", &speed_cl.Kd);
    Menu_Item_Init(&PID_menu[3], &PID_menu[2], &PID_menu[4], "speed_test", &speed_test);
    Menu_Item_Init(&PID_menu[4], &PID_menu[3], &PID_menu[5], "Upr_Kp", &upright.Kp);
    Menu_Item_Init(&PID_menu[5], &PID_menu[4], &PID_menu[6], "Upr_Ki", &upright.Ki);
    Menu_Item_Init(&PID_menu[6], &PID_menu[5], &PID_menu[7], "Upr_Kd", &upright.Kd);
    Menu_Item_Init(&PID_menu[7], &PID_menu[6], &PID_menu[8], "angle_test", &angle_test);
    Menu_Item_Init(&PID_menu[8], &PID_menu[7], &PID_menu[9], "Gyro_Kp", &gyro_pid.Kp);
    Menu_Item_Init(&PID_menu[9], &PID_menu[8], &PID_menu[10], "Gyro_Ki", &gyro_pid.Ki);
    Menu_Item_Init(&PID_menu[10], &PID_menu[9], &PID_menu[11], "Gyro_Kd", &gyro_pid.Kd);
    Menu_Item_Init(&PID_menu[11], &PID_menu[10], &PID_menu[12], "Dir_Kp", &direction.Kp);
    Menu_Item_Init(&PID_menu[12], &PID_menu[11], &PID_menu[13], "Dir_Ki", &direction.Ki);
    Menu_Item_Init(&PID_menu[13], &PID_menu[12], &PID_menu[14], "Dir_Kd", &direction.Kd);
    Menu_Item_Init(&PID_menu[14], &PID_menu[13], &PID_menu[15], "turn_Kp", &turn_kp);
    Menu_Item_Init(&PID_menu[15], &PID_menu[14], &PID_menu[16], "turn_speed", &turn_speed);
    Menu_Item_Init(&PID_menu[16], &PID_menu[15], &PID_menu[17], "down_point", &down_point);
    Menu_Item_Init(&PID_menu[17], &PID_menu[16], &PID_menu[18], "cut_point", &cut_point);
    Menu_Item_Init(&PID_menu[18], &PID_menu[17], &PID_menu[19], "Dir2_Kp", &direction_2.Kp);
    Menu_Item_Init(&PID_menu[19], &PID_menu[18], &PID_menu[20], "Dir2_Ki", &direction_2.Ki);
    Menu_Item_Init(&PID_menu[20], &PID_menu[19], &PID_menu[21], "Dir2_Kd", &direction_2.Kd);
    Menu_Item_Init(&PID_menu[21], &PID_menu[20], &PID_menu[22], "menu_flag", &menu_flag);
    Menu_Item_Init(&PID_menu[22], &PID_menu[21], NULL, "flash_flag", &flash_flag);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化条目
//  @param      destination             此条目（或者说指向此条目的指针）
//  @param      Up                      上指针
//  @param      Down                    下指针
//  @param      Left                    左指针
//  @param      Right                   右指针
//  @param      Name                    条目名称
//  @param      p                       条目值（实际为指向变量的指针）
//  @return     void
//  Sample usage:       Menu_Item_Init(&PID_menu[3], &PID_menu[2], &PID_menu[4], "Pos_Kp", &Pos_Kp);
//  note:
//-------------------------------------------------------------------------------------------------------------------
void Menu_Item_Init(PMenu destination, PMenu Up, PMenu Down, char *Name, uint32 *p)
{
    destination->up = Up;
    destination->down = Down;
    //    destination->left = Left;     暂时不需要啦
    //    destination->right = Right;
    destination->name = Name;
    destination->value = p;
}
