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

uint8 frame = 5;
uint8 beacon_check_frame = 0;
uint8 beacon_flag = 0;
uint8 run_mode = 0;
// uint8  PID_flag=0;  //pid使能标志位 目前无必要
uint8 Down_Point_flag = 0;
uint8 pid_flag = 1;
uint32 down_point = 40, cut_point = 50;
uint8 beacon_list[405] = {0};
uint32 beacon_x = 0, beacon_y = 0;
uint32 last_beacon_x = 0, last_beacon_y = 0;
uint32 beacon_area = 0, beacon_area_last = 0;
uint32 turn_kp = 0, turn_speed = 0;

uint16 angle_set = 1000; //机械零点左右角度
int16 speed_set = 0;
uint32 angle_test = 90;
uint32 speed_test = 0;
int16 leftpwm = 0;
int16 rightpwm = 0;

uint8 cut_flag;

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
    oled_init();

    Key_Init();
    Motor_Init();
    Encoder_Init();
    Beacon_List_Init();
    Wireless_Init();

    Pid_Init(&upright);
    Pid_Init(&direction);
    Pid_Init(&speed_cl);
    Pid_Init(&gyro_pid);
    Pid_Init(&upr_help);

    oled_p8x16str(0, 0, "IMU init...");
    //IMU_Init();
    oled_fill(0x00);
    oled_p8x16str(0, 0, "Flash init...");
    Param_Cfg();
    Flash_Read();
    oled_fill(0x00);
    oled_p8x16str(0, 0, "Camera init...");
    mt9v03x_init();
    oled_fill(0x00);
    Menu_Init();

    // gpio_init(B0,GPO,1,GPO_PUSH_PULL);

    tim_interrupt_init_ms(TIM_8, 1, 0); //角速度环中断
    tim_interrupt_init_ms(TIM_6, 5, 1); //角度环 内嵌速度环20ms

    tim_interrupt_init_ms(TIM_7, 20, 2); //参数发送中断
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
    angle_set = angle_test;
    //数灯（暂未加）
    if (run_mode == 0)
    {
        if (beacon_flag == 1)
        {
            cut_flag = 0;
            if (beacon_y < down_point) //没到减速点
            {
                LocPid_Cal(&direction, beacon_x, beacon_list[beacon_y]);
                speed_set = speed_test;
            }
            //            else if (beacon_y < cut_point) //到达减速点

            else if ((beacon_y != 404) && (beacon_y < cut_point)) //到达减速点

            {
                if (Down_Point_flag == 0)
                {
                    speed_set = speed_test - 1000;
                    Down_Point_flag = 1;
                }
                LocPid_Cal(&direction, beacon_x, beacon_list[beacon_y]);
            }
            else //到达切灯点
            {
                speed_set = speed_test - 1000;
                direction.value = 400;
                //                speed_set=speed_test;
            }
        }
        else //丢灯
        {
            cut_flag = 1;
            Down_Point_flag = 0;
            Cut_Set(1);
        }
    }
    else if (run_mode == 1)
        ;
    else if (run_mode == 2)
        ;
    else
        ;
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
    speed_cl.Kp = 109;
    speed_cl.Ki = 0;
    speed_cl.Kd = 56;
    speed_test = 1500;
    upright.Kp = 200;
    upright.Ki = 0;
    upright.Kd = 10;
    angle_test = 1700;
    gyro_pid.Kp = 60;
    gyro_pid.Ki = 1;
    gyro_pid.Kd = 0;
    direction.Kp = 1300;
    direction.Ki = 0;
    direction.Kd = 100;
    turn_kp = 0;
    turn_speed = 800;
    down_point = 35;
    cut_point = 60;
    upr_help.Kp = 2000;
    upr_help.Ki = 0;
    upr_help.Kd = 100;
}
