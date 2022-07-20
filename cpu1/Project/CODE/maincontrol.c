/*
 * All rights reserved.
 * @file       		maincontrol.c
 * @brief               主控制程�?
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-10
 * @note
 */

#include "headfile.h"

//图像�?
uint8 frame = 10;
uint8 beacon_check_frame = 0;
uint8 beacon_flag = 0, beacon_flag_2 = 0;
uint8 beacon_list[405] = {0};
uint8 beacon_list_2[405] = {0};
uint32 beacon_x = 0, beacon_y = 0, beacon_area = 0;
uint32 last_beacon_x = 0, last_beacon_y = 0;
uint32 beacon_x_2, beacon_y_2, beacon_area_2;

//底层�?
uint16 angle_set = 0; //机械零点左右角度
int16 speed_set = 0;
uint32 angle_test = 0;
uint32 speed_test = 0;
int16 leftpwm = 0;
int16 rightpwm = 0;

//控制�?
uint8 cut_flag;
uint32 run_mode = 0;
uint32 cut_point;
int16 turn_pwm;
uint32 turn_kp = 0, turn_speed = 0;
uint32 jiansu_t_max = 0; //加减速平滑时�?

//-------------------------------------------------------------------------------------------------------------------
//  @brief      所有初始化
//  @param      void
//  @return     void
//  @note
//  Sample usage:       All_Init();
//-------------------------------------------------------------------------------------------------------------------
void All_Init(void)
{

    board_init(false); // 初始�? debug输出串口
    oled_init();

    Key_Init();
    Motor_Init();
    Encoder_Init();
    Beacon_List_Init();
    Beacon_List_2_Init(DIR);
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

    speed_set = speed_test;

    speed_set_now = speed_test; // tmd不知道什么时候会用到

    tim_interrupt_init_ms(TIM_8, 1, 0);  //角速度环中�?
    tim_interrupt_init_ms(TIM_7, 20, 2); //速度�?
    tim_interrupt_init_ms(TIM_6, 5, 1);  //角度�?

    angle_set = angle_test;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      主控�?
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Main_Control();
//-------------------------------------------------------------------------------------------------------------------
uint8 ENVENT;
#define ALL_NO 0
#define UP_ONLY 1
#define DOWM_ONLY 2
#define ALL_OK 3

uint8 Down_Point_flag;
#define NO_DOWN 0 //稳定speedset
#define DOWN_1 1  // 1档位减�? 后续同理
#define DOWN_2 2
#define DOWN_3 3
#define DOWN_4 4
#define UP_1 5 // 1档位加�? 后续同理
#define UP_2 6
#define UP_3 7
#define UP_4 8

#define TURN_MODE_0 0
#define TURN_MODE_1 1
void Main_Control(void)
{
    Image_Get();
    If_Find_Beacon();

    //数灯（暂未加�?

    ENVENT = beacon_flag_2 + beacon_flag_2 + beacon_flag;

    if (run_mode == 0) //双摄正常跑模�?
    {
        switch (ENVENT)
        // switch (ALL_NO)
        {
        case ALL_NO: //都没看到
            if (cut_flag == 0)
                turn_pwm = 0;
            cut_flag = 1;
            // Speed_Control(1000, 60);
            Cut_Set(DIR, TURN_MODE_0);
            Down_Point_flag = 0;
            break;

        case UP_ONLY: //上摄看到
            angle_set = angle_test;
            Jiansu_Judge();
            switch (Down_Point_flag)
            {
            case NO_DOWN:
                Speed_Control(speed_test, 30);
                break;
            case DOWN_1:
                Speed_Control(speed_test - 600, 100);
                break;
            }
            cut_flag = 0;

            // Speed_Control(speed_test, 30);

            LocPid_Cal_Dir(&direction, beacon_x, beacon_list[beacon_y]);
            turn_pwm = direction.value;
            break;

        case ALL_OK: //都看�?
            angle_set = angle_test;

            cut_flag = 0;

            if (1)
            //                            if (Beacon_2_Confirm())
            {
                Jiansu_Judge();

                switch (Down_Point_flag)
                {
                case NO_DOWN:
                    Speed_Control(speed_test, 30);
                    break;
                case DOWN_1:
                    Speed_Control(speed_test - 600, 100);
                    break;
                }

                LocPid_Cal_Dir(&direction_2, beacon_x_2, beacon_list_2[beacon_y_2]);
                turn_pwm = direction_2.value;
            }
            else
            {
                Speed_Control(speed_test, 15);

                LocPid_Cal_Dir(&direction, beacon_x, beacon_list[beacon_y]);
                turn_pwm = direction.value;
                Down_Point_flag = 0;
            }

            break;

        case DOWM_ONLY: //下摄看到
            angle_set = angle_test;

            Jiansu_Judge();
            cut_flag = 0;
            switch (Down_Point_flag)
            {
            case NO_DOWN:
                Speed_Control(speed_test, 30);
                break;
            case DOWN_1:
                Speed_Control(speed_test - 600, 100);
                break;
            }
            LocPid_Cal_Dir(&direction_2, beacon_x_2, beacon_list_2[beacon_y_2]);
            turn_pwm = direction_2.value;
            break;

        default:
            break;
        }
    }
    else if (run_mode == 1) //决赛可能使用 提前做好准备
        ;
    else if (run_mode == 2)
        ;
    else
        ;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化轨迹数�?
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
    beacon_list[40] = 54;
    beacon_list[41] = 54;
    beacon_list[42] = 54;
    beacon_list[43] = 54;
    beacon_list[44] = 54;
    beacon_list[45] = 54;
    beacon_list[46] = 54;
    beacon_list[47] = 54;
    beacon_list[48] = 54;
    beacon_list[49] = 54;
    beacon_list[50] = 54;
    beacon_list[51] = 54;
    beacon_list[52] = 54;
    beacon_list[53] = 54;
    beacon_list[54] = 54;
    beacon_list[55] = 54;
    beacon_list[56] = 54;
    beacon_list[57] = 54;
    beacon_list[58] = 54;
    beacon_list[59] = 54;
    beacon_list[60] = 54;
    beacon_list[61] = 54;
    beacon_list[62] = 54;
    beacon_list[63] = 54;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化轨�?2数组
//  @param      dir 1 right \ 0 left
//  @return     void
//  Sample usage:       Beacon_List_2_Init();
//-------------------------------------------------------------------------------------------------------------------
void Beacon_List_2_Init(uint8 dir)
{
    if (dir)
    {
        //右切
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
        beacon_list_2[24] = 75;
        beacon_list_2[25] = 75;
        beacon_list_2[26] = 75;
        beacon_list_2[27] = 75;
        beacon_list_2[28] = 75;
        beacon_list_2[29] = 75;
        beacon_list_2[30] = 75;
        beacon_list_2[31] = 75;
        beacon_list_2[32] = 75;
        beacon_list_2[33] = 75;
        beacon_list_2[34] = 75;
        beacon_list_2[35] = 75;
        beacon_list_2[36] = 75;
        beacon_list_2[37] = 75;
        beacon_list_2[38] = 75;
        beacon_list_2[39] = 75;
        beacon_list_2[40] = 75;
        beacon_list_2[41] = 75;
        beacon_list_2[42] = 75;
        beacon_list_2[43] = 75;
        beacon_list_2[44] = 75;
        beacon_list_2[45] = 75;
        beacon_list_2[46] = 75;
        beacon_list_2[47] = 75;
        beacon_list_2[48] = 75;
        beacon_list_2[49] = 75;
        beacon_list_2[50] = 75;
        beacon_list_2[51] = 75;
        beacon_list_2[52] = 75;
        beacon_list_2[53] = 75;
        beacon_list_2[54] = 75;
        beacon_list_2[55] = 75;
        beacon_list_2[56] = 75;
        beacon_list_2[57] = 75;
        beacon_list_2[58] = 75;
        beacon_list_2[59] = 75;
        beacon_list_2[60] = 75;
        beacon_list_2[61] = 75;
        beacon_list_2[62] = 75;
        beacon_list_2[63] = 75;
    }
    else
    { //左切
        beacon_list_2[0] = 53;
        beacon_list_2[1] = 53;
        beacon_list_2[2] = 53;
        beacon_list_2[3] = 53;
        beacon_list_2[4] = 53;
        beacon_list_2[5] = 53;
        beacon_list_2[6] = 53;
        beacon_list_2[7] = 53;
        beacon_list_2[8] = 53;
        beacon_list_2[9] = 53;
        beacon_list_2[10] = 50;
        beacon_list_2[11] = 50;
        beacon_list_2[12] = 50;
        beacon_list_2[13] = 50;
        beacon_list_2[14] = 50;
        beacon_list_2[15] = 50;
        beacon_list_2[16] = 50;
        beacon_list_2[17] = 50;
        beacon_list_2[18] = 50;
        beacon_list_2[19] = 50;
        beacon_list_2[20] = 50;
        beacon_list_2[21] = 50;
        beacon_list_2[22] = 50;
        beacon_list_2[23] = 50;
        beacon_list_2[24] = 45;
        beacon_list_2[25] = 45;
        beacon_list_2[26] = 45;
        beacon_list_2[27] = 45;
        beacon_list_2[28] = 45;
        beacon_list_2[29] = 45;
        beacon_list_2[30] = 45;
        beacon_list_2[31] = 45;
        beacon_list_2[32] = 45;
        beacon_list_2[33] = 40;
        beacon_list_2[34] = 40;
        beacon_list_2[35] = 40;
        beacon_list_2[36] = 40;
        beacon_list_2[37] = 40;
        beacon_list_2[38] = 40;
        beacon_list_2[39] = 40;
        beacon_list_2[40] = 40;
        beacon_list_2[41] = 40;
        beacon_list_2[42] = 40;
        beacon_list_2[43] = 34;
        beacon_list_2[44] = 34;
        beacon_list_2[45] = 34;
        beacon_list_2[46] = 34;
        beacon_list_2[47] = 34;
        beacon_list_2[48] = 34;
        beacon_list_2[49] = 34;
        beacon_list_2[50] = 34;
        beacon_list_2[51] = 34;
        beacon_list_2[52] = 33;
        beacon_list_2[53] = 33;
        beacon_list_2[54] = 33;
        beacon_list_2[55] = 33;
        beacon_list_2[56] = 33;
        beacon_list_2[57] = 33;
        beacon_list_2[58] = 33;
        beacon_list_2[59] = 33;
        beacon_list_2[60] = 33;
        beacon_list_2[61] = 33;
        beacon_list_2[62] = 33;
        beacon_list_2[63] = 33;
    }
}

void Param_Cfg(void)
{
    speed_cl.Kp = 130;
    speed_cl.Ki = 0;
    speed_cl.Kd = 30;
    speed_test = 1600;
    upright.Kp = 230; // 170
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
    turn_speed = 1000;
    run_mode = 0;
    cut_point = 65;
    direction_2.Kp = 4000; // 4000
    direction_2.Ki = 0;
    direction_2.Kd = 400; // 400
}
