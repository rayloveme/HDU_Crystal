/*
 * All rights reserved.
 * @file       		maincontrol.c
 * @brief               主控制程序
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-10
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
uint32 down_point, cut_point;
uint8 beacon_list[405] = {0};
uint8 beacon_list_2[405] = {0};
uint32 beacon_x = 0, beacon_y = 0;
uint32 last_beacon_x = 0, last_beacon_y = 0;
uint32 beacon_area = 0, beacon_area_last = 0;
uint32 turn_kp = 0, turn_speed = 0;

uint32 beacon_x_2, beacon_y_2, beacon_area_2;
uint8 beacon_flag_2;

uint16 angle_set = 0; //机械零点左右角度
int16 speed_set = 0;
uint32 angle_test = 0;
uint32 speed_test = 0;
int16 leftpwm = 0;
int16 rightpwm = 0;
int16 turn_pwm;
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
    Beacon_List_2_Init();
    Wireless_Init();
    Send_Init();

    Pid_Init(&upright);
    Pid_Init(&direction);
    Pid_Init(&speed_cl);
    Pid_Init(&gyro_pid);
    Pid_Init(&direction_2);

    oled_p8x16str(0, 0, "IMU init...");
    IMU_Init();
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

    angle_set = angle_test;
    speed_set = speed_test;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      主控制
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Main_Control();
//-------------------------------------------------------------------------------------------------------------------
#define DOWN_CONDITION 1 //减速条件
#define DOWN 0 //减速值
void Main_Control(void)
{
    Image_Get();
    If_Find_Beacon();
    //数灯（暂未加）
    if (run_mode == 0) //双摄正常跑模式
    {
        if (beacon_flag_2 == 0) //双摄没看到
        {
            if (beacon_flag == 1)
            {
                cut_flag = 0;
                if (DOWN_CONDITION) //没到减速点
                {
                    speed_set = speed_test;

                    LocPid_Cal_Dir(&direction, beacon_x, beacon_list[beacon_y]);
                    turn_pwm = direction.value;
                }

                //            else if (beacon_y < cut_point) //到达减速点

                else if ((beacon_y != 404) && (beacon_y < cut_point)) //到达减速点

                {

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

                speed_set = speed_test - DOWN;

                cut_flag = 1;
                Down_Point_flag = 0;
                Cut_Set(0);
            }
        }
        else //双摄看到咯
        {
            if (DOWN_CONDITION)
            {
                if (Down_Point_flag == 0)
                {
                    speed_set = speed_test - DOWN;
                    Down_Point_flag = 1;
                }
            }
            LocPid_Cal_Dir(&direction_2,beacon_x_2,beacon_list_2[beacon_y_2]);
            turn_pwm = direction_2.value;
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
    beacon_list[0] = 80;
    beacon_list[1] = 80;
    beacon_list[2] = 80;
    beacon_list[3] = 80;
    beacon_list[4] = 80;
    beacon_list[5] = 80;
    beacon_list[6] = 80;
    beacon_list[7] = 80;
    beacon_list[8] = 80;
    beacon_list[9] = 80;
    beacon_list[10] = 80;
    beacon_list[11] = 80;
    beacon_list[12] = 80;
    beacon_list[13] = 80;
    beacon_list[14] = 80;
    beacon_list[15] = 80;
    beacon_list[16] = 80;
    beacon_list[17] = 80;
    beacon_list[18] = 80;
    beacon_list[19] = 80;
    beacon_list[20] = 80;
    beacon_list[21] = 80;
    beacon_list[22] = 80;
    beacon_list[23] = 80;
    beacon_list[24] = 80;
    beacon_list[25] = 80;
    beacon_list[26] = 80;
    beacon_list[27] = 80;
    beacon_list[28] = 80;
    beacon_list[29] = 80;
    beacon_list[30] = 80;
    beacon_list[31] = 80;
    beacon_list[32] = 80;
    beacon_list[33] = 80;
    beacon_list[34] = 80;
    beacon_list[35] = 80;
    beacon_list[36] = 80;
    beacon_list[37] = 80;
    beacon_list[38] = 80;
    beacon_list[39] = 80;
    beacon_list[40] = 80;
    beacon_list[41] = 80;
    beacon_list[42] = 80;
    beacon_list[43] = 80;
    beacon_list[44] = 80;
    beacon_list[45] = 80;
    beacon_list[46] = 80;
    beacon_list[47] = 80;
    beacon_list[48] = 80;
    beacon_list[49] = 80;
    beacon_list[50] = 80;
    beacon_list[51] = 80;
    beacon_list[52] = 80;
    beacon_list[53] = 80;
    beacon_list[54] = 80;
    beacon_list[55] = 80;
    beacon_list[56] = 80;
    beacon_list[57] = 80;
    beacon_list[58] = 80;
    beacon_list[59] = 80;
    beacon_list[60] = 80;
    beacon_list[61] = 80;
    beacon_list[62] = 80;
    beacon_list[63] = 80;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化轨迹2数组
//  @param      void
//  @return     void
//  Sample usage:       Beacon_List_2_Init();
//-------------------------------------------------------------------------------------------------------------------
void Beacon_List_2_Init(void)
{
    //
    beacon_list_2[0] =  80;
    beacon_list_2[1] =  80;
    beacon_list_2[2] =  80;
    beacon_list_2[3] =  80;
    beacon_list_2[4] =  80;
    beacon_list_2[5] =  80;
    beacon_list_2[6] =  80;
    beacon_list_2[7] =  80;
    beacon_list_2[8] =  80;
    beacon_list_2[9] =  80;
    beacon_list_2[10] = 80;
    beacon_list_2[11] = 80;
    beacon_list_2[12] = 80;
    beacon_list_2[13] = 80;
    beacon_list_2[14] = 80;
    beacon_list_2[15] = 80;
    beacon_list_2[16] = 80;
    beacon_list_2[17] = 80;
    beacon_list_2[18] = 80;
    beacon_list_2[19] = 80;
    beacon_list_2[20] = 80;
    beacon_list_2[21] = 80;
    beacon_list_2[22] = 80;
    beacon_list_2[23] = 80;
    beacon_list_2[24] = 80;
    beacon_list_2[25] = 80;
    beacon_list_2[26] = 80;
    beacon_list_2[27] = 80;
    beacon_list_2[28] = 80;
    beacon_list_2[29] = 80;
    beacon_list_2[30] = 80;
    beacon_list_2[31] = 80;
    beacon_list_2[32] = 80;
    beacon_list_2[33] = 80;
    beacon_list_2[34] = 80;
    beacon_list_2[35] = 80;
    beacon_list_2[36] = 80;
    beacon_list_2[37] = 80;
    beacon_list_2[38] = 80;
    beacon_list_2[39] = 80;
    beacon_list_2[40] = 80;
    beacon_list_2[41] = 80;
    beacon_list_2[42] = 80;
    beacon_list_2[43] = 80;
    beacon_list_2[44] = 80;
    beacon_list_2[45] = 80;
    beacon_list_2[46] = 80;
    beacon_list_2[47] = 80;
    beacon_list_2[48] = 80;
    beacon_list_2[49] = 80;
    beacon_list_2[50] = 80;
    beacon_list_2[51] = 80;
    beacon_list_2[52] = 80;
    beacon_list_2[53] = 80;
    beacon_list_2[54] = 80;
    beacon_list_2[55] = 80;
    beacon_list_2[56] = 80;
    beacon_list_2[57] = 80;
    beacon_list_2[58] = 80;
    beacon_list_2[59] = 80;
    beacon_list_2[60] = 80;
    beacon_list_2[61] = 80;
    beacon_list_2[62] = 80;
    beacon_list_2[63] = 80;
}

void Param_Cfg(void)
{
    speed_cl.Kp = 100;
    speed_cl.Ki = 5;
    speed_cl.Kd = 50;
    speed_test = 1000;
    upright.Kp = 280;
    upright.Ki = 0;
    upright.Kd = 10;
    angle_test = 1349;
    gyro_pid.Kp = 1199;
    gyro_pid.Ki = 5;
    gyro_pid.Kd = 0;
    direction.Kp = 1000;
    direction.Ki = 0;
    direction.Kd = 200;
    turn_kp = 0;
    turn_speed = 1000;
    down_point = 65;
    cut_point = 65;
    direction_2.Kp = 2000;
    direction_2.Ki = 0;
    direction_2.Kd = 0;
}
