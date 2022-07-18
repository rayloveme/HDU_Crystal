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

float jiansu_t_max = 0;
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

    //    tim_interrupt_init_ms(TIM_7, 20, 2); //参数发送中断

    angle_set = angle_test;
    speed_set = speed_test;
    //    speed_set_now = speed_test;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      主控制
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Main_Control();
//-------------------------------------------------------------------------------------------------------------------
#define DOWN_CONDITION 1 //减速条件
#define DOWN 0           //减速值
void Main_Control(void)
{
    Image_Get();
    If_Find_Beacon();
    //数灯（暂未加）
    if (run_mode == 0) //双摄正常跑模式
    {
        //        if (1) //双摄没看到
        if (beacon_flag_2 == 0) //双摄没看到
        {
            //            if (0)
            if (beacon_flag == 1)
            {
                cut_flag = 0;

                speed_set = speed_test;
                jiansu_t_max = 25;

                LocPid_Cal_Dir(&direction, beacon_x, beacon_list[beacon_y]);
                turn_pwm = direction.value;
                                Down_Point_flag = 0;

            }
            else //丢灯
            {
                speed_set = speed_test - 400;
                jiansu_t_max = 60;

                cut_flag = 1;

                Cut_Set(1);
            }
        }
        else //双摄看到咯
        {

            Jiansu_Judge();

            cut_flag = 0;
            if (Down_Point_flag)
            {
                speed_set = speed_test - 500;
                jiansu_t_max = 40;
            }
            else
            {
                speed_set = speed_test;
                jiansu_t_max = 25;
            }

            LocPid_Cal_Dir(&direction_2, beacon_x_2, beacon_list_2[beacon_y_2]);
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
    beacon_list[0] = 64;
    beacon_list[1] = 64;
    beacon_list[2] = 64;
    beacon_list[3] = 64;
    beacon_list[4] = 64;
    beacon_list[5] = 64;
    beacon_list[6] = 64;
    beacon_list[7] = 64;
    beacon_list[8] = 64;
    beacon_list[9] = 64;
    beacon_list[10] = 64;
    beacon_list[11] = 64;
    beacon_list[12] = 64;
    beacon_list[13] = 64;
    beacon_list[14] = 64;
    beacon_list[15] = 64;
    beacon_list[16] = 64;
    beacon_list[17] = 64;
    beacon_list[18] = 64;
    beacon_list[19] = 64;
    beacon_list[20] = 64;
    beacon_list[21] = 64;
    beacon_list[22] = 64;
    beacon_list[23] = 64;
    beacon_list[24] = 64;
    beacon_list[25] = 64;
    beacon_list[26] = 64;
    beacon_list[27] = 64;
    beacon_list[28] = 64;
    beacon_list[29] = 64;
    beacon_list[30] = 64;
    beacon_list[31] = 64;
    beacon_list[32] = 64;
    beacon_list[33] = 64;
    beacon_list[34] = 64;
    beacon_list[35] = 64;
    beacon_list[36] = 64;
    beacon_list[37] = 64;
    beacon_list[38] = 64;
    beacon_list[39] = 64;
    beacon_list[40] = 64;
    beacon_list[41] = 64;
    beacon_list[42] = 64;
    beacon_list[43] = 64;
    beacon_list[44] = 64;
    beacon_list[45] = 64;
    beacon_list[46] = 64;
    beacon_list[47] = 64;
    beacon_list[48] = 64;
    beacon_list[49] = 64;
    beacon_list[50] = 64;
    beacon_list[51] = 64;
    beacon_list[52] = 64;
    beacon_list[53] = 64;
    beacon_list[54] = 64;
    beacon_list[55] = 64;
    beacon_list[56] = 64;
    beacon_list[57] = 64;
    beacon_list[58] = 64;
    beacon_list[59] = 64;
    beacon_list[60] = 64;
    beacon_list[61] = 64;
    beacon_list[62] = 64;
    beacon_list[63] = 64;
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
    beacon_list_2[0] = 65;
    beacon_list_2[1] = 65;
    beacon_list_2[2] = 65;
    beacon_list_2[3] = 65;
    beacon_list_2[4] = 65;
    beacon_list_2[5] = 65;
    beacon_list_2[6] = 65;
    beacon_list_2[7] = 65;
    beacon_list_2[8] = 65;
    beacon_list_2[9] = 65;
    beacon_list_2[10] = 65;
    beacon_list_2[11] = 65;
    beacon_list_2[12] = 65;
    beacon_list_2[13] = 65;
    beacon_list_2[14] = 65;
    beacon_list_2[15] = 65;
    beacon_list_2[16] = 65;
    beacon_list_2[17] = 65;
    beacon_list_2[18] = 65;
    beacon_list_2[19] = 65;
    beacon_list_2[20] = 65;
    beacon_list_2[21] = 65;
    beacon_list_2[22] = 65;
    beacon_list_2[23] = 65;
    beacon_list_2[24] = 70;
    beacon_list_2[25] = 70;
    beacon_list_2[26] = 70;
    beacon_list_2[27] = 70;
    beacon_list_2[28] = 70;
    beacon_list_2[29] = 70;
    beacon_list_2[30] = 70;
    beacon_list_2[31] = 70;
    beacon_list_2[32] = 70;
    beacon_list_2[33] = 70;
    beacon_list_2[34] = 70;
    beacon_list_2[35] = 70;
    beacon_list_2[36] = 70;
    beacon_list_2[37] = 70;
    beacon_list_2[38] = 70;
    beacon_list_2[39] = 70;
    beacon_list_2[40] = 70;
    beacon_list_2[41] = 70;
    beacon_list_2[42] = 70;
    beacon_list_2[43] = 70;
    beacon_list_2[44] = 70;
    beacon_list_2[45] = 70;
    beacon_list_2[46] = 70;
    beacon_list_2[47] = 70;
    beacon_list_2[48] = 70;
    beacon_list_2[49] = 70;
    beacon_list_2[50] = 70;
    beacon_list_2[51] = 70;
    beacon_list_2[52] = 70;
    beacon_list_2[53] = 70;
    beacon_list_2[54] = 70;
    beacon_list_2[55] = 70;
    beacon_list_2[56] = 70;
    beacon_list_2[57] = 70;
    beacon_list_2[58] = 70;
    beacon_list_2[59] = 70;
    beacon_list_2[60] = 70;
    beacon_list_2[61] = 70;
    beacon_list_2[62] = 70;
    beacon_list_2[63] = 70;
}

void Param_Cfg(void)
{
    speed_cl.Kp = 130;
    speed_cl.Ki = 0;
    speed_cl.Kd = 30;
    speed_test = 1500;
    upright.Kp = 200; // 170
    upright.Ki = 1;
    upright.Kd = 30; // 65
    angle_test = 1550;
    gyro_pid.Kp = 80;
    gyro_pid.Ki = 50;
    gyro_pid.Kd = 0;
    direction.Kp = 4000; // 2000
    direction.Ki = 0;
    direction.Kd = 400;
    turn_kp = 0;
    turn_speed = 1200;
    down_point = 65;
    cut_point = 65;
    direction_2.Kp = 4000; // 4000
    direction_2.Ki = 0;
    direction_2.Kd = 400; // 400
}
