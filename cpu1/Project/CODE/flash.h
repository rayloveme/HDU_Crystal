/*
 * All rights reserved.
 * @file       		flash.h
 * @brief      		flash
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-15
 * @note
*/

#ifndef _flash_h
#define _flash_h

#include "headfile.h"



#define SECTION_INDEX		FLASH_SECTION_127// 最后一个扇区
#define PAGE_INDEX		FLASH_PAGE_3// 最后一个页
#define DATA_SIZE		256// 32bit数据存储 缓冲就是1024/4大小





extern uint32 flash_flag;
void Flash_Write(void);
void Flash_Read(void);



#endif