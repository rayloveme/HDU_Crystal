/*
 * All rights reserved.
 * @file       		menu.h
 * @brief               菜单头文件
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-01-15
 * @note
*/

#ifndef _menu_h
#define _menu_h

#include "headfile.h"

#define KEY1            gpio_get(G2)
#define KEY2            gpio_get(G3)
#define KEY_LEFT        gpio_get(G5)
#define KEY_ENTER       gpio_get(G8)
#define KEY_UP          gpio_get(G6)
#define KEY_RIGHT       gpio_get(G7)
#define KEY_DOWN        gpio_get(G4)

#define MENU_NUMBER 23
#define PAGE_NUMBER 3

typedef struct sMenu{

    struct sMenu* up;
    struct sMenu* down;
//    struct sMenu* left;
//    struct sMenu* right;

    char* name;
    uint32* value;
}Menu,* PMenu;

extern PMenu menu_pointer;
extern Menu PID_menu[MENU_NUMBER];
extern uint32 menu_flag;

void Menu_Item_Init(PMenu destination,PMenu Up,PMenu Down,char* Name,uint32* p);
void Menu_Init(void);

void Key_Init(void);
void Key_Operation(void);

void Show_Control(void);



#endif