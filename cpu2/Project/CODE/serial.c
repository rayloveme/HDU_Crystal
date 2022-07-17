/*
 * All rights reserved.
 * @file       		serial.c
 * @brief           双核通信程序
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-07-08
 * @note
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      传输初始化
//  @param      void
//  @return     void
//  Sample usage:      Send_Init();
//-------------------------------------------------------------------------------------------------------------------
void Send_Init(void)
{
    uart_init(UART_3, 115200, UART3_TX_D08, UART3_RX_D09);

   // uart_init(UART_5, 115200, UART5_TX_A04, UART5_RX_A05);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线发送数据，内部按照匿名通信协议来写
//  @param      void
//  @return     void
//  Sample usage:      Send_To_CPU1();
//-------------------------------------------------------------------------------------------------------------------
void Send_To_CPU1(void)
{
    static uint8 data_buff[30] = {0};
    static uint8 buff0[4], buff1[4], buff2[4], buff3[1];

    memcpy(buff0, &beacon_x, 4);
    memcpy(buff1, &beacon_y, 4);
    memcpy(buff2, &beacon_area, 4);
    memcpy(buff3, &beacon_flag, 1);

    uint8 _cnt = 0;

    data_buff[_cnt++] = 0xAA;
    data_buff[_cnt++] = 0xFF;
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
    data_buff[_cnt++] = buff2[2];
    data_buff[_cnt++] = buff2[3];
    data_buff[_cnt++] = buff3[0];
    data_buff[_cnt++] = 0xCC;

    uart_putbuff(UART_3, &data_buff[0], _cnt);
   //     uart_putbuff(UART_5, &data_buff[0], _cnt);

}
