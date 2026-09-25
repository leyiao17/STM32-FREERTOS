# Phase 1｜C + STM32 + Cortex-M 基础重构

> **Phase 1 目标：**
> 从“会使用 CubeMX / HAL、能让外设跑起来”，提升到：
>
> - 能解释 C 代码为什么这样运行
> - 能理解变量、指针、内存与 MCU 地址空间
> - 能理解程序从源码到 ELF 再到 MCU 执行的过程
> - 能解释 Cortex-M 启动、中断、异常与基本执行模型
> - 能理解 STM32 常见外设背后的硬件机制
> - 能使用示波器、逻辑分析仪、Debugger 验证自己的判断
> - 出现问题时能够从软件、寄存器、波形和硬件现象逐层定位
>
> **核心原则：**
>
> ```
> 会解释 + 会写 + 会测量/验证 + 会 Debug = 真正掌握
> ```

------

# P1-00｜建立 MCU 底层思维模型

## P1-00.1 CPU、内存、外设分别是什么

## P1-00.2 地址、数据、类型之间的关系

## P1-00.3 CPU 执行一条 C 语句时发生什么

## P1-00.4 寄存器是什么

## P1-00.5 Memory-Mapped I/O

## P1-00.6 HAL / LL / CMSIS / 寄存器之间的关系

## P1-00.7 Datasheet / Reference Manual / Programming Manual 分别查什么

### 本章目标

建立：

```text
C代码
  ↓
变量 / 指针 / 地址
  ↓
CPU Load / Store
  ↓
Memory-Mapped Register
  ↓
STM32外设
  ↓
真实硬件行为
```

------

# P1-01｜C：指针、数组与内存

## P1-01.1 变量、地址、指针

## P1-01.2 `&` 和 `*`

## P1-01.3 指针类型

## P1-01.4 指针运算

## P1-01.5 数组的内存布局

## P1-01.6 数组名与指针的关系

## P1-01.7 `a` / `&a` / `&a[0]`

## P1-01.8 指针数组

## P1-01.9 数组指针

## P1-01.10 多维数组

## P1-01.11 二级指针

## P1-01.12 `void *`

## P1-01.13 `NULL` / 野指针 / 悬空指针

## P1-01.14 指针越界与常见 Undefined Behavior

### 实验

- LAB-C01：地址与指针步长
- LAB-C02：数组与指针
- LAB-C03：数组指针 vs 指针数组
- LAB-C04：二级指针修改指针
- LAB-C05：多维数组内存布局

------

# P1-02｜C：函数、函数指针与回调

## P1-02.1 函数在程序中是什么

## P1-02.2 函数地址

## P1-02.3 函数指针语法

## P1-02.4 使用 `typedef` 简化函数指针

## P1-02.5 Callback 回调机制

## P1-02.6 函数指针表

## P1-02.7 Driver 接口设计

## P1-02.8 状态机 + 函数指针

### 实验

- LAB-C06：基本函数指针
- LAB-C07：Callback
- LAB-C08：Driver Operations Table
- LAB-C09：函数指针状态机

------

# P1-03｜C：作用域、生命周期与类型限定

## P1-03.1 局部变量 / 全局变量

## P1-03.2 生命周期 vs 作用域

## P1-03.3 `static` 局部变量

## P1-03.4 `static` 全局变量

## P1-03.5 `static` 函数

## P1-03.6 `const`

## P1-03.7 `const` 与指针

## P1-03.8 `volatile`

## P1-03.9 `volatile` 与硬件寄存器

## P1-03.10 `volatile` 与 ISR 共享变量

## P1-03.11 为什么 `volatile` 不保证原子性

## P1-03.12 为什么 `volatile` 不等于线程安全

### 重点辨析

```c
const uint8_t *p;

uint8_t * const p;

const uint8_t * const p;

volatile uint32_t flag;
```

------

# P1-04｜C：数据组织与底层表示

## P1-04.1 `struct`

## P1-04.2 Struct 内存布局

## P1-04.3 内存对齐

## P1-04.4 Padding

## P1-04.5 `union`

## P1-04.6 `enum`

## P1-04.7 `sizeof`

## P1-04.8 大端 / 小端

## P1-04.9 位运算

## P1-04.10 Bit Mask

## P1-04.11 宏

## P1-04.12 宏的常见陷阱

### 实验

- LAB-C10：结构体内存布局
- LAB-C11：成员 Offset
- LAB-C12：内存对齐与 Padding
- LAB-C13：大小端检测
- LAB-C14：位操作与寄存器模拟
- LAB-C15：CAN / UART 数据拆包

------

# P1-05｜C：Stack / Heap / 内存问题

## P1-05.1 Stack 是什么

## P1-05.2 Heap 是什么

## P1-05.3 局部变量放在哪里

## P1-05.4 函数调用与 Stack Frame 基本概念

## P1-05.5 `malloc()` / `free()` 基本机制

## P1-05.6 Memory Leak

## P1-05.7 Use After Free

## P1-05.8 Stack Overflow

## P1-05.9 Buffer Overflow

## P1-05.10 Undefined Behavior

## P1-05.11 Reentrant 基本概念

## P1-05.12 MCU 为什么通常谨慎使用动态内存

------

# P1-06｜从 C 到 ELF：预处理、编译、汇编、链接

## P1-06.1 `.c` 到可执行程序经历了什么

## P1-06.2 Preprocessor

## P1-06.3 `gcc -E`

## P1-06.4 Compiler

## P1-06.5 `gcc -S`

## P1-06.6 Assembly

## P1-06.7 `gcc -c`

## P1-06.8 Object File `.o`

## P1-06.9 Symbol

## P1-06.10 Linker

## P1-06.11 ELF

## P1-06.12 Map File

## P1-06.13 `.text`

## P1-06.14 `.rodata`

## P1-06.15 `.data`

## P1-06.16 `.bss`

## P1-06.17 Stack / Heap 在 MCU 中的位置

## P1-06.18 Linker Script 入门

### 编译链实验

```text
main.c
  ↓
gcc -E
  ↓
main.i
  ↓
gcc -S
  ↓
main.s
  ↓
gcc -c
  ↓
main.o
  ↓
Linker
  ↓
ELF
```

------

# P1-07｜Cortex-M：CPU、寄存器与程序执行

## P1-07.1 Cortex-M4 是什么

## P1-07.2 CPU Core vs STM32 MCU

## P1-07.3 R0-R12 基本概念

## P1-07.4 SP

## P1-07.5 LR

## P1-07.6 PC

## P1-07.7 xPSR

## P1-07.8 MSP

## P1-07.9 PSP

## P1-07.10 Thread Mode

## P1-07.11 Handler Mode

## P1-07.12 简单 ARM 汇编阅读

## P1-07.13 C 代码与汇编之间的联系

------

# P1-08｜STM32：从 Reset 到 main()

## P1-08.1 MCU Reset 后发生什么

## P1-08.2 Vector Table

## P1-08.3 Vector Table 第一项

## P1-08.4 Vector Table 第二项

## P1-08.5 Reset_Handler

## P1-08.6 MSP 初始化

## P1-08.7 `.data` 搬运

## P1-08.8 `.bss` 清零

## P1-08.9 `SystemInit()`

## P1-08.10 C Runtime

## P1-08.11 `main()`

## P1-08.12 阅读 `startup_xxx.s`

### 启动链

```text
Reset
  ↓
Vector Table
  ↓
MSP / Reset_Handler
  ↓
.data 初始化
.bss 清零
  ↓
SystemInit()
  ↓
C Runtime
  ↓
main()
```

------

# P1-09｜Cortex-M：Exception / Interrupt / NVIC

## P1-09.1 Exception 是什么

## P1-09.2 Interrupt 是什么

## P1-09.3 IRQ

## P1-09.4 NVIC

## P1-09.5 Interrupt Enable

## P1-09.6 Pending

## P1-09.7 Active

## P1-09.8 Priority

## P1-09.9 Preemption

## P1-09.10 Priority Group

## P1-09.11 中断嵌套

## P1-09.12 中断进入 / 退出基本过程

## P1-09.13 ISR 为什么应该尽量短

## P1-09.14 ISR 共享数据

## P1-09.15 SysTick

### 实验

- 两个 Timer Interrupt
- 设置不同优先级
- GPIO 翻转
- 使用逻辑分析仪观察中断抢占

------

# P1-10｜STM32：Timer 体系

## P1-10.1 MCU Clock 基本关系

## P1-10.2 Timer Clock

## P1-10.3 Counter

## P1-10.4 PSC

## P1-10.5 ARR

## P1-10.6 Update Event

## P1-10.7 Timer Interrupt

## P1-10.8 PWM

## P1-10.9 CCR

## P1-10.10 Duty Cycle

## P1-10.11 Input Capture

## P1-10.12 Encoder Mode

## P1-10.13 Overflow 处理

## P1-10.14 Encoder 速度计算

### 实验

- 1 kHz Timer
- 示波器验证周期
- PWM 输出
- 修改 Duty Cycle
- Input Capture
- Encoder Mode
- Encoder 速度计算

------

# P1-11｜STM32：DMA + ADC

## P1-11.1 CPU Polling 的问题

## P1-11.2 Interrupt 方式

## P1-11.3 DMA 是什么

## P1-11.4 Peripheral → Memory

## P1-11.5 Memory → Peripheral

## P1-11.6 DMA Request

## P1-11.7 Transfer Complete

## P1-11.8 Half Transfer

## P1-11.9 Circular Mode

## P1-11.10 ADC 基本工作过程

## P1-11.11 ADC + DMA

## P1-11.12 Polling / IRQ / DMA 对比

### 核心问题

> DMA 为什么可以减少 CPU 参与，但并不意味着完全不需要 CPU？

------

# P1-12｜UART → DMA → IDLE → Ring Buffer → Parser

## P1-12.1 UART Frame

## P1-12.2 Baud Rate

## P1-12.3 TX / RX

## P1-12.4 Polling RX

## P1-12.5 Interrupt RX

## P1-12.6 DMA RX

## P1-12.7 IDLE Line

## P1-12.8 不定长数据接收问题

## P1-12.9 Ring Buffer 原理

## P1-12.10 Head / Tail

## P1-12.11 Overflow

## P1-12.12 自己实现 Ring Buffer

## P1-12.13 Frame 设计

## P1-12.14 Parser

## P1-12.15 半包

## P1-12.16 连包

## P1-12.17 错包

## P1-12.18 CRC 基础

## P1-12.19 DMA + IDLE + Ring Buffer + Parser 整合

### 最终数据链

```text
UART
  ↓
DMA
  ↓
IDLE
  ↓
RX Buffer
  ↓
Ring Buffer
  ↓
Frame Parser
  ↓
Application
```

------

# P1-13｜STM32：SPI

## P1-13.1 SPI 总线模型

## P1-13.2 SCK

## P1-13.3 MOSI / MISO

## P1-13.4 CS

## P1-13.5 Full Duplex

## P1-13.6 CPOL

## P1-13.7 CPHA

## P1-13.8 Mode 0 / 1 / 2 / 3

## P1-13.9 寄存器读写协议

## P1-13.10 逻辑分析仪分析 SPI

### 实验目标

做到：

> 给出 SPI 波形，可以判断数据、时钟极性和采样边沿。

------

# P1-14｜STM32：I2C

## P1-14.1 Open Drain

## P1-14.2 Pull-up

## P1-14.3 START

## P1-14.4 STOP

## P1-14.5 Address

## P1-14.6 R/W

## P1-14.7 ACK

## P1-14.8 NACK

## P1-14.9 Register Read

## P1-14.10 Repeated START

## P1-14.11 逻辑分析仪分析 I2C

## P1-14.12 SDA / SCL 被拉低

## P1-14.13 Bus Lock 基本恢复思路

------

# P1-15｜STM32：CAN

## P1-15.1 CAN 为什么适合分布式控制

## P1-15.2 Differential Signal 基本概念

## P1-15.3 Dominant / Recessive

## P1-15.4 CAN Data Frame

## P1-15.5 Identifier

## P1-15.6 DLC / Data

## P1-15.7 CRC

## P1-15.8 ACK

## P1-15.9 Arbitration

## P1-15.10 为什么 ID 越小仲裁优先级越高

## P1-15.11 Filter

## P1-15.12 Error Detection

## P1-15.13 TEC / REC 基本概念

## P1-15.14 Error Active

## P1-15.15 Error Passive

## P1-15.16 Bus-Off

## P1-15.17 STM32 CAN 收发

## P1-15.18 RoboMaster Motor Feedback

## P1-15.19 Motor CAN Parser

### 最终目标

```text
CAN物理层基本理解
        ↓
CAN Frame
        ↓
Arbitration
        ↓
Filter
        ↓
Error Handling
        ↓
STM32 CAN Driver
        ↓
Motor Feedback
        ↓
Motor Parser
```

------

# P1-16｜Debug：DWT + HardFault

## P1-16.1 Debugger 基本模型

## P1-16.2 Breakpoint

## P1-16.3 Watch

## P1-16.4 Memory

## P1-16.5 Register

## P1-16.6 Call Stack

## P1-16.7 DWT Cycle Counter

## P1-16.8 函数 Execution Time

## P1-16.9 HardFault 是什么

## P1-16.10 主动制造非法访问

## P1-16.11 Fault 现场

## P1-16.12 PC / LR / SP

## P1-16.13 Fault Status Registers 基本使用

## P1-16.14 从 Fault 定位代码

## P1-16.15 HardFault Debug Checklist

### 实验

- 使用 DWT 测量函数执行时间
- 对比不同代码实现的 Cycle
- 主动制造非法内存访问
- 进入 HardFault
- 查看寄存器
- 找到 Fault 地址
- 定位出错代码
- 写 HardFault Debug Checklist

------

# P1-17｜补齐 MCU 基础接口

> 本章属于 Phase 1 补充内容，不抢占前面主线学习时间。

## P1-17.1 GPIO 寄存器模型

## P1-17.2 RCC / Clock 基本概念

## P1-17.3 Watchdog

## P1-17.4 Flash 基本概念

## P1-17.5 Boot Mode

## P1-17.6 Bootloader / IAP 基本思想

------

# P1-18｜Phase 1 综合验收

## P1-18.1 C 语言验收

能够解释：

- Pointer
- Array
- Pointer Array
- Array Pointer
- Double Pointer
- Function Pointer
- `static`
- `const`
- `volatile`
- Struct Alignment
- Endianness
- Stack / Heap
- Undefined Behavior

------

## P1-18.2 Build / Link 验收

能够解释：

```text
.c
 ↓
Preprocess
 ↓
Compile
 ↓
Assembly
 ↓
.o
 ↓
Link
 ↓
ELF
```

能够解释：

- `.text`
- `.rodata`
- `.data`
- `.bss`
- Stack
- Heap
- Map File
- ELF

------

## P1-18.3 Cortex-M 验收

能够解释：

- Vector Table
- Reset_Handler
- MSP
- PSP
- PC
- LR
- Thread Mode
- Handler Mode
- Exception
- NVIC
- Priority
- Preemption
- SysTick
- HardFault

------

## P1-18.4 STM32 外设验收

脱离教程独立完成：

- Timer
- PWM
- Encoder
- UART
- UART DMA
- UART DMA + IDLE
- Ring Buffer
- Parser
- ADC + DMA
- SPI
- I2C
- CAN

------

## P1-18.5 Debug 验收

能够使用：

- Breakpoint
- Watch
- Memory View
- Register View
- Call Stack
- Map File
- Logic Analyzer
- Oscilloscope
- DWT
- HardFault 信息

完成基本问题定位。

------

# Phase 1 最终成果

完成：

-  15～20 个可运行实验
-  每个实验都有 README
-  至少 5 份真实示波器 / 逻辑分析仪波形证据
-  `notes/c-language-memory.md`
-  `notes/build-link-process.md`
-  `notes/stm32-startup.md`
-  `notes/stm32-knowledge-map.md`
-  `notes/can-notes.md`
-  `notes/hardfault-debug-checklist.md`
-  `notes/uart-parser-design.md`
-  30 道 C / STM32 面试题口头回答记录
-  完整 Git Commit 历史
-  Git Tag：`foundation-v1.0`

------

# Phase 1 总学习路径

```text
P1-00  MCU底层思维模型
   ↓
P1-01  指针 / 数组 / 内存
   ↓
P1-02  函数指针 / Callback
   ↓
P1-03  static / const / volatile
   ↓
P1-04  struct / 对齐 / 大小端 / 位操作
   ↓
P1-05  Stack / Heap / 内存问题
   ↓
P1-06  编译 / 汇编 / 链接 / ELF
   ↓
P1-07  Cortex-M CPU模型
   ↓
P1-08  Reset → main()
   ↓
P1-09  Exception / Interrupt / NVIC
   ↓
P1-10  Timer / PWM / Encoder
   ↓
P1-11  DMA / ADC
   ↓
P1-12  UART / DMA / IDLE / Ring Buffer / Parser
   ↓
P1-13  SPI
   ↓
P1-14  I2C
   ↓
P1-15  CAN
   ↓
P1-16  DWT / HardFault / Debug
   ↓
P1-17  Watchdog / Flash / Bootloader补充
   ↓
P1-18  Phase 1综合验收
```

------

# 每个知识点统一学习模板

后续每个 `P1-XX` 都按照以下方式展开：

1. **当前水平测试**
2. **核心概念**
3. **底层原理**
4. **代码分析**
5. **内存 / CPU / 硬件执行过程**
6. **最小实验**
7. **STM32 实际应用**
8. **常见错误与 Debug**
9. **面试问题**
10. **本节验收题**
11. **实验 / Git / README 证据**
12. **与后续知识的连接**

------

# Phase 1 掌握标准

一个知识点只有同时满足下面四项，才标记为完成：

```text
I can explain.
      +
I can write.
      +
I can measure / test.
      +
I can debug.
      ↓
    MASTERED
```