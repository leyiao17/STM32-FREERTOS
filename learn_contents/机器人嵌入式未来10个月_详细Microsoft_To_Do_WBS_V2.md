# 机器人嵌入式未来10个月——详细阶段性 Microsoft To Do / WBS

**版本：V2.0（详细执行版）**  
**执行周期：2026-09-22 ～ 2027-07**  
**定位：机器人嵌入式 / MCU-RTOS实时控制为主线，Linux/ROS2系统能力与硬件/电源能力为两翼**  
**使用方式：本文件是总Roadmap；Microsoft To Do里只把“当前阶段 + 下一个阶段”的任务激活，避免任务爆炸。**

---

# 0. 这份 To Do 怎么用

## 0.1 不要把“学习”当完成标准

以后不要建立这种任务：

- [ ] 学FreeRTOS
- [ ] 学STM32
- [ ] 学ROS2

这类任务没有结束条件。

应该写成：

- [ ] 用GPIO+逻辑分析仪观测两个不同优先级任务的抢占行为，并保存波形
- [ ] 独立实现UART DMA + IDLE + Ring Buffer接收链路，并写README
- [ ] 自己写一个ROS2 Publisher/Subscriber C++ Package并完成QoS实验

原则：

> **任何任务都尽量变成“可以验收的动作 + 可以留下的证据”。**

---

## 0.2 Microsoft To Do 推荐列表

建议只建立以下列表：

### `🔥 Current Sprint`
只放未来1～2周真正要做的任务。

### `🗺 Career Roadmap`
放本文件中的Phase级里程碑，不放所有细节。

### `🤖 Robot Project`
机器人旗舰项目任务。

### `⚡ Supercap`
超级电容项目任务。

### `🐧 Embedded Linux`
Linux/i.MX6ULL任务。

### `💼 Interview & Job`
面试、简历、JD、投递。

### `🐞 Bugs & Follow-up`
暂时未解决Bug、技术债、后续验证。

### `💡 Backlog`
以后想学但当前不能打断主线的内容：
FPGA、Cadence、SLAM深入、双目、Zephyr、Rust、VLA等。

---

## 0.3 任务前缀

为了在Microsoft To Do里快速识别，建议使用：

- `[LEARN]` 理论学习
- `[LAB]` 实验
- `[CODE]` 编码
- `[HW]` 硬件
- `[DOC]` 文档
- `[TEST]` 测试
- `[GIT]` Git/Release
- `[AI]` AI辅助复盘
- `[INT]` 面试
- `[JOB]` 求职

---

# 1. 全程贯穿的固定任务

下面这些不是某一个月做一次，而是未来10个月持续执行。

## 1.1 每周固定循环

- [ ] `[PLAN]` 周一选出本周最重要的3个成果
- [ ] `[GIT]` 本周至少3次有意义Commit
- [ ] `[DOC]` 更新README / Notes / Bug Log
- [ ] `[INT]` 完成1次30～45分钟模拟面试
- [ ] `[INT]` 整理本周不会的10个面试问题
- [ ] `[LAB]` 至少完成1个带真实测量数据的实验
- [ ] `[BUG]` 完整记录至少1个真实Bug：现象→假设→实验→根因→修复→验证
- [ ] `[AI]` 用AI做一次Code Review或知识追问，但最终查官方文档/实验确认
- [ ] `[REVIEW]` 周日完成`weekly-review-YYYY-WXX.md`

---

## 1.2 推荐每周时间比例

如果每周能投入约20小时：

- **12小时（60%）**：项目 / 实验 / Debug
- **4小时（20%）**：基础理论
- **2小时（10%）**：面试 / 数据结构
- **2小时（10%）**：Git / 文档 / 复盘

如果时间变少，比例基本保持，而不是把项目砍掉只看教程。

---

# Phase 0｜2026-09-22 ～ 2026-09-28
# 工程环境、Git和个人研发体系建立

## 阶段目标

从“零散学习”切换到“所有学习有代码、有测试、有记录、有版本”。

---

## P0-1 建立Git工作区

- [ ] `[GIT]` 创建`embedded-learning-notes`
- [ ] `[GIT]` 创建`mcu-foundation-lab`
- [ ] `[GIT]` 创建`robot-embedded-control`
- [ ] `[GIT]` 创建`supercap-controller`
- [ ] `[GIT]` 创建`imx6ull-linux-driver`
- [ ] `[GIT]` 为每个Repo建立`.gitignore`
- [ ] `[GIT]` 为每个Repo建立基础`README.md`
- [ ] `[GIT]` 学会`clone/add/commit/push/pull/branch/merge/log/diff`
- [ ] `[GIT]` 练习建立`feature/test-branch`并Merge
- [ ] `[DOC]` 写一份自己的Commit规范

建议Commit风格：

```text
feat(can): add motor feedback parser
fix(uart): prevent rx ring buffer overflow
test(timer): measure 1kHz loop jitter
docs(freertos): add priority inversion experiment
```

---

## P0-2 建立文档模板

在`embedded-learning-notes/templates`建立：

- [ ] `[DOC]` `experiment-template.md`
- [ ] `[DOC]` `bug-template.md`
- [ ] `[DOC]` `weekly-review-template.md`
- [ ] `[DOC]` `design-note-template.md`
- [ ] `[DOC]` `interview-question-template.md`

实验模板必须包含：

```text
目的
理论
硬件/软件环境
实验步骤
预期结果
实测结果
波形/截图
问题
结论
```

Bug模板必须包含：

```text
现象
复现条件
假设
实验
根因
修复
回归测试
```

---

## P0-3 设备和资料盘点

- [ ] `[DOC]` 整理已有F4/H7开发板型号
- [ ] `[DOC]` 整理Jetson型号、JetPack、Ubuntu版本
- [ ] `[DOC]` 整理MID360S型号、网口供电需求
- [ ] `[DOC]` 整理海康相机型号、接口
- [ ] `[DOC]` 整理i.MX6ULL开发板
- [ ] `[DOC]` 整理实验室可用示波器、逻辑分析仪、电源
- [ ] `[DOC]` 整理RM电机、驱动器、机械件是否可以长期使用
- [ ] `[DOC]` 建`hardware-inventory.md`

---

## P0阶段产出物

必须产出：

```text
embedded-learning-notes/
mcu-foundation-lab/
robot-embedded-control/
supercap-controller/
imx6ull-linux-driver/

hardware-inventory.md
weekly-review-template.md
bug-template.md
experiment-template.md
```

---

## Phase 0退出条件（DoD）

只有满足以下条件才进入Phase 1：

- Git基本命令可以独立使用
- 至少做过一次Branch→Commit→Merge
- 有完整的学习/实验/bug模板
- 已整理已有硬件
- 从此以后项目不再出现`final2.zip`式版本管理

---

# Phase 1｜2026-09下旬 ～ 2026-10
# C语言 + STM32 + Cortex-M基础重构

## 阶段目标

从：

> “会CubeMX、会HAL、外设可以跑”

变成：

> “能够解释代码为什么工作、MCU发生了什么、出问题会定位”。

主Repo：

```text
mcu-foundation-lab
```

---

# Week 1｜C语言 + 编译链接 + STM32启动

## C语言

- [ ] `[LEARN]` 指针、数组、指针数组、数组指针
- [ ] `[LAB]` 写指针/数组地址实验并打印地址变化
- [ ] `[LEARN]` 二级指针
- [ ] `[LAB]` 写动态二维结构/函数修改指针实验
- [ ] `[LEARN]` 函数指针
- [ ] `[CODE]` 用函数指针实现简单Driver回调表
- [ ] `[LEARN]` `const`
- [ ] `[LEARN]` `static`
- [ ] `[LEARN]` `volatile`
- [ ] `[INT]` 回答：volatile能否保证原子性/线程安全吗
- [ ] `[LEARN]` struct/union/enum
- [ ] `[LAB]` 验证结构体内存对齐
- [ ] `[LEARN]` 大小端
- [ ] `[LAB]` 写C程序检测CPU大小端

## 编译链接

- [ ] `[LEARN]` 理解预处理→编译→汇编→链接
- [ ] `[LAB]` 使用`gcc -E/-S/-c`
- [ ] `[LAB]` 查看`.o`和最终ELF
- [ ] `[LEARN]` 理解`.text/.rodata/.data/.bss`
- [ ] `[LAB]` 修改全局变量类型观察Map文件变化

## Cortex-M启动

- [ ] `[LEARN]` 阅读F4 Startup文件
- [ ] `[LEARN]` 理解Vector Table
- [ ] `[LEARN]` 理解Reset_Handler
- [ ] `[LEARN]` 理解MSP基本概念
- [ ] `[LAB]` 找到程序从Reset到main的路径
- [ ] `[DOC]` 画一张`Reset → startup → SystemInit → main`流程图

### Week 1产出

```text
notes/c-language-memory.md
notes/build-link-process.md
notes/stm32-startup.md
labs/c-pointer/
labs/memory-layout/
labs/startup-analysis/
```

---

# Week 2｜NVIC + Timer + PWM + Encoder

## Interrupt / NVIC

- [ ] `[LEARN]` Interrupt和Exception区别
- [ ] `[LEARN]` NVIC Priority
- [ ] `[LEARN]` Preempt Priority
- [ ] `[LAB]` 建立两个Timer中断观察嵌套
- [ ] `[TEST]` GPIO翻转+逻辑分析仪观察抢占顺序
- [ ] `[DOC]` 保存逻辑分析仪截图
- [ ] `[INT]` 回答“中断里为什么不能做太重的事情”

## Timer

- [ ] `[LEARN]` PSC/ARR/Counter计算
- [ ] `[LAB]` 生成1kHz定时中断
- [ ] `[TEST]` 用示波器验证实际频率
- [ ] `[LAB]` PWM输出
- [ ] `[TEST]` 测量PWM Frequency和Duty
- [ ] `[LAB]` Input Capture
- [ ] `[LAB]` Encoder Mode
- [ ] `[CODE]` 完成Encoder速度计算

### Week 2产出

```text
labs/nvic-preemption/
labs/timer-1khz/
labs/pwm/
labs/input-capture/
labs/encoder/
docs/nvic-waveform.png
```

---

# Week 3｜UART + DMA + Ring Buffer + SPI/I2C

## UART

- [ ] `[LEARN]` Polling / Interrupt / DMA区别
- [ ] `[LAB]` UART Interrupt RX
- [ ] `[LAB]` UART DMA RX
- [ ] `[LEARN]` UART IDLE Line
- [ ] `[CODE]` 实现DMA+IDLE不定长接收
- [ ] `[CODE]` 自己实现Ring Buffer
- [ ] `[CODE]` 实现简单Frame Parser
- [ ] `[TEST]` 人为发错误包/半包测试Parser
- [ ] `[BUG]` 记录至少一个真实串口Bug

## SPI

- [ ] `[LEARN]` CPOL/CPHA
- [ ] `[LEARN]` Full Duplex
- [ ] `[LAB]` SPI读取一个实际设备或Loopback
- [ ] `[TEST]` 逻辑分析仪验证时序

## I2C

- [ ] `[LEARN]` START/STOP/ACK/NACK
- [ ] `[LAB]` I2C读取实际传感器
- [ ] `[TEST]` 逻辑分析仪验证Address/Data/ACK
- [ ] `[INT]` 回答I2C总线拉低/死锁基本处理思路

### Week 3产出

```text
drivers/ring_buffer.c
labs/uart-dma-idle/
labs/spi/
labs/i2c/
docs/uart-parser-design.md
docs/i2c-spi-waveforms/
```

---

# Week 4｜DMA + CAN + DWT + HardFault + 综合复盘

## DMA

- [ ] `[LEARN]` DMA为什么减少CPU参与
- [ ] `[LAB]` ADC+DMA
- [ ] `[LAB]` UART TX DMA
- [ ] `[TEST]` 对比Polling和DMA CPU行为
- [ ] `[INT]` 解释DMA完成中断

## CAN

- [ ] `[LEARN]` CAN Data Frame
- [ ] `[LEARN]` Dominant/Recessive
- [ ] `[LEARN]` Arbitration
- [ ] `[LEARN]` ACK
- [ ] `[LEARN]` Error Active/Error Passive/Bus-Off
- [ ] `[LAB]` CAN收发
- [ ] `[LAB]` Filter配置
- [ ] `[LAB]` 如果有RM电机：读取Motor Feedback
- [ ] `[CODE]` 写Motor CAN Parser

## DWT

- [ ] `[LAB]` 使用DWT测一段函数Execution Time
- [ ] `[TEST]` 对比不同实现耗时

## HardFault

- [ ] `[LEARN]` HardFault基本原因
- [ ] `[LAB]` 人为制造非法访问（在安全开发板上）
- [ ] `[DEBUG]` 用Debugger检查Fault现场
- [ ] `[DOC]` 写`hardfault-debug-checklist.md`

---

## Phase 1必须产出

- [ ] 15～20个可运行实验
- [ ] 每个实验有README
- [ ] 至少5张真实逻辑分析仪/示波器截图
- [ ] `stm32-knowledge-map.md`
- [ ] `can-notes.md`
- [ ] `hardfault-debug-checklist.md`
- [ ] `uart-parser-design.md`
- [ ] 30道C/STM32面试题口头回答记录
- [ ] Git Tag：`foundation-v1.0`

---

## Phase 1退出条件

能够不看教程完成：

- UART DMA+IDLE+Ring Buffer
- Timer/PWM
- Encoder
- SPI/I2C基础设备
- CAN收发

并且能口头解释：

- volatile
- .data/.bss
- 中断优先级
- DMA
- CAN仲裁
- HardFault基本排查

---

# Phase 2｜2026-11

# FreeRTOS深入 + 自己搭机器人下位机框架

主Repo：

```text
robot-embedded-control
```

---

# Week 1｜Task与Scheduler

- [ ] `[LEARN]` Running/Ready/Blocked/Suspended
- [ ] `[LAB]` 创建不同Priority任务
- [ ] `[LAB]` GPIO+逻辑分析仪观察抢占
- [ ] `[LEARN]` `vTaskDelay`与`vTaskDelayUntil`
- [ ] `[LAB]` 比较周期任务漂移
- [ ] `[LEARN]` SysTick作用
- [ ] `[LEARN]` PendSV作用
- [ ] `[LEARN]` Context Switch概念
- [ ] `[DOC]` 画Task状态图
- [ ] `[INT]` 回答“Blocked为什么不占CPU”

---

# Week 2｜Queue / Semaphore / Mutex / Notification

- [ ] `[LAB]` Queue：Producer→Consumer
- [ ] `[LAB]` Binary Semaphore
- [ ] `[LAB]` Counting Semaphore
- [ ] `[LAB]` Mutex保护共享资源
- [ ] `[LAB]` Task Notification
- [ ] `[TEST]` 比较Queue与Notification适用场景
- [ ] `[INT]` 回答Mutex和Semaphore区别
- [ ] `[INT]` 回答为什么ISR不能随便用普通API

---

# Week 3｜ISR + Priority Inversion + Stack/Heap

- [ ] `[LEARN]` FreeRTOS中断优先级限制
- [ ] `[LAB]` ISR→Task Notification
- [ ] `[LAB]` `portYIELD_FROM_ISR`
- [ ] `[LAB]` 主动构造Priority Inversion
- [ ] `[LAB]` 观察Mutex Priority Inheritance
- [ ] `[LEARN]` Task Stack
- [ ] `[LAB]` 使用High Water Mark
- [ ] `[LAB]` 人为制造Stack过小
- [ ] `[LEARN]` heap_4基本行为
- [ ] `[DOC]` 写`freertos-debug-checklist.md`

---

# Week 4｜机器人下位机Framework V0.1

设计目录：

```text
BSP
Device
Service
Control
Application
```

任务：

- [ ] `[DESIGN]` 划分BSP/Device/Service/Control/Application职责
- [ ] `[CODE]` CAN BSP
- [ ] `[CODE]` Motor Device层
- [ ] `[CODE]` Motor Service
- [ ] `[CODE]` Communication Service框架
- [ ] `[CODE]` Monitor Service
- [ ] `[CODE]` Fault基本框架
- [ ] `[CODE]` MotorControlTask
- [ ] `[CODE]` CommunicationTask
- [ ] `[CODE]` MonitorTask
- [ ] `[TEST]` 统计Task Stack
- [ ] `[TEST]` 测关键Task周期
- [ ] `[DOC]` 写`architecture.md`
- [ ] `[DOC]` 写`task-design.md`

---

## Phase 2必须产出

```text
robot-embedded-control/
├── firmware/
├── docs/
│   ├── architecture.md
│   ├── task-design.md
│   ├── freertos-debug-checklist.md
│   └── experiment/
```

以及：

- [ ] FreeRTOS 6～8个实验
- [ ] Task调度波形
- [ ] Priority Inversion实验记录
- [ ] Stack High Water Mark截图/数据
- [ ] 第一版机器人下位机框架
- [ ] 30道RTOS面试题
- [ ] Git Release：`v0.1-rtos-framework`

---

## Phase 2退出条件

面试时可以自己画出：

```text
ISR → Notification/Queue → Task → Process → Block
```

并能够回答“为什么这么设计”，而不是只会创建Task。

---

# Phase 3｜2026-12
# 超级电容理解 + KiCad + 硬件设计Review

主Repo：

```text
supercap-controller
```

---

# Week 1｜系统与拓扑理解

- [ ] `[LEARN]` 整体Power Flow
- [ ] `[LEARN]` 双向Buck-Boost各工作状态
- [ ] `[DOC]` 自己画功率流向图
- [ ] `[LEARN]` 电感选型逻辑
- [ ] `[LEARN]` MOSFET关键参数
- [ ] `[LEARN]` Gate Driver原理
- [ ] `[DOC]` 建关键器件Datasheet索引
- [ ] `[INT]` 自己讲10分钟“为什么是四开关Buck-Boost”

---

# Week 2｜采样、PWM、保护

- [ ] `[LEARN]` 电压采样链路
- [ ] `[LEARN]` 电流采样链路
- [ ] `[LEARN]` ADC参考/量程/误差
- [ ] `[LEARN]` PWM与Dead Time
- [ ] `[LEARN]` 过流保护
- [ ] `[LEARN]` 过压保护
- [ ] `[LEARN]` 欠压/反接等异常
- [ ] `[DOC]` 自己画控制框图
- [ ] `[DOC]` 写保护状态表

---

# Week 3｜KiCad重构

- [ ] `[TOOL]` 熟悉KiCad工程结构
- [ ] `[HW]` 重新建立/整理原理图
- [ ] `[HW]` 给关键Net清晰命名
- [ ] `[HW]` 检查Gate Drive回路
- [ ] `[HW]` 检查采样回路
- [ ] `[HW]` 检查大电流路径
- [ ] `[HW]` 检查地划分/回流
- [ ] `[HW]` 建BOM
- [ ] `[GIT]` KiCad工程纳入版本管理

---

# Week 4｜Design Review与Bring-up计划

- [ ] `[DOC]` 写Power Tree
- [ ] `[DOC]` 写关键器件选型表
- [ ] `[DOC]` 写Bring-up Checklist
- [ ] `[DOC]` 写Test Plan
- [ ] `[REVIEW]` 自己做一次完整Design Review
- [ ] `[AI]` 让AI作为Review员提出20个潜在问题
- [ ] `[VERIFY]` 每个AI问题回到Datasheet/原理图确认
- [ ] `[HW]` 确认限流电源、示波器探测方式、安全条件

---

## Phase 3必须产出

- [ ] `power-tree.md`
- [ ] `topology-analysis.md`
- [ ] `control-block-diagram.md`
- [ ] `protection-table.md`
- [ ] `key-components.xlsx/md`
- [ ] KiCad工程
- [ ] BOM
- [ ] `design-review-v1.md`
- [ ] `bring-up-checklist.md`
- [ ] `test-plan.md`
- [ ] Git Tag：`v0.1-design-review`

---

## Phase 3退出条件

你必须能够不看开源README独立回答：

- 为什么这个拓扑
- 电感/MOS/Gate Driver分别干什么
- 电流、电压怎么采
- PWM怎么工作
- 哪些异常必须保护
- 上电顺序怎么安排

---

# Phase 4｜2027-01
# 超级电容Bring-up + C++工程基础

> 高功率电源部分必须低压、限流、分阶段验证，任何阶段不要跳过保护和安全检查。

---

# Week 1｜低压Bring-up

- [ ] `[HW]` 断电测阻检查短路
- [ ] `[HW]` 检查焊接
- [ ] `[HW]` 低压限流上电
- [ ] `[TEST]` 测辅助电源
- [ ] `[TEST]` 验证MCU启动
- [ ] `[TEST]` 验证Debug接口
- [ ] `[TEST]` 验证ADC静态采样
- [ ] `[DOC]` 保存所有关键电压测试值
- [ ] `[BUG]` 建第一版Bring-up Bug Log

---

# Week 2｜PWM / Gate Driver / Open Loop

- [ ] `[TEST]` 空载观察PWM
- [ ] `[TEST]` 测Dead Time
- [ ] `[TEST]` 测Gate Driver输出
- [ ] `[TEST]` 低能量条件下验证开环
- [ ] `[TEST]` 校准Voltage Sampling
- [ ] `[TEST]` 校准Current Sampling
- [ ] `[DOC]` 保存示波器波形
- [ ] `[BUG]` 对异常波形做根因分析

---

# Week 3｜Protection / Closed Loop初步

- [ ] `[CODE]` 实现过流保护
- [ ] `[CODE]` 实现过压保护
- [ ] `[CODE]` 实现欠压保护
- [ ] `[TEST]` 在安全条件验证保护触发
- [ ] `[LEARN]` 理解控制环基本逻辑
- [ ] `[CODE]` Closed Loop初版
- [ ] `[TEST]` 小功率验证
- [ ] `[DOC]` 写第一版测试结果

---

# Week 4｜C++基础并行学习

- [ ] `[LEARN]` Class/Constructor/Destructor
- [ ] `[LEARN]` RAII
- [ ] `[LEARN]` vector/map/unordered_map
- [ ] `[LEARN]` smart pointer
- [ ] `[LEARN]` lambda
- [ ] `[LEARN]` thread
- [ ] `[LEARN]` mutex
- [ ] `[LEARN]` condition_variable
- [ ] `[LEARN]` chrono
- [ ] `[TOOL]` CMake基础
- [ ] `[CODE]` 写3～5个C++小程序
- [ ] `[GIT]` 每个程序纳入`cpp-foundation`目录

---

## Phase 4必须产出

超级电容：

- [ ] `bring-up-log.md`
- [ ] 5张以上关键波形
- [ ] Sampling Calibration数据
- [ ] Protection测试记录
- [ ] Bug Log
- [ ] 第一版真实实验数据

C++：

- [ ] 3～5个可运行C++程序
- [ ] 一个多线程Producer/Consumer小程序
- [ ] 一个Socket前置练习可留到下月

---

## Phase 4退出条件

超级电容不是“板子点亮”，而是至少完成：

> 辅助电源 → MCU → ADC → Gate Driver → PWM → 低功率Open Loop → Protection → 初步Closed Loop

如果Closed Loop仍未稳定，允许延续到后续月，但必须有清晰Bug/实验记录，不允许“失败了就放弃”。

---

# Phase 5｜2027-02
# Linux应用 + ROS2基础 + MID360S + 简历V1

这是一个重要节点：

> **2月底必须具备投实习的简历，不等所有东西都学完。**

---

# Week 1｜Linux应用开发

- [ ] `[LEARN]` Process vs Thread
- [ ] `[CODE]` fork/exec小实验
- [ ] `[CODE]` pthread/C++ thread
- [ ] `[CODE]` mutex/condition_variable
- [ ] `[LEARN]` File IO
- [ ] `[CODE]` TCP Server/Client
- [ ] `[CODE]` UDP Sender/Receiver
- [ ] `[TOOL]` GDB断点/Backtrace
- [ ] `[TOOL]` CMake编译一个多文件工程
- [ ] `[INT]` 整理20道Linux应用面试题

---

# Week 2｜ROS2核心

- [ ] `[ENV]` 确认Jetson Ubuntu/ROS2版本
- [ ] `[LEARN]` Workspace/Package
- [ ] `[TOOL]` colcon
- [ ] `[CODE]` C++ Publisher
- [ ] `[CODE]` C++ Subscriber
- [ ] `[CODE]` Service/Client
- [ ] `[CODE]` Action Server/Client
- [ ] `[CODE]` Parameter
- [ ] `[CODE]` Launch
- [ ] `[LEARN]` QoS
- [ ] `[LAB]` 不同QoS做简单实验
- [ ] `[TOOL]` ros2 topic/node/interface CLI

---

# Week 3｜TF2 / rosbag2 / MID360S

- [ ] `[LEARN]` TF Tree
- [ ] `[CODE]` Static Transform
- [ ] `[CODE]` Dynamic Transform
- [ ] `[TOOL]` RViz
- [ ] `[TOOL]` rosbag2 record/play
- [ ] `[HW]` 配置MID360S网络
- [ ] `[BUILD]` 编译Livox官方ROS2 Driver
- [ ] `[TEST]` 稳定输出PointCloud2
- [ ] `[TEST]` RViz可视化
- [ ] `[TEST]` rosbag录制和回放
- [ ] `[CODE]` 自己写一个PointCloud简单统计/ROI节点

---

# Week 4｜简历V1 + 求职准备

- [ ] `[JOB]` 写1页中文简历V1
- [ ] `[JOB]` 项目排序：RM/机器人基础、超级电容、已有YOLO
- [ ] `[JOB]` 不写尚未完成的技能为“熟练”
- [ ] `[JOB]` 收集20个目标岗位JD
- [ ] `[AI]` 聚类JD高频关键词
- [ ] `[JOB]` 建投递Tracker
- [ ] `[INT]` 第一次完整模拟技术面
- [ ] `[INT]` 录音复盘项目介绍
- [ ] `[DOC]` 写`resume-gap-analysis.md`

---

## Phase 5必须产出

- [ ] Linux TCP/UDP小程序
- [ ] 两个以上自己写的ROS2 C++ Package
- [ ] MID360S接入成功
- [ ] rosbag文件
- [ ] 点云工具节点
- [ ] ROS2学习笔记
- [ ] **简历V1**
- [ ] 20个JD分析表
- [ ] 投递Tracker

---

## Phase 5退出条件

到2月底应该达到：

> 可以参加机器人嵌入式/MCU/RTOS/智能硬件实习面试，而不是仍然等待“全部学完”。

---

# Phase 6｜2027-03
# 正式投实习 + YOLO完整训练/部署闭环

---

# Track A｜求职（每周持续）

- [ ] `[JOB]` 每周筛选20～30个JD
- [ ] `[JOB]` 每周至少完成有效投递
- [ ] `[JOB]` 每个JD记录岗位/公司/方向/要求/状态
- [ ] `[INT]` 每场面试后24h内写复盘
- [ ] `[INT]` 把不会问题放回学习Backlog
- [ ] `[JOB]` 每两周更新一次简历表达

---

# Track B｜数据集

- [ ] `[AI]` 确定4～8个目标类别
- [ ] `[DATA]` 自己采集图像
- [ ] `[DATA]` 数据清洗
- [ ] `[DATA]` 标注
- [ ] `[DATA]` Train/Val/Test划分
- [ ] `[GIT/DOC]` 记录Dataset Version，不把超大数据直接提交Git

---

# Track C｜训练

- [ ] `[LEARN]` Epoch/Batch/LR
- [ ] `[LEARN]` Precision/Recall
- [ ] `[LEARN]` mAP
- [ ] `[LEARN]` Confusion Matrix
- [ ] `[TRAIN]` 完成Baseline训练
- [ ] `[TEST]` 分析Validation结果
- [ ] `[TRAIN]` 做1～2组合理对照实验
- [ ] `[DOC]` 记录实验配置

---

# Track D｜Jetson部署

- [ ] `[EXPORT]` PyTorch → ONNX
- [ ] `[VERIFY]` 验证ONNX输出
- [ ] `[DEPLOY]` ONNX → TensorRT
- [ ] `[DEPLOY]` FP16
- [ ] `[TEST]` FPS
- [ ] `[TEST]` 单帧Latency
- [ ] `[TEST]` GPU/CPU/显存占用
- [ ] `[TEST]` 比较PyTorch/ONNX/TensorRT
- [ ] `[CODE]` 写C++/ROS2推理Node
- [ ] `[VIDEO]` 录Demo

---

## Phase 6必须产出

- [ ] Dataset说明
- [ ] Training Config
- [ ] Confusion Matrix
- [ ] ONNX文件
- [ ] TensorRT Engine/生成说明（大文件可不入Git）
- [ ] `ai-deployment-report.md`
- [ ] TensorRT Benchmark表
- [ ] Demo视频
- [ ] 投递Tracker
- [ ] 至少一轮完整面试复盘

---

# Phase 7｜2027-04
# 机器人旗舰项目系统集成

这里开始把之前分散的能力组成真正的系统。

目标：

```text
H7 + FreeRTOS + CAN
        ↕
Jetson + ROS2
   ↙        ↘
Camera     MID360S
   ↓
YOLO
```

---

# Week 1｜H7机器人底层V1

- [ ] `[CODE]` Motor Driver整理
- [ ] `[CODE]` Chassis Control
- [ ] `[CODE]` Motor Online检测
- [ ] `[CODE]` Safety基本状态
- [ ] `[CODE]` Watchdog
- [ ] `[TEST]` 控制任务周期
- [ ] `[TEST]` Stack High Water Mark
- [ ] `[DOC]` 更新RTOS Task Table

---

# Week 2｜Host-MCU Protocol

- [ ] `[DESIGN]` 定义SOF/Version/MsgID/Seq/Timestamp/Length/CRC
- [ ] `[CODE]` MCU Parser
- [ ] `[CODE]` Jetson Parser
- [ ] `[CODE]` HEARTBEAT
- [ ] `[CODE]` CMD_VELOCITY
- [ ] `[CODE]` ROBOT_STATE
- [ ] `[CODE]` FAULT_STATE
- [ ] `[CODE]` ODOM_STATE
- [ ] `[TEST]` 错CRC
- [ ] `[TEST]` 半包
- [ ] `[TEST]` 连包
- [ ] `[TEST]` Host停止发送
- [ ] `[DOC]` `communication-protocol.md`

---

# Week 3｜ROS2 Base

- [ ] `[CODE]` `labsentinel_base`或等价Package
- [ ] `[CODE]` Subscribe `/cmd_vel`
- [ ] `[CODE]` Publish `/odom`
- [ ] `[CODE]` Publish `/robot_state`
- [ ] `[CODE]` Publish `/fault_state`
- [ ] `[CODE]` TF
- [ ] `[TEST]` Keyboard Teleop控制实车
- [ ] `[TEST]` Jetson重启/节点重启恢复行为

---

# Week 4｜Camera + LiDAR + YOLO集成

- [ ] `[INTEGRATE]` Camera ROS Node
- [ ] `[INTEGRATE]` YOLO Node
- [ ] `[INTEGRATE]` MID360S
- [ ] `[INTEGRATE]` rosbag
- [ ] `[LAUNCH]` 一键启动基础系统
- [ ] `[TEST]` 运行30分钟
- [ ] `[BUG]` 记录5个真实系统Bug
- [ ] `[VIDEO]` 初版系统Demo

---

## Phase 7必须产出

- [ ] `system-architecture.md`
- [ ] `communication-protocol.md`
- [ ] RTOS Task Table
- [ ] ROS2 Package
- [ ] 一键Launch
- [ ] rosbag样本
- [ ] Runtime Log
- [ ] 至少5个完整Bug Case
- [ ] 初版Demo Video
- [ ] Git Release：`v0.5-system-integration`

---

## Phase 7退出条件

一台真实系统可以：

- Jetson发运动命令
- H7稳定执行
- 状态返回ROS2
- Camera工作
- YOLO工作
- MID360S工作
- rosbag记录
- Host断开时底层不会无限执行旧命令

---

# Phase 8｜2027-05
# 可靠性、性能测试、工程质量

这一个月不要急着加入新功能。

目标：

> 把“能跑”升级成“测过、知道边界、知道怎么坏”。

---

## Heartbeat / Timeout / Fault

- [ ] `[CODE]` Host Heartbeat
- [ ] `[CODE]` Command Timeout
- [ ] `[CODE]` Motor Offline
- [ ] `[CODE]` Fault Code
- [ ] `[CODE]` Safe Stop
- [ ] `[CODE]` Watchdog Reset Reason
- [ ] `[TEST]` Host通信断开
- [ ] `[TEST]` Motor断开
- [ ] `[TEST]` Camera停止
- [ ] `[TEST]` LiDAR停止
- [ ] `[TEST]` ROS2 Node Crash

---

## Performance

- [ ] `[TEST]` MotorControl实际周期
- [ ] `[TEST]` Jitter
- [ ] `[TEST]` MCU Stack
- [ ] `[TEST]` CAN频率/Bus Load基础统计
- [ ] `[TEST]` Host→MCU命令Latency
- [ ] `[TEST]` Camera→YOLO输出Latency
- [ ] `[TEST]` End-to-End控制链延迟
- [ ] `[TEST]` 2小时Long-run

---

## Fault Injection Report

每个Case记录：

```text
Fault
Expected
Observed
Recovery
Evidence
PASS/FAIL
```

---

## Phase 8必须产出

```text
test-report-v1.md
fault-injection-report.md
performance-metrics.csv/md
long-run-test.md
```

报告至少包含：

- Metrics
- Test Setup
- Method
- Result
- Failure
- Improvement

---

## Phase 8退出条件

不能只说“稳定”。

必须能拿数据回答：

- 控制周期多少
- 抖动多少
- Host掉线多久进入安全动作
- 系统连续运行多久
- 哪些故障可恢复
- 哪些故障必须停机

所有具体数字均来自真实实测。

---

# Phase 9｜2027-06
# i.MX6ULL Embedded Linux Driver + 国产MCU迁移

---

# Track A｜Embedded Linux基础

- [ ] `[LEARN]` BootROM→U-Boot→Kernel→RootFS
- [ ] `[LEARN]` Kernel/User Space
- [ ] `[LEARN]` Device Tree
- [ ] `[LEARN]` platform_driver基础
- [ ] `[LEARN]` I2C/SPI driver模型
- [ ] `[LEARN]` IRQ
- [ ] `[LEARN]` Blocking/Non-blocking
- [ ] `[LEARN]` poll/select
- [ ] `[LEARN]` `copy_to_user/copy_from_user`

---

# Track B｜实际Driver

选一个真实外设，不要只做LED。

- [ ] `[HW]` 选择I2C/SPI设备
- [ ] `[DTS]` 写Device Tree
- [ ] `[CODE]` Driver Probe/Remove
- [ ] `[CODE]` 数据读取
- [ ] `[CODE]` IRQ（设备适用时）
- [ ] `[CODE]` Character/合适接口
- [ ] `[CODE]` Userspace C程序
- [ ] `[CODE]` poll/select
- [ ] `[CODE]` Socket发到PC
- [ ] `[TEST]` Driver Load/Unload
- [ ] `[TEST]` Error Path
- [ ] `[DOC]` `driver-design.md`

---

# Track C｜国产MCU迁移

只选择**一种**：

- GD32，或
- N32

任务：

- [ ] `[MIGRATE]` GPIO
- [ ] `[MIGRATE]` UART
- [ ] `[MIGRATE]` Timer
- [ ] `[MIGRATE]` CAN（芯片支持时）
- [ ] `[MIGRATE]` FreeRTOS
- [ ] `[DOC]` 记录STM32与新平台SDK/HAL差异
- [ ] `[DOC]` 写`stm32-to-gd32/n32-migration.md`

目标不是“又会一种芯片”，而是证明：

> 拿到陌生MCU + Datasheet + SDK可以迁移系统。

---

# Track D｜简历V2

- [ ] `[JOB]` 加入真实系统测试指标
- [ ] `[JOB]` 加入Linux Driver项目
- [ ] `[JOB]` 超级电容写实测结果
- [ ] `[JOB]` 删除低价值课程作业
- [ ] `[JOB]` 针对MCU岗制作Resume-A
- [ ] `[JOB]` 针对机器人/Linux岗制作Resume-B

---

## Phase 9必须产出

- [ ] `imx6ull-linux-driver`完整Repo
- [ ] Device Tree
- [ ] Driver Source
- [ ] Userspace Program
- [ ] Driver Design Document
- [ ] Demo/Log
- [ ] 国产MCU迁移记录
- [ ] 简历V2

---

# Phase 10｜2027-07
# 项目封装 + 面试冲刺 + 秋招准备

原则：

> **不再大规模学习新技术。**

把之前的能力变成招聘可见成果。

---

## 10.1 三个作品集封装

### Robot

- [ ] README重写
- [ ] Architecture图
- [ ] RTOS Task图
- [ ] Protocol
- [ ] Test Report
- [ ] Fault Report
- [ ] Demo Video
- [ ] 5个Bug Story
- [ ] Release Tag

### Supercap

- [ ] README
- [ ] Schematic/PCB
- [ ] BOM
- [ ] Bring-up
- [ ] Waveform
- [ ] Test Data
- [ ] Bug Story
- [ ] 开源来源/License说明

### Linux Driver

- [ ] README
- [ ] DTS
- [ ] Driver
- [ ] Userspace
- [ ] Architecture
- [ ] Demo

---

## 10.2 面试知识整理

### C

- [ ] Pointer
- [ ] Memory
- [ ] static/const/volatile
- [ ] alignment
- [ ] macro
- [ ] build/link

### MCU

- [ ] Interrupt
- [ ] DMA
- [ ] Timer
- [ ] ADC
- [ ] UART
- [ ] SPI/I2C
- [ ] CAN
- [ ] Boot

### RTOS

- [ ] Scheduler
- [ ] Queue
- [ ] Semaphore
- [ ] Mutex
- [ ] Priority
- [ ] Deadlock
- [ ] ISR
- [ ] Stack

### Hardware

- [ ] MOS
- [ ] Op-Amp基础
- [ ] ADC
- [ ] Filter
- [ ] Power
- [ ] Pull-up
- [ ] Scope
- [ ] PCB基本问题

### Linux

- [ ] Process/Thread
- [ ] Memory
- [ ] Socket
- [ ] Driver
- [ ] Device Tree

### C++

- [ ] STL
- [ ] RAII
- [ ] Smart Pointer
- [ ] Thread/Mutex

### ROS2

- [ ] Topic
- [ ] Service
- [ ] Action
- [ ] QoS
- [ ] TF
- [ ] Executor

---

## 10.3 项目面试准备

每个项目准备三个版本。

### 30秒版

回答：

> 你做了什么？

### 3分钟版

回答：

- 背景
- 架构
- 我负责什么
- 最大难点
- 结果

### 10分钟技术版

能展开：

- 为什么这样设计
- 替代方案
- 实际Bug
- 性能数据
- 如果重做怎么改

---

## 10.4 Bug Story准备

至少准备：

- [ ] STM32/中断Bug一个
- [ ] FreeRTOS/任务同步Bug一个
- [ ] CAN/通信Bug一个
- [ ] 超级电容硬件Bug一个
- [ ] ROS2/Linux系统Bug一个

每个都按：

```text
现象
→ 假设
→ 实验
→ 根因
→ 修复
→ 验证
→ 学到什么
```

---

## 10.5 数据结构与算法最低要求

- [ ] Array
- [ ] Linked List
- [ ] Stack
- [ ] Queue
- [ ] Hash
- [ ] Binary Tree基础
- [ ] Binary Search
- [ ] Sort
- [ ] BFS/DFS基础
- [ ] Bit Operation

目标：

> 能过嵌入式基础笔试，不是转算法岗。

---

## Phase 10必须产出

- [ ] 三个完整作品集
- [ ] 简历V3/秋招版
- [ ] Resume-A MCU/RTOS
- [ ] Resume-B Robot/Linux
- [ ] 个人Git主页整理
- [ ] 项目Demo合集
- [ ] 100道以上面试问题自己的答案
- [ ] 5个Bug Story
- [ ] JD关键词统计
- [ ] 投递Tracker
- [ ] 秋招投递节奏

---

# 2. 三个项目最终必须达到什么水平

## 项目一｜机器人异构嵌入式系统

必须有：

- [ ] H7下位机自己写
- [ ] FreeRTOS任务设计
- [ ] CAN
- [ ] Motor Control
- [ ] Host-MCU Protocol
- [ ] Heartbeat
- [ ] Fault
- [ ] Watchdog
- [ ] Jetson
- [ ] ROS2
- [ ] Camera
- [ ] YOLO
- [ ] MID360S
- [ ] rosbag
- [ ] Test Report
- [ ] Bug Log
- [ ] Demo

优秀线：

- [ ] Jitter实测
- [ ] End-to-End Latency
- [ ] Fault Injection
- [ ] Long-run Test
- [ ] 一键Launch

---

## 项目二｜超级电容

必须有：

- [ ] 拓扑解释
- [ ] 原理图
- [ ] PCB
- [ ] BOM
- [ ] Bring-up
- [ ] ADC
- [ ] PWM
- [ ] Gate波形
- [ ] Protection
- [ ] Closed Loop进展
- [ ] 实测数据
- [ ] Bug Log
- [ ] 开源来源说明

不要把“复刻”冒充原创。

真正价值是：

> 理解 + 调通 + 测试 + 二次改进。

---

## 项目三｜Embedded Linux Driver

必须有：

- [ ] Device Tree
- [ ] Driver
- [ ] probe/remove
- [ ] IRQ
- [ ] Kernel/User接口
- [ ] Userspace
- [ ] poll/select
- [ ] Socket
- [ ] README
- [ ] Demo

---

# 3. 每个阶段的“产出物”总表

| 阶段 | 核心产出 |
|---|---|
| Phase 0 | Git体系、模板、设备清单 |
| Phase 1 | 15～20 MCU实验、STM32知识图、波形、Debug Checklist |
| Phase 2 | FreeRTOS实验、机器人MCU框架、Architecture、Task Design |
| Phase 3 | 超电原理分析、KiCad、BOM、Design Review、Bring-up Plan |
| Phase 4 | 超电Bring-up、波形、保护测试、C++小程序 |
| Phase 5 | Linux Socket、ROS2 Packages、MID360S、简历V1 |
| Phase 6 | 自建YOLO数据集、TensorRT、Benchmark、投递Tracker |
| Phase 7 | H7+Jetson+ROS2完整系统、Protocol、Demo、5个Bug |
| Phase 8 | Fault Injection、Jitter/Latency/Long-run、Test Report |
| Phase 9 | Linux Driver Repo、国产MCU迁移、简历V2 |
| Phase 10 | 三个完整作品集、简历V3、面试体系、秋招材料 |

---

# 4. 十个月后最终验收

## MCU/RTOS

- [ ] 不看教程独立做STM32项目
- [ ] 熟悉中断/DMA/Timer/CAN
- [ ] 能解释Cortex-M启动/异常基础
- [ ] 能设计FreeRTOS任务系统
- [ ] 能定位常见实时系统问题

## Robot

- [ ] 自己完成H7下位机
- [ ] Jetson/ROS2与MCU完整通信
- [ ] LiDAR + Camera + YOLO接入
- [ ] 有真实系统Demo
- [ ] 有真实测试指标

## Hardware

- [ ] 超级电容项目真实调试
- [ ] 有波形
- [ ] 有实验数据
- [ ] 有Bug
- [ ] 能解释硬件设计

## Linux

- [ ] C++/Linux Thread/Socket
- [ ] 一个真实Driver
- [ ] Device Tree
- [ ] 能解释Kernel/User基本关系

## Engineering

- [ ] Git成为日常工具
- [ ] 三个完整Repo
- [ ] README
- [ ] Architecture
- [ ] Bug Log
- [ ] Test Report
- [ ] Demo Video

## Job

- [ ] 2027-02：简历V1
- [ ] 2027-03：开始实习投递
- [ ] 持续面试复盘
- [ ] 2027-07：秋招简历与作品集定型

---

# 5. 你什么时候可以把任务打勾？

统一规则：

## 学习任务

不是“视频看完”。

而是：

> 能不看答案口头讲清楚，并且至少做过一个实验/代码验证。

## 实验任务

必须有：

> Code + Result + Screenshot/Waveform + Conclusion。

## 项目任务

必须有：

> Git Commit + Documentation + Test。

## 技能任务

只有满足：

> 我能解释 + 我能写 + 我能测 + 我能Debug

才可以标记“掌握”。

---

# 6. 最重要的执行纪律

未来十个月遇到新技术时，先问：

1. 它是否直接解决当前Phase的问题？
2. 它是否是目标JD的高频技能？
3. 它是否能增加三个核心作品集之一的质量？

如果三个答案都是“No”：

> 放进Backlog，不立即学习。

当前禁止因为焦虑同时新开：

- FPGA
- Cadence深度学习
- 强化学习
- 双目视觉深入
- VLA
- Rust嵌入式
- Zephyr
- 多种国产MCU
- Linux Kernel全源码阅读

你的目标不是“接触最多”。

而是：

> **到2027年7月，让面试官可以看到三个真正完整、有测试、有Bug、有代码、有工程文档的项目。**
