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
    uart_rx_irq(UART_3, 1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      传输数据接收
//  @param      rx_data 输入字节
//  @return     void
//  Sample usage:      Send_Process();
//-------------------------------------------------------------------------------------------------------------------
void Send_Process(uint8 rx_data)
{
    static uint8 i = 0, cpu2_buff[16] = {0};
    static uint8 buff0[4], buff1[4], buff2[4], buff3[1];

    cpu2_buff[i] = rx_data;

    if (cpu2_buff[0] != 0xAA)
        i = 0;
    else if (i == 1 && cpu2_buff[1] != 0xFF)
        i = 0;
    else if (i == 15 && cpu2_buff[15] == 0xCC)
    {
        i--;
        buff3[0] = cpu2_buff[i--];

        buff2[3] = cpu2_buff[i--];
        buff2[2] = cpu2_buff[i--];
        buff2[1] = cpu2_buff[i--];
        buff2[0] = cpu2_buff[i--];

        buff1[3] = cpu2_buff[i--];
        buff1[2] = cpu2_buff[i--];
        buff1[1] = cpu2_buff[i--];
        buff1[0] = cpu2_buff[i--];

        buff0[3] = cpu2_buff[i--];
        buff0[2] = cpu2_buff[i--];
        buff0[1] = cpu2_buff[i--];
        buff0[0] = cpu2_buff[i--];

        i = 0;

        memcpy(&beacon_x_2, buff0, 4);
        memcpy(&beacon_y_2, buff1, 4);
        memcpy(&beacon_area_2, buff2, 4);
        memcpy(&beacon_flag_2, buff3, 1);
    }
    else
        i++;
}
