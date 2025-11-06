
/**-----------------------------------------------------------------------------
 *        (C) Copyright 2025, PSYM. All Rights Reserved
 * ------------------------------------------------------------------------------
 *  File name   : Debug_Log.c
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

/* ------------------------------- 包含头文件 -------------------------------- */
#include "Debug_Log.h"

#if DEBUG_LOG_TO_NONE == 0
#if DEBUG_LOG_TO_USB_CDC
#include "usbd_cdc_if.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
#elif (DEBUG_LOG_TO_USART1 || DEBUG_LOG_TO_USART2 || DEBUG_LOG_TO_USART3)
#include "usart.h"
#endif

/* ------------------------------ 私有宏定义 --------------------------------- */
/* None. */

/* ----------------------------- 私有类型定义 -------------------------------- */
/* None. */

/* ------------------------------- 扩展变量 ---------------------------------- */
/* None. */

/* ------------------------------- 私有变量 ---------------------------------- */
/* None. */

/* ------------------------------ 私有函数原型 -------------------------------- */
/* None. */

/* --------------------------------- 函数体 ---------------------------------- */

#if defined(__CC_ARM) || defined(__GNUC__)

/**
 * Keil ARMCC 使用 fputc 重定向单字符输出
 */
int fputc(int ch, FILE *f)
{
#if DEBUG_LOG_TO_USB_CDC
    uint32_t timeout = 0;

    while (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
    {
        if (++timeout > 100000) return -1;
    }

    timeout = 0;
    while (CDC_Transmit_FS((uint8_t *)ch, 1) == USBD_BUSY)
    {
        if (++timeout > 100000) return -1;
    }
    return ch;

#elif defined(DEBUG_LOG_TO_USART1)
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;

#elif defined(DEBUG_LOG_TO_USART2)
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;

#elif defined(DEBUG_LOG_TO_USART3)
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;

#else
    return ch;
#endif
}

#elif defined(__ICCARM__)

/**
 * IAR 使用 __write 重定向
 */
int __write(int handle, const unsigned char *buf, unsigned int size)
{
#ifdef DEBUG_LOG_TO_USB_CDC
    uint32_t timeout = 0;

    while (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
    {
        if (++timeout > 100000) return -1;
    }

    timeout = 0;
    while (CDC_Transmit_FS((uint8_t *)buf, size) == USBD_BUSY)
    {
        if (++timeout > 100000) return -1;
    }
    return size;

#elif defined(DEBUG_LOG_TO_USART1)
    HAL_UART_Transmit(&huart1, (uint8_t *)buf, size, HAL_MAX_DELAY);
    return size;

#elif defined(DEBUG_LOG_TO_USART2)
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, size, HAL_MAX_DELAY);
    return size;

#elif defined(DEBUG_LOG_TO_USART3)
    HAL_UART_Transmit(&huart3, (uint8_t *)buf, size, HAL_MAX_DELAY);
    return size;

#else
    return size;
#endif
}

#else
#error "Unsupported compiler"
#endif
#endif

void LOG_TEST(void)
{
    LOG_INFO("=================================");
    LOG_INFO("   🧪 Debug Log System Test");
    LOG_INFO("=================================");
    LOG_INFO(" Log system is running!");
    LOG_INFO("🔧 MCU: STM32 %s", "F103");

    LOG_DEBUG("This is a DEBUG message");
    LOG_INFO("This is an INFO message");
    LOG_WARN("This is a WARNING message");
    LOG_ERROR("This is an ERROR message");

    int a     = 123;
    float f   = 3.1415926f;
    char *str = "Hello World";

    LOG_INFO("🔢 Integer: %d", a);
    LOG_INFO("📊 Float: %.6f", (double)f);
    LOG_INFO("🔤 String: %s", str);

    LOG_INFO("📝 Long string test: %s",
             "This is a longer message to test buffer handling and line wrapping.");

    LOG_INFO("=================================");
    LOG_INFO("         Test Complete!");
    LOG_INFO("=================================");
}

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
