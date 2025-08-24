# ADC Driver for GD32F103C8T6

## Overview

This ADC driver provides a complete interface for configuring and controlling the ADC peripherals on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **ADC Initialization**
   - Configurable ADC mode (independent or dual mode)
   - Configurable scan conversion mode
   - Configurable continuous conversion mode
   - Configurable external trigger sources
   - Configurable data alignment (left or right)
   - Configurable number of channels

2. **ADC Control Functions**
   - Enable/disable ADC peripheral
   - Start/stop ADC conversion
   - Configure regular and injected channels
   - Set sample times for channels
   - Configure conversion sequences

3. **Advanced Features**
   - DMA support for high-speed data transfer
   - Interrupt-driven operations
   - Analog watchdog for monitoring voltage levels
   - Temperature sensor and Vrefint channel support
   - Calibration functions

4. **Data Management**
   - Get conversion results for regular channels
   - Get conversion results for injected channels
   - Dual mode conversion value retrieval

## API Functions

### ADC Initialization
- `void ADC_DeInit(ADC_TypeDef* ADCx)`
- `void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)`
- `void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)`
- `void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)`

### ADC Configuration
- `void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)`
- `void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)`
- `void ADC_ResetCalibration(ADC_TypeDef* ADCx)`
- `FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx)`
- `void ADC_StartCalibration(ADC_TypeDef* ADCx)`
- `FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)`

### Conversion Control
- `void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)`
- `FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)`
- `void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)`
- `void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)`

### Data Retrieval
- `uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)`
- `uint32_t ADC_GetDualModeConversionValue(void)`

### Injected Channel Functions
- `void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)`
- `void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length)`
- `void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)`
- `uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel)`

### Analog Watchdog
- `void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog)`
- `void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold)`
- `void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)`

### Special Functions
- `void ADC_TempSensorVrefintCmd(FunctionalState NewState)`
- `FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)`
- `void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)`
- `ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT)`
- `void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT)`

## Usage Example

The provided example demonstrates:
1. ADC configuration for single channel conversion
2. FreeRTOS task integration
3. Periodic ADC value reading and reporting

```c
// Initialize ADC peripheral
ADC_InitTypeDef ADC_InitStructure;
ADC_InitStructure.ADC_Mode = ADC_MODE_INDEPENDENT;
ADC_InitStructure.ADC_ScanConvMode = DISABLE;
ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
ADC_InitStructure.ADC_ExternalTrigConv = ADC_EXTERNALTRIGCONV_SOFTWARE;
ADC_InitStructure.ADC_DataAlign = ADC_DATAALIGN_RIGHT;
ADC_InitStructure.ADC_NbrOfChannel = 1;
ADC_Init(ADC0, &ADC_InitStructure);

// Configure ADC channel
ADC_RegularChannelConfig(ADC0, ADC_CHANNEL_0, 1, ADC_SAMPLETIME_239POINT5);

// Enable ADC
ADC_Cmd(ADC0, ENABLE);
```

## FreeRTOS Integration

The ADC driver is designed to work with FreeRTOS:
1. All ADC functions are reentrant and can be called from tasks
2. Example provided with FreeRTOS task for periodic ADC readings
3. Proper delay handling using vTaskDelay()

## Configuration Considerations

1. Ensure GPIO pins are configured for analog input mode
2. Enable the ADC clock before initialization
3. Perform ADC calibration after enabling the ADC
4. Configure appropriate sample times based on signal characteristics
5. For high-speed applications, consider using DMA

## Performance Notes

1. Maximum conversion rate: Up to 1Msps
2. 12-bit resolution conversion
3. Support for up to 18 channels
4. Dual mode for simultaneous sampling
5. DMA support for high-throughput applications

## Error Handling

The driver provides comprehensive error handling through:
1. Parameter validation using assert_param
2. Calibration status checking
3. Flag-based status monitoring
4. Interrupt-driven error detection
5. Detailed error status reporting