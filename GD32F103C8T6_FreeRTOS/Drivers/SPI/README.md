# SPI Driver for GD32F103C8T6

## Overview

This SPI driver provides a complete interface for configuring and controlling the SPI peripherals on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **SPI Initialization**
   - Configurable master/slave mode
   - Configurable clock polarity (CPOL) and clock phase (CPHA)
   - Configurable data size (8-bit or 16-bit)
   - Configurable baud rate prescaler
   - Configurable NSS (Slave Select) management (hardware or software)
   - Configurable data transfer direction (MSB or LSB first)

2. **Data Transmission Functions**
   - Single and continuous data transmission
   - Blocking and non-blocking transmission modes
   - Support for 8-bit and 16-bit data frames

3. **Data Reception Functions**
   - Single and continuous data reception
   - Blocking and non-blocking reception modes
   - Support for 8-bit and 16-bit data frames

4. **Advanced Features**
   - CRC calculation and error detection
   - DMA support for high-speed data transfer
   - Interrupt-driven operations with comprehensive flag and interrupt management
   - Bidirectional data transfer mode
   - SS output enable/disable for master mode

5. **I2S Support**
   - Support for I2S protocol configuration
   - Configurable audio frequency, standard, and data format
   - Master/slave transmitter/receiver modes
   - MCLK output enable/disable

## API Functions

### SPI Initialization
- `void SPI_I2S_DeInit(SPI_TypeDef* SPIx)`
- `void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)`
- `void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)`
- `void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)`
- `void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)`
- `void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)`
- `void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)`

### Data Transmission and Reception
- `void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data)`
- `uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)`

### Configuration Functions
- `void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)`
- `void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)`
- `void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)`
- `void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)`

### CRC Functions
- `void SPI_TransmitCRC(SPI_TypeDef* SPIx)`
- `void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)`
- `uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)`
- `uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)`

### DMA and Interrupt Management
- `void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)`
- `void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)`

### Status Monitoring
- `FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)`
- `void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)`
- `ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)`
- `void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)`

## Usage Example

The provided example demonstrates:
1. SPI master mode operation
2. SPI slave mode operation
3. FreeRTOS task integration
4. Data transmission and reception between master and slave

```c
// Initialize SPI peripheral in master mode
SPI_InitTypeDef SPI_InitStructure;
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStructure.SPI_CRCPolynomial = 7;
SPI_Init(SPI1, &SPI_InitStructure);

// Enable SPI peripheral
SPI_Cmd(SPI1, ENABLE);

// Transmit data
SPI_I2S_SendData(SPI1, data);

// Receive data
data = SPI_I2S_ReceiveData(SPI1);
```

## FreeRTOS Integration

The SPI driver is designed to work with FreeRTOS:
1. All SPI functions are reentrant and can be called from tasks
2. Example provided with FreeRTOS tasks for SPI master and slave operations
3. Proper delay handling using vTaskDelay()

## Configuration Considerations

1. Ensure GPIO pins are configured for alternate function push-pull mode
2. Enable the SPI clock before initialization
3. Configure appropriate baud rate prescaler based on system clock and required SPI clock speed
4. For master mode, ensure NSS is properly managed (hardware or software)
5. In multi-master systems, implement proper arbitration handling

## Performance Notes

1. Maximum SPI clock frequency: Up to fPCLK/2
2. Baud rate prescaler values: 2, 4, 8, 16, 32, 64, 128, 256
3. Data transfer rates up to several Mbps depending on configuration
4. DMA support available for high-throughput applications
5. Interrupt-driven operations for efficient CPU utilization

## Error Handling

The driver provides comprehensive error handling through:
1. CRC calculation and error detection
2. Flag-based status checking
3. Interrupt-driven error detection
4. Detailed error status reporting