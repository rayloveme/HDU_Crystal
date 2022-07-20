/*
 * All rights reserved.
 * @file       		flash.c
 * @brief      		flash
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-15
 * @note
*/

#include "headfile.h"

uint32 flash_buffer[DATA_SIZE]={0};
uint32 flash_flag=1;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      flash写入
//  @param      void
//  @return     void
//  Sample usage:       Flash_Write();
//-------------------------------------------------------------------------------------------------------------------
void Flash_Write(void)
{
    flash_buffer[0] =direction.Kp;
    flash_buffer[1] =direction.Ki;
    flash_buffer[2] =direction.Kd;
    flash_buffer[3] =run_mode;
    flash_buffer[4] =cut_point;
    flash_buffer[5] =angle_test;
    flash_buffer[6] =upright.Kp;
    flash_buffer[7] =upright.Ki;
    flash_buffer[8] =upright.Kd;
    flash_buffer[9] =flash_flag;
    flash_buffer[10]=turn_speed;
    flash_buffer[11]=turn_kp;
    flash_buffer[12]=speed_cl.Kp;
    flash_buffer[13]=speed_cl.Ki;
    flash_buffer[14]=speed_cl.Kd;
    flash_buffer[15]=speed_test;
    flash_buffer[16]=gyro_pid.Kp;
    flash_buffer[17]=gyro_pid.Ki;
    flash_buffer[18]=gyro_pid.Kd;
    flash_buffer[19]=direction_2.Kp;
    flash_buffer[20]=direction_2.Ki;
    flash_buffer[21]=direction_2.Kd;



    uart_rx_irq(UART_3, 0);

    flash_erase_page(SECTION_INDEX,PAGE_INDEX);
    flash_page_program(SECTION_INDEX,PAGE_INDEX,flash_buffer,DATA_SIZE);


    systick_delay_ms(1000);

    uart_rx_irq(UART_3, 1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      flash读取
//  @param      void
//  @return     void
//  Sample usage:       Flash_Read();
//-------------------------------------------------------------------------------------------------------------------
void Flash_Read(void)
{
    if(flash_check(SECTION_INDEX,PAGE_INDEX) == 1)
    {
        //读取参数
        flash_page_read(SECTION_INDEX,PAGE_INDEX,flash_buffer,DATA_SIZE);
    }
    else
    {
        //若没有数据则将当前数据写入
        Flash_Write();
    }

    if(flash_buffer[9]==0)
    {
        //恢复出厂设置
        flash_flag=1;
        Flash_Write();
    }
    else
    {
        direction.Kp=flash_buffer[0];
        direction.Ki=flash_buffer[1];
        direction.Kd=flash_buffer[2];
        run_mode  =flash_buffer[3];
        cut_point   =flash_buffer[4];
        angle_test  =flash_buffer[5];
        upright.Kp  =flash_buffer[6];
        upright.Ki  =flash_buffer[7];
        upright.Kd  =flash_buffer[8];
        flash_flag  =flash_buffer[9];
        turn_speed  =flash_buffer[10];
        turn_kp     =flash_buffer[11];
        speed_cl.Kp =flash_buffer[12];
        speed_cl.Ki =flash_buffer[13];
        speed_cl.Kd =flash_buffer[14];
        speed_test  =flash_buffer[15];
        gyro_pid.Kp =flash_buffer[16];
        gyro_pid.Ki =flash_buffer[17];
        gyro_pid.Kd =flash_buffer[18];
        direction_2.Kp =flash_buffer[19];
        direction_2.Ki =flash_buffer[20];
        direction_2.Kd =flash_buffer[21];

    }
}
