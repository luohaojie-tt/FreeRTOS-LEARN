# DAC Driver for GD32F103C8T6

## Overview

This DAC driver provides a complete interface for configuring and controlling the DAC peripherals on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **DAC Initialization**
   - Configurable trigger sources (software, timer, external)
   - Configurable wave generation (noise, triangle)
   - Configurable output buffer
   - Configurable LFSR mask and triangle amplitude

2. **DAC Control Functions**
   - Enable/disable DAC channels
   - Software trigger control
   - Wave generation control
   - Dual channel simultaneous control

3. **Data Management**
   - 12-bit data resolution
   - Multiple data alignment options (left, right)
   - Dual channel data setting
   - Data output value retrieval

4. **Advanced Features**
   - DMA support for high-speed data transfer
   - Noise and triangle wave generation
   - Configurable wave amplitude

## API Functions

### DAC Initialization
- `void DAC_DeInit(void)`
- `void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)`
- `void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)`
- `void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)`

### DAC Configuration
- `void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)`
- `void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)`
- `void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)`
- `void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)`

### Data Management
- `void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)`
- `void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)`
- `void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)`
- `uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)`

## Usage Example

The provided example demonstrates:
1. DAC configuration for channel 0
2. FreeRTOS task integration
3. Generation of a ramp waveform

```c
// Initialize DAC peripheral
DAC_InitTypeDef DAC_InitStructure;
DAC_InitStructure.DAC_Trigger = DAC_TRIGGER_NONE;
DAC_InitStructure.DAC_WaveGeneration = DAC_WAVEGENERATION_NONE;
DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUNMASK_BIT0;
DAC_InitStructure.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
DAC_Init(DAC_CHANNEL_0, &DAC_InitStructure);

// Enable DAC Channel
DAC_Cmd(DAC_CHANNEL_0, ENABLE);

// Set DAC output value
DAC_SetChannel1Data(DAC_ALIGN_12B_R, 2048);  // Set to mid-scale
```

## FreeRTOS Integration

The DAC driver is designed to work with FreeRTOS:
1. All DAC functions are reentrant and can be called from tasks
2. Example provided with FreeRTOS task for waveform generation
3. Proper delay handling using vTaskDelay()

## Configuration Considerations

1. Ensure GPIO pins are configured for analog mode
2. Enable the DAC clock before initialization
3. Configure appropriate trigger sources based on application requirements
4. For high-speed applications, consider using DMA

## Performance Notes

1. Maximum conversion rate: Up to 1Msps
2. 12-bit resolution output
3. Support for 2 independent channels
4. DMA support for high-throughput applications
5. Wave generation capabilities (noise and triangle)

## Error Handling

The driver provides comprehensive error handling through:
1. Parameter validation using assert_param
2. Detailed error status reporting
3. Proper initialization and de-initialization functions