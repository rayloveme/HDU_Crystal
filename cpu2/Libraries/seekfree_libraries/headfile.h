/*
 * All rights reserved.
 * @file       		headfile.h
 * @brief               总头文件
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-28
 * @note
*/

#ifndef _headfile_h
#define _headfile_h

#include <stdint.h>

#include "common.h"
#include "core_cm3.h"
#include "board.h"

//------逐飞科技 功能函数头文件
#include "SEEKFREE_ASSERT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_PRINTF.h"

//------逐飞科技 单片机外设驱动头文件
#include "zf_adc.h"
#include "zf_camera.h"
#include "zf_exti.h"
#include "zf_flash.h"
#include "zf_gpio.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_tim.h"
#include "zf_uart.h"
#include "zf_fsmc.h"
//#include "zf_driver_encoder.h"

//------逐飞科技 产品模块驱动头文件
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_UART_7725.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_MT9V03X.h"

//--------------ray-----------------
#include "maincontrol.h"
#include "encoder.h"
#include "imu.h"
#include "menu.h"
#include "motor.h"
#include "pid.h"
#include "flash.h"
#include "image.h"
#include "wireless.h"
#include "swj.h"
#include "mymath.h"
#include "othercontrol.h"
#endif

