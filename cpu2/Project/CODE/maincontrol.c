/*
 * All rights reserved.
 * @file       		maincontrol.c
 * @brief               主控制程序
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-30
 * @note
 */

#include "headfile.h"

//全局变量区

uint8 frame = 1;
uint8 beacon_check_frame = 0;
uint8 beacon_flag = 0;
uint8 beacon_list[405] = {0};
uint32 beacon_x = 0, beacon_y = 0;
uint32 last_beacon_x = 0, last_beacon_y = 0;
uint32 beacon_area = 0, beacon_area_last = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      所有初始化
//  @param      void
//  @return     void
//  @note
//  Sample usage:       All_Init();
//-------------------------------------------------------------------------------------------------------------------
void All_Init(void)
{
    board_init(false); // 初始化 debug输出串口
                       //    oled_init();
    Beacon_List_Init();
    Param_Cfg();
    Send_Init();
    //    oled_p8x16str(0, 0, "Camera init...");
    mt9v03x_init();
    oled_fill(0x00);
    seekfree_wireless_init();
    //    Buzzer_Init();

    //    BUZZER_ON;
    //    systick_delay_ms(100);
    //    BUZZER_OFF;
    //    systick_delay_ms(100);
    //    BUZZER_ON;
    //    systick_delay_ms(100);
    //    BUZZER_OFF;

    tim_interrupt_init_ms(TIM_7, 10, 2); //参数发送中断
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      主控制
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Main_Control();
//-------------------------------------------------------------------------------------------------------------------
void Main_Control(void)
{
    Image_Get();
    If_Find_Beacon();
        sendimg_WIFI(mt9v03x_image[0], 128, 64);
//    sendimg_WIFI_binary_CHK(mt9v03x_image[0], 128, 64, THRESHOLD, 5);
//    put_int32_WIFI(0, (int32)beacon_x);
//    put_int32_WIFI(1, (int32)beacon_y);
    //    if(beacon_flag)BUZZER_ON;
    //    else BUZZER_OFF;
    //    oled_dis_bmpr(64,128,image_binr[0]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化轨迹数组
//  @param      void
//  @return     void
//  Sample usage:       Beacon_List_Init();
//-------------------------------------------------------------------------------------------------------------------
void Beacon_List_Init(void)
{
    beacon_list[0] = 75;
    beacon_list[1] = 75;
    beacon_list[2] = 75;
    beacon_list[3] = 75;
    beacon_list[4] = 75;
    beacon_list[5] = 75;
    beacon_list[6] = 75;
    beacon_list[7] = 75;
    beacon_list[8] = 75;
    beacon_list[9] = 75;
    beacon_list[10] = 75;
    beacon_list[11] = 75;
    beacon_list[12] = 75;
    beacon_list[13] = 75;
    beacon_list[14] = 75;
    beacon_list[15] = 75;
    beacon_list[16] = 75;
    beacon_list[17] = 75;
    beacon_list[18] = 75;
    beacon_list[19] = 75;
    beacon_list[20] = 75;
    beacon_list[21] = 75;
    beacon_list[22] = 75;
    beacon_list[23] = 75;
    beacon_list[24] = 75;
    beacon_list[25] = 75;
    beacon_list[26] = 75;
    beacon_list[27] = 75;
    beacon_list[28] = 75;
    beacon_list[29] = 75;
    beacon_list[30] = 75;
    beacon_list[31] = 75;
    beacon_list[32] = 75;
    beacon_list[33] = 75;
    beacon_list[34] = 75;
    beacon_list[35] = 75;
    beacon_list[36] = 75;
    beacon_list[37] = 75;
    beacon_list[38] = 75;
    beacon_list[39] = 75;
    beacon_list[40] = 75;
    beacon_list[41] = 75;
    beacon_list[42] = 75;
    beacon_list[43] = 75;
    beacon_list[44] = 75;
    beacon_list[45] = 75;
    beacon_list[46] = 75;
    beacon_list[47] = 75;
    beacon_list[48] = 75;
    beacon_list[49] = 75;
    beacon_list[50] = 75;
    beacon_list[51] = 75;
    beacon_list[52] = 75;
    beacon_list[53] = 75;
    beacon_list[54] = 75;
    beacon_list[55] = 75;
    beacon_list[56] = 75;
    beacon_list[57] = 75;
    beacon_list[58] = 75;
    beacon_list[59] = 75;
    beacon_list[60] = 75;
    beacon_list[61] = 75;
    beacon_list[62] = 75;
    beacon_list[63] = 75;
}

void Param_Cfg(void)
{
    return;
}
