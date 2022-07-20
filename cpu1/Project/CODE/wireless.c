/*
 * All rights reserved.
 * @file       		wireless.c
 * @brief               无线传输程序
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-05-22
 * @note
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线初始化
//  @param      void
//  @return     void
//  Sample usage:      Wireless_Init();
//-------------------------------------------------------------------------------------------------------------------
void Wireless_Init(void)
{
    //        seekfree_wireless_init();

    uart_init(UART_4, 460800, UART4_TX_C10, UART4_RX_C11);

    uart_rx_irq(UART_4, 1); // 使能 UART4 的接收中断
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线发送数据，内部按照匿名通信协议来写
//  @param      void
//  @return     void
//  Sample usage:      Wireless_Send();
//-------------------------------------------------------------------------------------------------------------------
void Wireless_Send_Pra(void)
{
    uint8 data_buff[30] = {0};
    uint8 buff0[4], buff1[4], buff2[2], buff3[2], buff4[2], buff5[2], buff6[2],buff7[1];

    int16 spe = L_C+R_C;
    int16 speL = L_C;
    int16 speR = R_C;
    int16 spe_now=(int16)speed_set_now;

    //这一段根据自己需求来即可
    /*常用值 icm_gyro_x,icm_gyro_y,icm_gyro_z,
    icm_acc_x,icm_acc_y,icm_acc_z,angle_final,angle
    L_C,R_C,beacon_x,beacon_y,speed_set_now,beacon_x_2,beacon_y_2
    */

    memcpy(buff0, &beacon_y, 4);
    memcpy(buff1, &beacon_y_2, 4);

    memcpy(buff2, &spe_now, 2);
    memcpy(buff3, &speed_set, 2);
    memcpy(buff4, &spe, 2);
    memcpy(buff5, &angle_final, 2);
    memcpy(buff6, &icm_gyro_y, 2); //往下降低 往上增加
    memcpy(buff7, &ENVENT, 1);


    uint8 _cnt = 0;
    data_buff[_cnt++] = 0xAA;
    data_buff[_cnt++] = 0xFF;
    data_buff[_cnt++] = 0xF1;
    data_buff[_cnt++] = 19; //发送给上位机的字节数 uint8
    data_buff[_cnt++] = buff0[0];
    data_buff[_cnt++] = buff0[1];
    data_buff[_cnt++] = buff0[2];
    data_buff[_cnt++] = buff0[3];
    data_buff[_cnt++] = buff1[0];
    data_buff[_cnt++] = buff1[1];
    data_buff[_cnt++] = buff1[2];
    data_buff[_cnt++] = buff1[3];
    data_buff[_cnt++] = buff2[0];
    data_buff[_cnt++] = buff2[1];
    data_buff[_cnt++] = buff3[0];
    data_buff[_cnt++] = buff3[1];
    data_buff[_cnt++] = buff4[0];
    data_buff[_cnt++] = buff4[1];
    data_buff[_cnt++] = buff5[0];
    data_buff[_cnt++] = buff5[1];
    data_buff[_cnt++] = buff6[0];
    data_buff[_cnt++] = buff6[1];
        data_buff[_cnt++] = buff7[0];

    uint8 sumcheck = 0; //校验位
    uint8 addcheck = 0; //校验位

    for (uint8 i = 0; i < (data_buff[3] + 4); i++)
    {
        sumcheck += data_buff[i];
        addcheck += sumcheck;
    }

    data_buff[_cnt++] = sumcheck;
    data_buff[_cnt++] = addcheck;
    uart_putbuff(UART_4, &data_buff[0], _cnt);

    //    seekfree_wireless_send_buff(&data_buff[0],_cnt);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      图传
//  @param      void
//  @return     void
//  Sample usage:      Wireless_Send_Img();
//-------------------------------------------------------------------------------------------------------------------
void Wireless_Send_Img(void)
{
    sendimg_binary(image_binr[0], 128, 64, 0);
    // sendimg(mt9v03x_image[0],128,64);
}