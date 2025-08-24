# PWM Driver for GD32F103C8T6

## Overview

This PWM driver provides a complete interface for configuring and controlling the PWM peripherals on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **PWM Initialization**
   - Configurable PWM frequency (0-1MHz)
   - Configurable duty cycle (0-100%)
   - Configurable counter mode (up, down, center-aligned)
   - Configurable output compare mode
   - Configurable output polarity

2. **PWM Control Functions**
   - Enable/disable PWM channels
   - Set compare values for duty cycle control
   - Set auto-reload and prescaler values
   - Configure fast mode and preload registers

3. **Advanced Features**
   - Support for complementary outputs
   - Idle state configuration
   - Forced output control
   - DMA support

4. **FreeRTOS Integration**
   - Thread-safe operation
   - Example provided with FreeRTOS task for PWM control

## API Functions

### PWM Initialization
- `void PWM_DeInit(TIMER_TypeDef* TIMERx)`
- `void PWM_Init(TIMER_TypeDef* TIMERx, PWM_InitTypeDef* PWM_InitStruct)`
- `void PWM_StructInit(PWM_InitTypeDef* PWM_InitStruct)`
- `void PWM_Cmd(TIMER_TypeDef* TIMERx, FunctionalState NewState)`
- `void PWM_CtrlPWMOutput(TIMER_TypeDef* TIMERx, FunctionalState NewState)`

### Configuration Functions
- `void PWM_OC1FastConfig(TIMER_TypeDef* TIMERx, uint16_t PWM_OCFast)`
- `void PWM_OC2FastConfig(TIMER_TypeDef* TIMERx, uint16_t PWM_OCFast)`
- `void PWM_OC3FastConfig(TIMER_TypeDef* TIMERx, uint16_t PWM_OCFast)`
- `void PWM_OC4FastConfig(TIMER_TypeDef* TIMERx, uint16_t PWM_OCFast)`
- `void PWM_SetCompare1(TIMER_TypeDef* TIMERx, uint32_t Compare1)`
- `void PWM_SetCompare2(TIMER_TypeDef* TIMERx, uint32_t Compare2)`
- `void PWM_SetCompare3(TIMER_TypeDef* TIMERx, uint32_t Compare3)`
- `void PWM_SetCompare4(TIMER_TypeDef* TIMERx, uint32_t Compare4)`
- `void PWM_SetAutoreload(TIMER_TypeDef* TIMERx, uint32_t Autoreload)`
- `void PWM_SetPrescaler(TIMER_TypeDef* TIMERx, uint16_t Prescaler)`

## Usage Example

The provided example demonstrates:
1. PWM configuration for TIMER0 CH0
2. FreeRTOS task integration
3. Dynamic duty cycle adjustment for LED fading effect

```c
// Initialize PWM peripheral
PWM_InitTypeDef PWM_InitStructure;
PWM_InitStructure.PWM_Channel = PWM_CHANNEL_0;
PWM_InitStructure.PWM_Frequency = 1000;  // 1KHz
PWM_InitStructure.PWM_DutyCycle = 50;    // 50% duty cycle
PWM_InitStructure.PWM_CounterMode = PWM_COUNTERMODE_UP;
PWM_InitStructure.PWM_OCMode = PWM_OCMODE_PWM1;
PWM_InitStructure.PWM_OCPolarity = PWM_OCPOLARITY_HIGH;
PWM_InitStructure.PWM_OutputState = ENABLE;
PWM_Init(TIMER0, &PWM_InitStructure);

// Enable PWM
PWM_Cmd(TIMER0, ENABLE);
```

## FreeRTOS Integration

The PWM driver is designed to work with FreeRTOS:
1. All PWM functions are reentrant and can be called from tasks
2. Example provided with FreeRTOS task for dynamic PWM control
3. Proper delay handling using vTaskDelay()

## Configuration Considerations

1. Ensure GPIO pins are configured for alternate function push-pull mode
2. Enable the TIMER clock before initialization
3. Configure appropriate prescaler based on system clock and required PWM frequency
4. For advanced timers, configure complementary outputs if needed

## Performance Notes

1. Maximum PWM frequency: Up to 1MHz depending on system clock
2. Resolution: 16-bit counters provide high resolution
3. Multiple channels: Support for up to 4 channels per timer
4. Advanced features: Dead time insertion, break functionality for advanced timers

## Error Handling

The driver provides comprehensive error handling through:
1. Parameter validation using assert_param
2. Detailed error status reporting
3. Proper initialization and de-initialization functions