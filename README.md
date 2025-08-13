# Debug_Log

轻量级嵌入式日志库，支持将 `printf` 等标准输出重定向到 **USB CDC** 或 **USART (1/2/3)**。
兼容 **GCC / ARMCC / IAR**，零依赖、易移植，适用于 STM32 等 MCU 平台。

![1755072473051.png](https://fastly.jsdelivr.net/gh/psympsym/PicBed@utoolsTuC/2025-08/1755072473051_1755073058514.png)

## ✨ 特性

-   ✅ 一键重定向 `printf` 到 USB CDC 或 USART
-   ✅ 支持多编译器：GCC（`_write`）、ARMCC（`fputc`）、IAR（`__write`）
-   ✅ 非阻塞超时处理（防止 USB CDC 忙等）
-   ✅ 简洁宏接口：`LOG_DEBUG/INFO/WARN/ERROR`
-   ✅ 纯 C 实现，低资源占用，可直接嵌入工程
-   ✅ 提供自检函数 `LOG_TEST()` 方便快速验证

## 📂 目录结构

```text
Debug_Log/
│ ── debug_log.h
│ ── Debug_Log.c
└─── README.md
```

## 🔧 使用方法

1. **拷贝源码**

    - 将 `debug_log.h` 与 `Debug_Log.c` 加入你的工程
    - 确保包含路径中有 `debug_log.h`

2. **选择输出通道（在编译选项或代码中定义其一）**

    ```c
    // 任选其一：
    #define DEBUG_LOG_TO_USB_CDC
    // #define DEBUG_LOG_TO_USART1
    // #define DEBUG_LOG_TO_USART2
    // #define DEBUG_LOG_TO_USART3

    ```

若使用 USB CDC，需要工程已有 `usbd_cdc_if.c/h`，并暴露 `hUsbDeviceFS`

若使用 USART，需要已有 `usart.h` 与对应 `huartX` 句柄

````c
#include "debug_log.h"

int main(void) {
    // ... 硬件与外设初始化
    LOG_INFO("System started.");
    LOG_DEBUG("Value=%d", 123);
    LOG_WARN("Battery low!");
    LOG_ERROR("Sensor not found.");
    LOG_TEST();  // 自检输出
    while (1) { /* ... */ }
}```

````

## 🛠️ 编译器适配

-   **GCC**：实现 `_write(int file, char *ptr, int len)`
-   **ARMCC**：实现 `fputc(int ch, FILE *f)`
-   **IAR**：实现 `__write(int handle, const unsigned char *buf, unsigned int size)`

## ⏱️ 超时与阻塞

-   USB CDC 发送前会等待设备进入 `USBD_STATE_CONFIGURED`
-   发送过程中若 `USBD_BUSY` 会重试并在超时后返回，避免长时间阻塞

## ⚠️ 注意事项

-   若使用浮点 `printf`，请在链接选项中开启相应支持（不同工具链选项略有差异）
-   USB CDC 端口需在主机侧打开后才能稳定收发（例如串口终端）
-   在中断中打印可能导致阻塞，不建议在高优先级中断里大量输出

## ✅ 兼容性

-   已在 STM32（如 F4 系列）+ HAL 驱动上验证
-   其他 MCU 只需替换发送接口为对应驱动即可
