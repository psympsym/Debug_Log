/**-----------------------------------------------------------------------------
 *        (C) Copyright 2025, PSYM. All Rights Reserved
 * ------------------------------------------------------------------------------
 *  File name   : Debug_Log.h
 *  Description :
 *  Author      : PSYM
 * ------------------------------------------------------------------------------
 *  Update note:
 *  -----------   -----------   -------------------------------------------------
 *     Date         Author                              Note
 *  -----------   -----------   -------------------------------------------------
 *  2025-08-11,     PSYM
 *
 */

#ifndef __DEBUG_LOG_H__
#define __DEBUG_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

    /* --------------------------------- 包含头文件 --------------------------------- */
#include <stdio.h>

/* ----------------------------------- 宏定义 ----------------------------------- */
// 选择日志输出接口
// #define DEBUG_LOG_TO_USB_CDC
// #define DEBUG_LOG_TO_USART1
// #define DEBUG_LOG_TO_USART2
// #define DEBUG_LOG_TO_USART3
#define DEBUG_LOG_TO_NONE

    // 日志级别宏定义
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\r\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf("[INFO ] " fmt "\r\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) printf("[WARN ] " fmt "\r\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf("[ERROR] " fmt "\r\n", ##__VA_ARGS__)

    /* ---------------------------------- 类型定义 ---------------------------------- */
    /* None. */

    /* ---------------------------------- 扩展变量 ---------------------------------- */
    /* None. */

    /* ---------------------------------- 函数声明 ---------------------------------- */
    void LOG_TEST(void);

#ifdef __cplusplus
}
#endif

#endif /* debug_log_H */

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
