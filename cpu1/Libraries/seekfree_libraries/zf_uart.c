/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				zf_uart.c
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#include "zf_uart.h"
#include "zf_gpio.h"

UART_TypeDef *uart_index[8] = {UART1, UART2, UART3, UART4, UART5, UART6, UART7, UART8};
IRQn_Type uart_irq[8] = {UART1_IRQn, UART2_IRQn, UART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn, UART8_IRQn};

//-------------------------------------------------------------------------------------------------------------------
// @brief		UART 引脚初始化 内部调用
// @param		tx_pin			选择 TX 引脚
// @param		rx_pin			选择 RX 引脚
// @return		void
// Sample usage:				uart_pin_init(tx_pin, rx_pin);
//-------------------------------------------------------------------------------------------------------------------
static void uart_pin_init (UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
	afio_init((PIN_enum)(tx_pin &0xff), GPO, (GPIOAF_enum)((tx_pin &0xf00)>>8), GPO_AF_PUSH_PUL);// 提取对应IO索引 AF功能编码
	afio_init((PIN_enum)(rx_pin &0xff), GPI, (GPIOAF_enum)((rx_pin &0xf00)>>8), GPI_FLOATING_IN);// 提取对应IO索引 AF功能编码
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口初始化
// @param		uartn			串口模块号
// @param		baud			串口波特率
// @param		tx_pin			串口发送引脚
// @param		rx_pin			串口接收引脚
// @return		void
// Sample usage:				uart_init(UART_1,115200,UART1_TX_A09,UART1_RX_A10);				// 初始化串口1 波特率115200 发送引脚使用PA09 接收引脚使用PA10
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uartn, uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
	uart_pin_init(tx_pin, rx_pin);																// 引脚初始化

	switch(uartn)
	{
		case UART_1:
			RCC->APB2ENR |= RCC_APB2ENR_UART1;
			RCC->APB2RSTR |= (RCC_APB2RSTR_UART1);
			RCC->APB2RSTR &= ~(RCC_APB2RSTR_UART1);
			break;
		case UART_2:
			RCC->APB1ENR |= RCC_APB1ENR_UART2;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART2);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART2);
			break;
		case UART_3:
			RCC->APB1ENR |= RCC_APB1ENR_UART3;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART3);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART3);
			break;
		case UART_4:
			RCC->APB1ENR |= RCC_APB1ENR_UART4;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART4);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4);
			break;
		case UART_5:
			RCC->APB1ENR |= RCC_APB1ENR_UART5;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART5);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5);
			break;
		case UART_6:
			RCC->APB2ENR |= RCC_APB2ENR_UART6;
			RCC->APB2RSTR |= (RCC_APB2RSTR_UART6);
			RCC->APB2RSTR &= ~(RCC_APB2RSTR_UART6);
			break;
		case UART_7:
			RCC->APB1ENR |= RCC_APB1ENR_UART7;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART7);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART7);
			break;
		case UART_8:
			RCC->APB1ENR |= RCC_APB1ENR_UART8;
			RCC->APB1RSTR |= (RCC_APB1RSTR_UART8);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART8);
			break;
	}
	uart_index[uartn]->BRR = (SystemCoreClock / baud) / 16;										// 设置波特率
	uart_index[uartn]->FRA = (SystemCoreClock / baud) % 16;										// 设置波特率
	uart_index[uartn]->CCR |= UART_CCR_CHAR;													// 8bits 数据位
	uart_index[uartn]->GCR |= UART_GCR_TX | UART_GCR_RX | UART_GCR_UART;						// 使能 TX RX UART
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口字节输出
// @param		uartn			串口模块号
// @param		dat				需要发送的字节
// @return		void
// Sample usage:				uart_putchar(UART_1,0xA5);										// 串口1发送0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uartn, uint8 dat)
{
	uart_index[uartn]->TDR = dat;																// 写入发送数据
	while(!(uart_index[uartn]->CSR & UART_CSR_TXC));											// 等待发送完成
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口发送数组
// @param		uartn			串口模块号
// @param		*buff			要发送的数组地址
// @param		len				发送长度
// @return		void
// Sample usage:				uart_putbuff(UART_1,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len)
{
	while(len)																					// 循环到发送完
	{
		uart_index[uartn]->TDR = *buff++;														// 写入发送数据
		while(!(uart_index[uartn]->CSR & UART_CSR_TXC));										// 等待发送完成
		len--;
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口发送字符串
// @param		uartn			串口模块号
// @param		*str			要发送的字符串地址
// @return		void
// Sample usage:				uart_putstr(UART_1,"i lvoe you");
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uartn, const uint8 *str)
{
	while(*str)																					// 一直循环到结尾
	{
		uart_putchar(uartn, *str++);															// 发送数据
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		读取串口接收的数据（whlie等待）
// @param		uartn			串口模块号
// @param		*dat			接收数据的地址
// @return		void
// Sample usage:				uint8 dat; uart_getchar(UART_1,&dat);							// 接收串口1数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
void uart_getchar(UARTN_enum uartn, uint8 *dat)
{
	while(!(uart_index[uartn]->CSR & UART_CSR_RXAVL));											// 等待读取到一个数据
	*dat = (uint8)uart_index[uartn]->RDR;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		读取串口接收的数据（查询接收）
// @param		uartn			串口模块号
// @param		*dat			接收数据的地址
// @return		uint8			1：接收成功   0：未接收到数据
// Sample usage:				uint8 dat; uart_query(UART_1,&dat);								// 接收串口1数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query(UARTN_enum uartn, uint8 *dat)
{
	if(uart_index[uartn]->CSR & UART_CSR_RXAVL)													// 读取到一个数据
	{
		*dat = (uint8)uart_index[uartn]->RDR;													// 存储一个数据
		return 1;
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口发送中断设置
// @param		uartn			串口模块号
// @param		status			1：打开中断   0：关闭中断
// @return		void
// Sample usage:				uart_tx_irq(UART_1,1,1);										// 打开串口1发送完成中断
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_irq(UARTN_enum uartn, uint32 status)
{
	if(status)
		uart_index[uartn]->IER |= UART_IER_TX;													// 使能发送完成中断
	else
		uart_index[uartn]->IER &= ~(UART_IER_TX);												// 关闭发送完成中断

	nvic_init(uart_irq[uartn], 0x00, (FunctionalState)status);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口接收中断设置
// @param		uartn			串口模块号
// @param		status			1：打开中断   0：关闭中断
// @return		void
// Sample usage:				uart_rx_irq(UART_1,1,1);										// 打开串口1接收完成中断
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_irq(UARTN_enum uartn, uint32 status)
{
	if(status)
		uart_index[uartn]->IER |= UART_IER_RX;													// 使能接收完成中断
	else
		uart_index[uartn]->IER &= ~(UART_IER_RX);												// 关闭接收完成中断

	nvic_init(uart_irq[uartn], 0x00, (FunctionalState)status);
}

//--------------------------------------------------------------------------------				// printf 重定向 此部分不允许用户更改
#if defined(__GNUC__)
#define PUTCHAR_PROTOTYPE s32 __io_putchar(s32 ch)
#else
#define PUTCHAR_PROTOTYPE s32 fputc(s32 ch, FILE *f)
#endif

#if defined(__ICCARM__)
PUTCHAR_PROTOTYPE {
	while((UART1->CSR & UART_CSR_TXC) == 0); //The loop is sent until it is finished
	UART1->TDR = (ch & (u16)0x00FF);
	return ch;
}
#else
s32 fputc(s32 ch, FILE* f)
{
	while((UART1->CSR & UART_CSR_TXC) == 0); //The loop is sent until it is finished
	UART1->TDR = (ch & (u16)0x00FF);
	return ch;
}

#endif
//--------------------------------------------------------------------------------			// printf 重定向 此部分不允许用户更改
