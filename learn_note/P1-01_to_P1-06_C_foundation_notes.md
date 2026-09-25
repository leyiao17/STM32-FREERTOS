# Phase 1｜P1-01 ～ P1-06 C 语言基础重构笔记

> 目标：不追求把每个知识点写成教材，而是建立一条能用于 STM32、Debug 和面试的理解主线。
>
> 主线：
>
> ```text
> 指针与内存
>   ↓
> 函数指针 / 回调 / 接口
>   ↓
> 作用域 / 生命周期 / const / volatile
>   ↓
> struct / 内存布局 / 字节序 / 位操作
>   ↓
> Stack / Heap / 内存错误
>   ↓
> C源码 → ELF → STM32启动
> ```

---

# P1-01｜指针、数组与内存

## 1. 核心理解

先建立四个概念：

```text
变量
↓
一个有类型的对象

地址
↓
对象在内存中的位置

指针
↓
保存地址的变量

类型
↓
告诉编译器如何解释这片内存、一次访问多少字节
```

例如：

```c
uint32_t x = 100;
uint32_t *p = &x;
```

关系：

```text
x
↓
100

&x
↓
x 的地址

p
↓
保存 &x

*p
↓
访问 p 指向的 uint32_t 对象
```

所以：

```c
*p = 200;
```

最终修改的是：

```c
x
```

---

## 2. 指针类型为什么重要

```c
uint8_t  *p8;
uint16_t *p16;
uint32_t *p32;
```

类型会影响：

```text
如何解释内存
+
一次访问多大
+
指针 + 1 前进多少
```

典型情况下：

```text
uint8_t*  + 1 → 1 Byte
uint16_t* + 1 → 2 Byte
uint32_t* + 1 → 4 Byte
```

---

## 3. 数组

```c
int a[4];
```

数组是一组：

```text
相同类型
+
连续存储
```

的对象。

```text
a[0]
a[1]
a[2]
a[3]
```

在内存中连续排列。

---

## 4. 数组名和指针

不要简单背：

> 数组名就是指针。

更准确：

> 数组表达式在很多场景下会转换为指向首元素的指针。

例如：

```c
a
```

很多表达式中相当于：

```c
&a[0]
```

但：

```c
sizeof(a)
```

得到的是整个数组大小。

---

## 5. `a`、`&a[0]`、`&a`

假设：

```c
int a[4];
```

它们的数值地址可能一样，但类型不同：

```text
a
↓
通常转换为 int *

&a[0]
↓
int *

&a
↓
int (*)[4]
```

因此：

```text
a + 1
↓
前进一个 int

&a + 1
↓
前进整个 int[4]
```

---

## 6. 指针数组 vs 数组指针

指针数组：

```c
int *p[4];
```

理解：

```text
p 是数组
数组里有 4 个 int *
```

数组指针：

```c
int (*p)[4];
```

理解：

```text
p 是指针
它指向 int[4]
```

---

## 7. 二级指针

```c
int **pp;
```

关系：

```text
pp
↓
指向一个指针

*pp
↓
得到一级指针

**pp
↓
得到最终对象
```

如果函数需要修改调用者的指针：

```c
void change(int **pp);
```

往往就需要二级指针。

---

## 8. `void *`

```c
void *p;
```

可以保存通用的**对象指针**。

常见于：

```text
通用接口
Callback Context
Driver Context
malloc 返回值
```

使用前通常要恢复成正确对象类型。

---

## 9. 常见危险

```text
NULL
↓
没有指向有效对象

野指针
↓
从未正确初始化

悬空指针
↓
曾经有效，但对象生命周期已经结束

越界访问
↓
访问不属于自己的内存

Undefined Behavior
↓
程序行为不再受 C 语言保证
```

典型错误：

```c
int *func(void)
{
    int x = 10;
    return &x;
}
```

`func()` 返回后：

```text
x 生命周期结束
↓
返回的地址成为悬空地址
```

---

## 10. 和 STM32 的连接

```c
volatile uint32_t *reg =
    (volatile uint32_t *)0x40000000;
```

本质就是：

```text
地址
+
指针
+
类型
+
解引用
```

所以后面的寄存器操作，本质仍然建立在 P1-01 上。

---

# P1-02｜函数、函数指针与回调

## 1. 函数也有地址

普通调用：

```c
add(1, 2);
```

函数指针：

```c
int (*fp)(int, int);

fp = add;

fp(1, 2);
```

理解：

```text
fp
↓
保存某个函数的地址

fp(...)
↓
通过这个地址调用函数
```

---

## 2. 函数指针声明

```c
int (*fp)(int, int);
```

拆：

```text
fp
↓
*fp
↓
(*fp)(int, int)
↓
指向“接收两个 int、返回 int”的函数
```

注意：

```c
int *fp(int, int);
```

不是函数指针。

它表示：

```text
一个返回 int * 的函数
```

---

## 3. typedef 简化

```c
typedef int (*Operation)(int, int);

Operation op;
```

比直接写复杂声明更清楚。

---

## 4. Callback｜回调

回调最重要的理解：

> 把一个函数交给另一个模块保存，在某个事件发生时，由那个模块再调用它。

例如：

```c
typedef void (*UartCallback)(uint8_t data);

static UartCallback rx_callback = NULL;

void uart_register_callback(UartCallback cb)
{
    rx_callback = cb;
}

void uart_receive(uint8_t data)
{
    if (rx_callback != NULL)
    {
        rx_callback(data);
    }
}
```

APP：

```c
void app_handler(uint8_t data)
{
    ...
}

uart_register_callback(app_handler);
```

过程：

```text
APP 把 app_handler 地址交给 UART
            ↓
UART 保存到 rx_callback
            ↓
UART 收到数据
            ↓
rx_callback(data)
            ↓
实际调用 app_handler(data)
```

所谓“注册回调”：

```text
本质就是保存函数地址
```

---

## 5. Callback 的模块关系

典型：

```text
APP
 │
 │ 注册 callback
 ▼
Driver
 │
 │ 硬件事件发生
 ▼
callback()
 │
 ▼
APP
```

所以 Driver 不需要写死：

```c
app_handler();
```

它只知道：

```c
rx_callback();
```

这样 Driver 和 APP 解耦。

---

## 6. 函数指针表

```c
typedef void (*StateHandler)(void);

StateHandler handlers[] =
{
    idle_handler,
    run_handler,
    fault_handler
};
```

调用：

```c
handlers[state]();
```

本质：

```text
索引
↓
找到函数指针
↓
调用对应函数
```

---

## 7. Driver Interface

```c
typedef struct
{
    int (*init)(void);
    int (*read)(uint8_t *buf, uint16_t len);
    int (*write)(const uint8_t *buf, uint16_t len);
} DriverOps;
```

UART 可以提供一套实现：

```text
uart_ops
```

SPI 可以提供另一套：

```text
spi_ops
```

上层只依赖：

```text
DriverOps
```

而不是写死具体 UART/SPI。

可以理解成 C 中的：

```text
手工接口
+
动态分发
```

---

## 8. DriverOps 和 Callback 区别

```text
APP → Driver
```

通常通过：

```text
DriverOps
```

表示：

> APP 主动要求 Driver 做事。

而：

```text
Driver → APP
```

通常通过：

```text
Callback
```

表示：

> Driver 有事件需要通知 APP。

---

## 9. 状态机 + 函数指针

```text
State
↓
查 Handler Table
↓
执行当前状态 Handler
```

例如：

```c
handlers[ROBOT_RUN]();
```

但要记住：

> 函数表只是状态动作的组织方式，不等于完整状态机。

真正状态机还包含：

```text
State
+
Event / Condition
↓
Next State
+
Action
```

---

# P1-03｜作用域、生命周期与类型限定

## 1. Scope 和 Lifetime 不是一回事

Scope：

```text
这个名字在哪里能被代码访问？
```

Lifetime：

```text
这个对象什么时候存在？
```

---

## 2. 普通局部变量

```c
void func(void)
{
    int x = 10;
}
```

典型：

```text
Scope
↓
func 内部

Lifetime
↓
进入对应块 → 离开对应块
```

---

## 3. 全局变量

```c
int g_value;
```

生命周期：

```text
整个程序运行期间
```

---

## 4. `static` 局部变量

```c
void func(void)
{
    static int count = 0;
    count++;
}
```

特点：

```text
Scope
↓
仍然只在 func 内

Lifetime
↓
整个程序运行期间
```

所以函数再次进入时：

```text
count 的值仍然保留
```

---

## 5. 文件作用域 `static`

```c
static int module_state;
```

常用于：

```text
模块内部私有状态
```

其他 `.c` 文件不能像普通外部符号那样直接访问这个名字。

---

## 6. `const`

```c
const uint32_t value = 10;
```

表示：

```text
不能通过这个名字修改对象
```

指针是最容易考的：

```c
const uint8_t *p;
```

理解：

```text
p 可以改
*p 不能通过 p 改
```

---

```c
uint8_t * const p = ...;
```

理解：

```text
p 不能改
*p 可以改
```

---

```c
const uint8_t * const p = ...;
```

理解：

```text
p 不能改
*p 也不能通过 p 改
```

---

## 7. `volatile`

```c
volatile uint32_t flag;
```

告诉 Compiler：

> 这个对象可能被当前代码流程之外的因素改变，对它的访问不能随意优化掉。

典型场景：

```text
硬件寄存器
ISR 和主程序共享变量
某些并发/外部修改场景
```

例如：

```c
while (flag == 0)
{
}
```

如果 `flag` 可能被 ISR 修改，`volatile` 可以让 Compiler 每次按要求重新访问对象。

---

## 8. `volatile` 不是什么

必须记住：

```text
volatile
≠ atomic

volatile
≠ thread-safe

volatile
≠ mutex

volatile
≠ memory barrier 的万能替代
```

它主要解决：

```text
Compiler 对访问的优化问题
```

不是完整并发同步机制。

---

# P1-04｜数据组织与底层表示

## 1. struct

```c
typedef struct
{
    uint8_t id;
    int16_t speed;
    int16_t current;
} Motor;
```

本质：

> 按一定内存布局，把多个成员组织成一个对象。

访问：

```c
motor.speed;
```

如果是指针：

```c
Motor *p = &motor;

p->speed;
```

其中：

```c
p->speed
```

等价于：

```c
(*p).speed
```

---

## 2. struct 和 STM32 寄存器

STM32 中：

```c
GPIOA->ODR
```

可以理解成：

```text
GPIOA
↓
指向 GPIO 寄存器结构体的指针

ODR
↓
结构体中的某个成员

GPIOA基地址 + ODR成员偏移
↓
ODR实际寄存器地址
```

因此：

```text
struct + pointer
```

就是 CMSIS 寄存器映射的重要基础。

---

## 3. Alignment / Padding

例如：

```c
typedef struct
{
    uint8_t a;
    uint32_t b;
    uint8_t c;
} Test;
```

不能简单认为：

```text
sizeof(Test) = 1 + 4 + 1 = 6
```

Compiler 可能为了满足对齐要求插入：

```text
Padding
```

概念布局可能：

```text
offset 0      a
offset 1~3    padding
offset 4~7    b
offset 8      c
offset 9~11   padding
```

因此：

```text
sizeof(Test)
```

可能是 12。

具体规则由：

```text
目标平台 ABI
Compiler
类型对齐要求
```

决定。

---

## 4. 成员顺序影响大小

```c
struct A
{
    uint8_t a;
    uint32_t b;
    uint8_t c;
};
```

与：

```c
struct B
{
    uint32_t b;
    uint8_t a;
    uint8_t c;
};
```

成员相同，但 Padding 可能不同。

所以成员顺序可能影响：

```text
sizeof(struct)
```

---

## 5. union

```c
union Data
{
    uint32_t value;
    uint8_t bytes[4];
};
```

和 struct 最大区别：

```text
struct
↓
每个成员有自己的存储

union
↓
所有成员共享同一块存储
```

可以把同一组 bit 用不同成员形式观察。

---

## 6. enum

```c
typedef enum
{
    ROBOT_IDLE,
    ROBOT_RUN,
    ROBOT_FAULT
} RobotState;
```

比：

```c
int state;
```

更清楚地表达：

```text
一组相关离散状态
```

---

## 7. Endianness｜大小端

假设：

```c
uint32_t value = 0x12345678;
```

Little Endian：

```text
低地址
↓
78 56 34 12
```

Big Endian：

```text
低地址
↓
12 34 56 78
```

注意：

> 大小端描述的是多字节对象在内存中的 Byte 排列，不是数值本身变了。

STM32 Cortex-M 常见工作方式是 Little Endian。

---

## 8. 位操作

最常用：

```text
&
|
^
~
<<
>>
```

生成某一位 Mask：

```c
1U << n
```

置位：

```c
reg |= (1U << n);
```

清位：

```c
reg &= ~(1U << n);
```

翻转：

```c
reg ^= (1U << n);
```

检查：

```c
if (reg & (1U << n))
{
}
```

STM32 寄存器操作的核心就是：

```text
只修改目标 bit
尽量保持其他 bit 不变
```

---

## 9. 通信协议连接

例如收到：

```text
Byte0 Byte1 → angle
Byte2 Byte3 → speed
```

解析过程：

```text
Raw Bytes
↓
Endianness
↓
Shift / OR
↓
整数
↓
写入 struct
↓
上层使用
```

这就是后面：

```text
UART Parser
CAN Parser
Motor Feedback
```

的基础。

---

# P1-05｜Stack / Heap / 内存问题

## 1. 先分清对象

```c
int global_a = 100;

void func(void)
{
    int x = 10;

    int *p = malloc(sizeof(int));
}
```

这里：

```text
global_a
↓
静态存储期对象

x
↓
自动存储期对象

p
↓
一个自动指针变量

malloc 出来的 int
↓
动态分配对象
```

特别重要：

```text
指针变量
≠
指针指向的对象
```

---

## 2. Stack

Stack 主要与：

```text
函数调用
局部自动对象
保存调用现场
部分临时数据
```

有关。

调用：

```text
main
↓
A
↓
B
↓
C
```

通常形成多个调用层次。

返回：

```text
C
↓
B
↓
A
↓
main
```

符合：

```text
Last In, First Out
```

---

## 3. Stack Frame

一次函数调用通常需要自己的工作区域：

```text
局部数据
保存的寄存器
调用现场
必要的参数/临时数据
```

称为：

```text
Stack Frame
```

具体内容由：

```text
ABI
Compiler
Optimization
函数本身
```

决定。

---

## 4. Stack Overflow

危险场景：

```c
void func(void)
{
    uint8_t buffer[4096];
}
```

或者深度递归：

```text
func
↓
func
↓
func
↓
...
```

Stack 空间有限。

超出边界可能：

```text
破坏其他内存
↓
异常行为
↓
HardFault / Crash
```

---

## 5. Heap

```c
int *p = malloc(sizeof(int));
```

含义：

```text
运行时申请一块动态内存
↓
malloc 返回它的地址
↓
p 保存这个地址
```

必须检查：

```c
if (p != NULL)
```

因为：

```text
malloc 可能失败
```

---

## 6. `free`

```c
free(p);
```

释放的是：

```text
p 指向的动态对象
```

不是：

```text
p 这个指针变量本身
```

执行后：

```text
p 变量可能仍然存在
但原动态对象已经结束生命周期
```

---

## 7. 常见内存问题

### Memory Leak

```text
malloc
↓
忘记 free
↓
内存长期无法重新利用
```

---

### Use After Free

```c
free(p);
*p = 10;
```

对象已经失效，却继续访问。

---

### Double Free

```c
free(p);
free(p);
```

同一个动态对象重复释放。

---

### Buffer Overflow

```c
uint8_t buffer[8];

buffer[8] = 1;
```

合法范围只有：

```text
buffer[0] ~ buffer[7]
```

---

### Dangling Pointer

```text
指针仍然保存地址
但对象生命周期已经结束
```

---

## 8. Heap Fragmentation

动态申请、释放后可能出现：

```text
很多小块空闲区域
```

即使总空闲空间不少，也可能找不到足够大的：

```text
连续内存
```

因此实时 MCU 中需要谨慎设计动态内存。

---

## 9. 为什么 MCU 谨慎使用 malloc/free

主要考虑：

```text
内存有限
分配可能失败
Memory Leak
Fragmentation
运行时间是否可预测
对象所有权
多任务安全
长期运行稳定性
```

不是：

> MCU 绝对不能使用 malloc。

而是：

> 使用动态内存必须明确代价和生命周期。

---

## 10. Reentrant｜可重入

可以先理解成：

> 一个函数执行过程中再次进入该函数，不会破坏前一次调用正在使用的状态。

例如：

```c
int calculate(int x)
{
    int temp = x * 2;
    return temp + 1;
}
```

每次调用有自己的状态，比较容易做到可重入。

而：

```c
static int temp;

int calculate(int x)
{
    temp = x * 2;
    return temp + 1;
}
```

多个调用共享：

```text
temp
```

就可能互相影响。

这在：

```text
Main + ISR
多个 RTOS Task
递归
```

中非常重要。

---

# P1-06｜从 C 到 ELF

## 1. 整体过程

```text
main.c
  │
  │ Preprocess
  ▼
main.i
  │
  │ Compile
  ▼
main.s
  │
  │ Assemble
  ▼
main.o
  │
  │ Link
  ▼
firmware.elf
```

---

## 2. Preprocess

命令：

```bash
gcc -E main.c -o main.i
```

主要处理：

```text
#include
#define
#if / #ifdef
```

例如：

```c
#define VALUE 10

int x = VALUE;
```

预处理后可以粗略理解为：

```c
int x = 10;
```

---

## 3. Compile

命令：

```bash
gcc -S main.c -o main.s
```

过程：

```text
C
↓
语法 / 类型检查
↓
优化
↓
目标架构汇编
```

输出：

```text
main.s
```

---

## 4. Assemble

```bash
gcc -c main.c -o main.o
```

最终得到：

```text
Object File
```

`.o` 已经包含目标 CPU 的机器码，但还不是完整程序。

---

## 5. Symbol

例如：

`main.c`：

```c
int add(int, int);

int main(void)
{
    return add(1, 2);
}
```

`math.c`：

```c
int add(int a, int b)
{
    return a + b;
}
```

关系：

```text
main.o
↓
需要 add

math.o
↓
提供 add

Linker
↓
把它们连接起来
```

---

## 6. Linker

主要负责：

```text
合并多个 .o / Library
解析 Symbol
处理 Relocation
决定最终地址
按照 Linker Script 布局 Section
```

最终：

```text
firmware.elf
```

---

## 7. 常见 Link Error

没有实现：

```text
undefined reference
```

重复定义：

```text
multiple definition
```

因此：

```text
Compile Error
↓
通常是单个 Translation Unit 的语法/类型等问题

Link Error
↓
多个目标文件组合后的 Symbol / Definition 问题
```

---

## 8. Linker Script

STM32 常见：

```text
xxx_FLASH.ld
```

主要描述：

```text
FLASH 起始地址 / 大小
RAM 起始地址 / 大小
各 Section 放在哪里
一些 Stack / Heap / Startup 所需符号
```

所以最终地址主要由：

```text
Linker
+
Linker Script
```

决定。

---

## 9. ELF

ELF 可以包含：

```text
代码
数据
Section
Symbol
Debug Information
```

因此可以用于：

```text
Debugger
GDB
objdump
nm
readelf
HardFault 分析
```

---

## 10. 四个重要 Section

### `.text`

```text
程序机器代码
典型位于 Flash
```

### `.rodata`

```text
只读数据
字符串、只读表等
典型位于 Flash
```

### `.data`

例如：

```c
int speed = 100;
```

过程：

```text
Flash 保存初始值
↓
Startup
↓
复制到 RAM
↓
程序运行时在 RAM 中修改
```

### `.bss`

例如：

```c
uint8_t buffer[1024];
```

过程：

```text
只需要知道运行时需要多少 RAM
↓
Startup
↓
把对应 RAM 区域清零
```

所以 `.bss`：

```text
占运行时 RAM
但通常不需要在 Flash 镜像保存大量 0
```

---

## 11. `.data` vs `.bss`

```text
.data
↓
非零初始化静态存储期数据
↓
RAM 运行
+
Flash 保存初始镜像
```

```text
.bss
↓
零初始化静态存储期数据
↓
RAM 运行
+
Startup 清零
```

---

## 12. Map File

Map 文件可以帮助查看：

```text
Symbol 最终地址
Section 大小
Flash / RAM 使用
哪个 .o 占空间
变量最终在哪里
```

遇到：

```text
RAM 为什么突然增加？
```

可以优先查看：

```text
.map
```

---

## 13. 常用命令

```bash
gcc -E main.c -o main.i
gcc -S main.c -o main.s
gcc -c main.c -o main.o
```

STM32 GCC：

```bash
arm-none-eabi-size firmware.elf
arm-none-eabi-readelf -S firmware.elf
arm-none-eabi-nm firmware.elf
arm-none-eabi-objdump -d firmware.elf
```

---

# P1-01 ～ P1-06 总连接

现在不要把六章当成六堆知识点。

它们实际是一条链：

```text
P1-01
地址 / 指针 / 数组
        │
        ▼
理解“数据在哪里、如何访问”


P1-02
函数地址 / 函数指针 / Callback
        │
        ▼
理解“代码也可以通过地址间接调用”


P1-03
Scope / Lifetime / static / const / volatile
        │
        ▼
理解“对象什么时候存在、编译器如何对待它”


P1-04
struct / Alignment / Endian / Bit
        │
        ▼
理解“数据在内存里到底怎样排列和解释”


P1-05
Stack / Heap / Memory Error
        │
        ▼
理解“运行时对象和函数调用如何占用内存”


P1-06
Compile / Link / ELF / Section
        │
        ▼
理解“这些代码和对象最终怎样进入 MCU”
```

下一步：

```text
P1-07
Cortex-M CPU / Register / SP / LR / PC
```

再下一步：

```text
P1-08
Reset
↓
Vector Table
↓
MSP
↓
Reset_Handler
↓
.data copy
↓
.bss zero
↓
SystemInit
↓
main()
```

到这里，C 语言知识会真正和 STM32 CPU 执行过程连接起来。

---

# 常见面试问题

下面以“能口述”为目标，不需要背长答案。

---

## 1. 指针是什么？

指针是：

> 保存地址的变量。

指针类型还决定：

```text
如何解释目标内存
+
解引用访问多少数据
+
指针运算步长
```

---

## 2. `a`、`&a[0]`、`&a` 有什么区别？

对于：

```c
int a[4];
```

典型：

```text
a
→ 表达式中常转换为 int *

&a[0]
→ int *

&a
→ int (*)[4]
```

数值地址可能一样，但类型和 `+1` 的步长不同。

---

## 3. 指针数组和数组指针区别？

```c
int *p[4];
```

是：

```text
数组，里面放指针
```

```c
int (*p)[4];
```

是：

```text
指针，指向一个数组
```

---

## 4. 为什么函数修改调用者指针时经常需要二级指针？

因为参数传递本身是值传递。

如果只传：

```c
int *p
```

修改的是指针副本。

想修改调用者自己的指针变量，需要把：

```text
这个指针变量的地址
```

传进去，即：

```c
int **pp
```

---

## 5. 函数指针是什么？

例如：

```c
int (*fp)(int, int);
```

表示：

> fp 是一个指针，指向“接收两个 int、返回 int”的函数。

可以：

```c
fp = add;
fp(1, 2);
```

---

## 6. Callback 是什么？

Callback 是：

> 把函数指针交给另一个模块保存，在某个事件发生时，由该模块调用这个函数。

典型：

```text
APP 注册 callback
↓
Driver 保存函数地址
↓
硬件事件发生
↓
Driver 调 callback
↓
通知 APP
```

---

## 7. Callback 和 DriverOps 有什么区别？

典型方向：

```text
APP → Driver
使用 DriverOps

Driver → APP
使用 Callback
```

一个偏“请求服务”，一个偏“事件通知”。

---

## 8. `static` 局部变量有什么特点？

```text
Scope
↓
仍然在函数/块内部

Lifetime
↓
整个程序运行期间
```

函数退出后值仍然保留。

---

## 9. `const uint8_t *p` 和 `uint8_t * const p` 区别？

```c
const uint8_t *p;
```

```text
p 可以改变
*p 不能通过 p 修改
```

```c
uint8_t * const p = ...;
```

```text
p 不能改变
*p 可以修改
```

---

## 10. `volatile` 有什么作用？

主要告诉 Compiler：

> 这个对象可能被外部因素改变，对它的访问不能随意优化掉。

常见：

```text
硬件寄存器
ISR共享变量
```

但：

```text
volatile ≠ atomic
volatile ≠ thread-safe
```

---

## 11. struct 为什么会有 Padding？

为了满足目标平台的：

```text
Alignment
```

要求。

因此：

```text
sizeof(struct)
```

可能大于成员大小之和。

成员顺序也可能影响最终大小。

---

## 12. struct 和 union 区别？

```text
struct
↓
每个成员有自己的存储

union
↓
所有成员共享同一块存储
```

---

## 13. 什么是大小端？

描述多字节对象在内存中的 Byte 排列。

对于：

```text
0x12345678
```

Little Endian：

```text
低地址 → 78 56 34 12
```

Big Endian：

```text
低地址 → 12 34 56 78
```

---

## 14. 如何设置、清除、检查某一个寄存器 bit？

设置：

```c
reg |= (1U << n);
```

清除：

```c
reg &= ~(1U << n);
```

检查：

```c
if (reg & (1U << n))
{
}
```

---

## 15. Stack 和 Heap 区别？

Stack：

```text
主要服务函数调用和自动对象
通常自动管理
空间有限
```

Heap：

```text
主要服务动态分配
malloc/free 管理
可能失败、泄漏、碎片化
```

---

## 16. `free(p)` 后 p 还存在吗？

可能存在。

`free(p)` 结束的是：

```text
p 指向的动态对象
```

不是：

```text
p 这个变量本身
```

因此此时 `p` 可能成为悬空指针。

---

## 17. Memory Leak 是什么？

```text
动态内存已经申请
↓
程序不再需要
↓
却没有释放
```

导致可用内存逐渐减少。

---

## 18. Use After Free 是什么？

```c
free(p);
*p = 10;
```

对象已经结束生命周期，却继续访问。

属于严重内存错误。

---

## 19. 为什么嵌入式中谨慎使用 malloc/free？

因为需要考虑：

```text
内存有限
分配失败
泄漏
碎片化
实时性
所有权
长期运行稳定性
```

---

## 20. 什么叫可重入函数？

一个函数执行过程中再次被调用时：

> 新调用不会破坏旧调用正在使用的状态。

共享可修改的：

```text
global
static
```

状态会增加不可重入风险。

---

## 21. C 程序从源码到 ELF 经历什么？

```text
Preprocess
↓
Compile
↓
Assemble
↓
Link
```

即：

```text
.c → .i → .s → .o → .elf
```

---

## 22. `gcc -E / -S / -c` 分别是什么？

```text
-E
→ 预处理后停止

-S
→ 生成汇编后停止

-c
→ 生成 .o 后停止，不链接
```

---

## 23. `.o` 已经有机器码了吗？

有。

但是：

```text
外部 Symbol 可能没解析
最终地址可能没确定
多个模块还没有组合
```

所以还需要 Link。

---

## 24. `undefined reference` 是什么问题？

通常是 Link Error。

意思是：

```text
代码使用了某个 Symbol
↓
但 Linker 找不到对应 Definition
```

---

## 25. `.text / .rodata / .data / .bss` 分别是什么？

```text
.text
→ 机器代码

.rodata
→ 只读数据

.data
→ 非零初始化的静态存储期可写数据

.bss
→ 零初始化静态存储期数据
```

STM32 典型：

```text
.text / .rodata
→ Flash

.data
→ RAM运行 + Flash初始镜像

.bss
→ RAM运行 + Startup清零
```

---

## 26. 为什么 `.data` 同时占 RAM 和 Flash？

因为：

```text
运行时需要修改
→ 放 RAM

上电后需要恢复初始值
→ 初始镜像存在 Flash
```

Startup 将它从 Flash 复制到 RAM。

---

## 27. 为什么 `.bss` 不需要在 Flash 中保存大量 0？

因为 Startup 可以：

```text
直接把对应 RAM 区域清零
```

所以只需要知道：

```text
地址
+
大小
```

不必在固件镜像保存成千上万个零。

---

## 28. Linker Script 有什么作用？

主要告诉 Linker：

```text
FLASH / RAM 从哪里开始
有多大
Section 放哪里
一些 Startup / Stack / Heap 所需符号
```

---

## 29. Map File 有什么用？

用于查看：

```text
Symbol 地址
Section 大小
Flash / RAM 占用
哪个 .o 占空间
变量最终放在哪里
```

---

## 30. ELF 和 BIN 的区别？

ELF 通常包含：

```text
代码
数据
Section
Symbol
Debug Information
```

适合 Debug 和分析。

BIN 更接近：

```text
需要烧写的原始 Byte 数据
```

---

# 最终自检

如果下面这条链能不看答案自己讲出来，P1-01 ～ P1-06 的基础就基本建立起来了：

```text
一个 uint32_t 变量是什么？
↓
它为什么有地址？
↓
指针为什么能访问它？
↓
数组为什么可以用指针遍历？
↓
函数为什么也能通过函数指针调用？
↓
Driver 为什么能保存 Callback？
↓
static / const / volatile 分别在解决什么问题？
↓
struct 为什么会有 Padding？
↓
0x12345678 在内存中怎样排列？
↓
局部对象和 malloc 对象的生命周期有什么区别？
↓
为什么会 Stack Overflow / UAF / Memory Leak？
↓
.c 文件怎样变成 .o？
↓
多个 .o 怎样变成 ELF？
↓
.data / .bss 为什么需要 Startup 处理？
↓
STM32 Reset 后又是谁完成这些工作？
```

最后一个问题，就是下一阶段：

```text
P1-07 Cortex-M CPU
+
P1-08 Reset → main()
```
