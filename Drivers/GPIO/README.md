# GPIO Driver for GD32F103C8T6

## Overview

This GPIO driver provides a complete interface for configuring and controlling the GPIO pins on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **GPIO Initialization**
   - Configurable pin mode (input, output, alternate function, analog)
   - Configurable output speed (2MHz, 10MHz, 50MHz)
   - Support for all GPIO ports (GPIOA, GPIOB, GPIOC, GPIOD, GPIOE)

2. **GPIO Control Functions**
   - Set/reset individual pins
   - Read pin states
   - Toggle pin states
   - Write to entire port

3. **Advanced Features**
   - Pin remapping support
   - External interrupt configuration
   - Event output configuration
   - Pin lock configuration

## API Functions

### GPIO Initialization
- `void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)`
- `void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)`
- `void GPIO_DeInit(GPIO_TypeDef* GPIOx)`

### GPIO Control
- `void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
- `void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
- `void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)`
- `void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)`
- `uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
- `uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)`
- `uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
- `uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)`

### Advanced Features
- `void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)`
- `void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)`
- `void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)`
- `void GPIO_EventOutputCmd(FunctionalState NewState)`
- `void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`

## Usage Example

```c
// Initialize LED pins
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
GPIO_Init(GPIOC, &GPIO_InitStructure);

// Toggle LEDs in FreeRTOS task
while(1) {
    GPIO_WriteBit(GPIOC, GPIO_PIN_0, Bit_SET);
    vTaskDelay(500 / portTICK_RATE_MS);
    GPIO_WriteBit(GPIOC, GPIO_PIN_0, Bit_RESET);
    vTaskDelay(500 / portTICK_RATE_MS);
}
```

## FreeRTOS Integration

The GPIO driver is designed to work with FreeRTOS:
1. All GPIO functions are reentrant and can be called from tasks
2. No blocking operations in GPIO functions
3. Example provided with FreeRTOS tasks for LED control and button handling

## Pin Configuration

The driver supports all standard GPIO pin configurations:
- Input modes: Analog, Floating, Pull-up/Pull-down
- Output modes: Push-pull, Open-drain
- Alternate function modes: Push-pull, Open-drain
- Output speeds: 2MHz, 10MHz, 50MHz

## Notes

1. Remember to enable the GPIO clock before using any GPIO functions
2. For external interrupts, ensure AFIO clock is enabled
3. The driver follows the standard GD32 firmware library conventions for compatibility