/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				SEEKFREE_ASSERT.c
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.32.4 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/

#include "SEEKFREE_ASSERT.h"

#if ZF_ASSERT																		// �� common.h �ж�������

#if (defined(__CC_ARM)) || (defined(__ARMCC_VERSION)) || (defined(__ICCARM__))
void __aeabi_assert(const char *failedExpr, const char *file, int line)
{
    printf("ASSERT ERROR \" %s \": file \"%s\" Line \"%d\" \n", failedExpr, file, line);
    for (;;)
    {
        __BKPT(0);
    }
}
#elif (defined(__GNUC__))
#if defined(__REDLIB__)
void __assertion_failed(char *failedExpr)
{
    printf("ASSERT ERROR \" %s \n", failedExpr);
    for (;;)
    {
        __BKPT(0);
    }
}
#else
void __assert_func(const char *file, int line, const char *func, const char *failedExpr)
{
    printf("ASSERT ERROR \" %s \": file \"%s\" Line \"%d\" function name \"%s\" \n", failedExpr, file, line, func);
    for (;;)
    {
        __BKPT(0);
    }
}
#endif // defined(__REDLIB__)
#endif // (defined(__CC_ARM) || (defined(__ICCARM__)) || (defined(__ARMCC_VERSION))

#endif // #if ZF_ASSERT
