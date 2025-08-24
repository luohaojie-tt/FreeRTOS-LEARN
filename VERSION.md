# 版本说明

## V1.1 (2025-08-24)

### 更新内容
1. 更新了GD32F10x标准外设库版本号从V1.0到V1.1
2. 完善了项目驱动程序框架，添加了以下驱动模块：
   - ADC (模数转换器)
   - DAC (数模转换器)
   - GPIO (通用输入输出)
   - I2C (Inter-Integrated Circuit)
   - PWM (脉宽调制)
   - SPI (串行外设接口)

### 新增文件
- Drivers/ADC/
  - README.md: ADC驱动说明文档
  - adc_example.c: ADC使用示例
  - gd32f10x_adc.c: ADC驱动源文件
  - gd32f10x_adc.h: ADC驱动头文件

- Drivers/DAC/
  - README.md: DAC驱动说明文档
  - dac_example.c: DAC使用示例
  - gd32f10x_dac.c: DAC驱动源文件
  - gd32f10x_dac.h: DAC驱动头文件

- Drivers/GPIO/
  - README.md: GPIO驱动说明文档
  - gpio_example.c: GPIO使用示例
  - gd32f10x_gpio.c: GPIO驱动源文件
  - gd32f10x_gpio.h: GPIO驱动头文件

- Drivers/I2C/
  - README.md: I2C驱动说明文档
  - i2c_example.c: I2C使用示例
  - gd32f10x_i2c.c: I2C驱动源文件
  - gd32f10x_i2c.h: I2C驱动头文件

- Drivers/PWM/
  - README.md: PWM驱动说明文档
  - pwm_example.c: PWM使用示例
  - gd32f10x_pwm.c: PWM驱动源文件
  - gd32f10x_pwm.h: PWM驱动头文件

- Drivers/SPI/
  - README.md: SPI驱动说明文档
  - spi_example.c: SPI使用示例
  - gd32f10x_spi.c: SPI驱动源文件
  - gd32f10x_spi.h: SPI驱动头文件

### 改进
1. 优化了项目结构，为后续的驱动开发和示例代码实现奠定了基础
2. 为每个驱动模块提供了详细的说明文档和使用示例

## V1.0 (2025-08-24)
- 初始版本
- 完成了FreeRTOS在GD32F103C8T6上的基础移植
- 建立了项目框架结构