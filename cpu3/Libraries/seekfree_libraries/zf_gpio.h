/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				zf_gpio.h
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#ifndef _zf_gpio_h
#define _zf_gpio_h

#include "common.h"

typedef enum																					// 枚举端口方向	此枚举定义不允许用户修改
{
	GPI = 0x00,																					// 定义管脚输入
	GPO = 0x03,																					// 定义管脚输出
}GPIODIR_enum;

typedef enum																					// 枚举端口模式	此枚举定义不允许用户修改
{
	GPI_ANAOG_IN		= 0x00,																	// 定义管脚模拟输入
	GPI_FLOATING_IN		= 0x04,																	// 定义管脚浮空输入
	GPI_PULL_DOWN		= 0x28,																	// 定义管脚下拉输入
	GPI_PULL_UP		= 0x48,															// 定义管脚上拉输入

	GPO_PUSH_PULL		= 0x00,																	// 定义管脚推挽输出
	GPO_OPEN_DTAIN		= 0x04,																	// 定义管脚开漏输出
	GPO_AF_PUSH_PUL		= 0x08,																	// 定义管脚复用推挽输出
	GPO_AF_OPEN_DTAIN	= 0x0C,																	// 定义管脚复用开漏输出
}GPIOMODE_enum;

typedef enum																					// 枚举端口复用	此枚举定义不允许用户修改
{
	GPIO_AF0 = 0x00,																			// 引脚复用功能选项  0
	GPIO_AF1 = 0x01,																			// 引脚复用功能选项  1
	GPIO_AF2 = 0x02,																			// 引脚复用功能选项  2
	GPIO_AF3 = 0x03,																			// 引脚复用功能选项  3
	GPIO_AF4 = 0x04,																			// 引脚复用功能选项  4
	GPIO_AF5 = 0x05,																			// 引脚复用功能选项  5
	GPIO_AF6 = 0x06,																			// 引脚复用功能选项  6
	GPIO_AF7 = 0x07,																			// 引脚复用功能选项  7
	GPIO_AF8 = 0x08,																			// 引脚复用功能选项  8
	GPIO_AF9 = 0x09,																			// 引脚复用功能选项  9
	GPIO_AF10 = 0x0A,																			// 引脚复用功能选项 10
	GPIO_AF11 = 0x0B,																			// 引脚复用功能选项 11
	GPIO_AF12 = 0x0C,																			// 引脚复用功能选项 12
	GPIO_AF13 = 0x0D,																			// 引脚复用功能选项 13
	GPIO_AF14 = 0x0E,																			// 引脚复用功能选项 14
	GPIO_AF15 = 0x0F,																			// 引脚复用功能选项 15
}GPIOAF_enum;

typedef enum																					// 枚举端口电平	此枚举定义不允许用户修改
{
	GPIO_LOW = 0,																				// 定义管脚初始化电平为低
	GPIO_HIGH = 1,																				// 定义管脚初始化电平为高
}GPIOLEVEL_enum;

#define GPIO_PIN_RESET(x)	gpio_group[(x>>4)]->BRR  |= ((uint16_t)0x0001 << (x & 0x0F))		//GPIO复位
#define GPIO_PIN_SET(x)		gpio_group[(x>>4)]->BSRR  |= ((uint16_t)0x0001 << (x & 0x0F))		//GPIO置位

extern GPIO_TypeDef *gpio_group[8];

void		gpio_init		(PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum mode);
void		afio_init		(PIN_enum pin, GPIODIR_enum dir, GPIOAF_enum af, GPIOMODE_enum mode);
void		gpio_set		(PIN_enum pin, uint8 dat);
uint8		gpio_get		(PIN_enum pin);
void		gpio_dir		(PIN_enum pin, GPIODIR_enum dir, GPIOMODE_enum mode);
void		gpio_toggle		(PIN_enum pin);

#endif
