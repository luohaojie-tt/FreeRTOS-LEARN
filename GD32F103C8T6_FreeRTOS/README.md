# GD32F103C8T6 FreeRTOS项目

## 项目概述
这是一个基于GD32F103C8T6芯片的嵌入式项目，使用FreeRTOS实时操作系统。

## 版本信息
- 当前版本: V1.1
- 版本说明: 请参考 [VERSION.md](VERSION.md) 文件

## 项目结构
```
GD32F103C8T6_FreeRTOS/
├── Drivers/           # 驱动程序
│   ├── ADC/           # ADC驱动
│   ├── DAC/           # DAC驱动
│   ├── GPIO/          # GPIO驱动
│   ├── I2C/           # I2C驱动
│   ├── PWM/           # PWM驱动
│   ├── SPI/           # SPI驱动
│   └── CMSIS/         # ARM CMSIS库
├── FreeRTOS/          # FreeRTOS源码
├── Inc/               # 头文件
├── Src/               # 源文件
├── README.md          # 项目说明文件
└── VERSION.md         # 版本说明文件
```

## 开发环境
- IDE: Keil MDK / STM32CubeIDE / 其他支持ARM Cortex-M3的IDE
- 编译器: ARM GCC / Keil ARMCC / IAR
- 调试器: J-Link / ST-Link

## 移植步骤记录

### 1. 项目框架搭建
- 创建了基本的项目目录结构
- 克隆了FreeRTOS-Kernel源码到项目中

### 2. FreeRTOS移植
- 获取了FreeRTOS源码并放入项目目录
- 确认了适用于GD32F103C8T6的ARM_CM3移植层
- 移植层文件位于: FreeRTOS/portable/GCC/ARM_CM3/port.c

### 3. 驱动程序框架完善 (V1.1)
- 添加了ADC、DAC、GPIO、I2C、PWM、SPI等驱动模块
- 为每个驱动模块提供了示例代码和说明文档

## 下一步工作
1. 完成FreeRTOS在GD32F103C8T6上的完整移植
2. 配置芯片启动文件和链接脚本
3. 实现基本的任务创建和调度示例
4. 完善各驱动模块的功能实现和测试