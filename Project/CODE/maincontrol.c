/*
 * All rights reserved.
 * @file       		maincontrol.c
 * @brief               �����Ƴ���
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-06-28
 * @note
*/

#include "headfile.h"

//ȫ�ֱ�����

uint8  frame=5;
uint8  beacon_check_frame=0;
uint8  beacon_flag=0;
uint8  run_mode=0;
//uint8  PID_flag=0;  //pidʹ�ܱ�־λ Ŀǰ�ޱ�Ҫ
uint8  Down_Point_flag=0;
uint8 pid_flag=1;
uint32 down_point=40,cut_point=50;
uint8  beacon_list[405]={0};
uint32 beacon_x=0,beacon_y=0;
uint32 last_beacon_x=0,last_beacon_y=0;
uint32 beacon_area=0,beacon_area_last=0;
int16 area_change_rate=0;
uint32 turn_kp=0,turn_speed=0;

uint16 angle_set=750;//��е������ҽǶ�
uint16 speed_set=0;
uint32 angle_test=90;
uint32 speed_test=0;
int16 leftpwm=0;
int16 rightpwm=0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���г�ʼ��
//  @param      void
//  @return     void
//  @note
//  Sample usage:       All_Init();
//-------------------------------------------------------------------------------------------------------------------
void All_Init(void)
{

    board_init(false);	// ��ʼ�� debug�������
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


    oled_p8x16str(0,0,"IMU init...");
    IMU_Init();
    oled_fill(0x00);
    oled_p8x16str(0,0,"Flash init...");
    Param_Cfg();
    Flash_Read();
    oled_fill(0x00);
    oled_p8x16str(0,0,"Camera init...");
    mt9v03x_init();
    oled_fill(0x00);
    Menu_Init();

    //gpio_init(B0,GPO,1,GPO_PUSH_PULL);

    tim_interrupt_init_ms(TIM_8, 1, 0);	//���ٶȻ��ж�
    tim_interrupt_init_ms(TIM_6, 5, 1);//�ǶȻ� ��Ƕ�ٶȻ�20ms

    tim_interrupt_init_ms(TIM_7, 20, 2);//���������ж�

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Main_Control();
//-------------------------------------------------------------------------------------------------------------------
void Main_Control(void)
{
    Image_Get();
    If_Find_Beacon();
    angle_set=angle_test;
    //���ƣ���δ�ӣ�
    if (run_mode == 0)
    {
        if (beacon_flag == 1)
        {
            if ((area_change_rate<5)||(beacon_y<45)) //û�����ٵ�
            {
                Down_Point_flag = 0;
                LocPid_Cal(&direction,beacon_x,beacon_list[beacon_y]);
                speed_set=speed_test;
            }
            else if (beacon_y < cut_point) //������ٵ�
            {
                if (Down_Point_flag == 0)
                {
                    speed_set=speed_test-3200;
                    Down_Point_flag = 1;
                }
                LocPid_Cal(&direction,beacon_x,beacon_list[beacon_y]);
            }
            else //�����еƵ�
            {
                direction.value=-1000;
//                speed_set=speed_test;
            }
        }
        else //����
        {
            Cut_Set(0);
            speed_set=speed_test;
        }
    }
    else if (run_mode == 1);
    else if (run_mode == 2);
    else;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʼ���켣����
//  @param      void
//  @return     void
//  Sample usage:       Beacon_List_Init();
//-------------------------------------------------------------------------------------------------------------------
void Beacon_List_Init(void)
{
    beacon_list[0]= 55;
    beacon_list[1]= 55;
    beacon_list[2]= 55;
    beacon_list[3]= 55;
    beacon_list[4]= 55;
    beacon_list[5]= 55;
    beacon_list[6]= 55;
    beacon_list[7]= 55;
    beacon_list[8]= 55;
    beacon_list[9]= 55;
    beacon_list[10]=55;
    beacon_list[11]=55;
    beacon_list[12]=55;
    beacon_list[13]=55;
    beacon_list[14]=55;
    beacon_list[15]=55;
    beacon_list[16]=55;
    beacon_list[17]=55;
    beacon_list[18]=55;
    beacon_list[19]=55;
    beacon_list[20]=55;
    beacon_list[21]=55;
    beacon_list[22]=55;
    beacon_list[23]=55;
    beacon_list[24]=55;
    beacon_list[25]=55;
    beacon_list[26]=55;
    beacon_list[27]=55;
    beacon_list[28]=55;
    beacon_list[29]=55;
    beacon_list[30]=55;
    beacon_list[31]=60;
    beacon_list[32]=61;
    beacon_list[33]=61;
    beacon_list[34]=61;
    beacon_list[35]=62;
    beacon_list[36]=62;
    beacon_list[37]=63;
    beacon_list[38]=63;
    beacon_list[39]=64;
    beacon_list[40]=64;
    beacon_list[41]=64;
    beacon_list[42]=65;
    beacon_list[43]=65;
    beacon_list[44]=75;
    beacon_list[45]=75;
    beacon_list[46]=75;
    beacon_list[47]=75;
    beacon_list[48]=75;
    beacon_list[49]=75;
    beacon_list[50]=75;
    beacon_list[51]=75;
    beacon_list[52]=75;
    beacon_list[53]=75;
    beacon_list[54]=75;
    beacon_list[55]=75;
    beacon_list[56]=75;
    beacon_list[57]=75;
    beacon_list[58]=75;
    beacon_list[59]=75;
    beacon_list[60]=75;
    beacon_list[61]=75;
    beacon_list[62]=75;
    beacon_list[63]=75;
}

void Param_Cfg(void)
{
    speed_cl.Kp =109;
    speed_cl.Ki =0;
    speed_cl.Kd =56;
    speed_test  =1500;
    upright.Kp  =200;
    upright.Ki  =0;
    upright.Kd  =10;
    angle_test  =1700;
    gyro_pid.Kp =60;
    gyro_pid.Ki =1;
    gyro_pid.Kd =0;
    direction.Kp=1300;
    direction.Ki=0;
    direction.Kd=100;
    turn_kp     =0;
    turn_speed  =557;
    down_point  =35;
    cut_point   =60;
    upr_help.Kp  =2000;
    upr_help.Ki  =0;
    upr_help.Kd  =100;
}
