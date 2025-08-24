# I2C Driver for GD32F103C8T6

## Overview

This I2C driver provides a complete interface for configuring and controlling the I2C peripherals on the GD32F103C8T6 microcontroller. The driver is designed to work seamlessly with FreeRTOS and follows the standard GD32 firmware library conventions.

## Features

1. **I2C Initialization**
   - Configurable master/slave mode
   - Configurable clock speed (standard mode up to 100kHz, fast mode up to 400kHz)
   - Configurable duty cycle for fast mode
   - Configurable own address (7-bit or 10-bit)
   - Acknowledgement enable/disable

2. **Data Transmission Functions**
   - Master transmitter mode
   - Slave transmitter mode
   - Single byte and burst data transmission
   - START and STOP condition generation

3. **Data Reception Functions**
   - Master receiver mode
   - Slave receiver mode
   - Single byte and burst data reception
   - Acknowledge management

4. **Advanced Features**
   - Dual addressing support for slave mode
   - General call address recognition
   - SMBus support
   - PEC (Packet Error Checking) support
   - Clock stretching control
   - DMA support
   - Interrupt-driven operations

5. **Error Handling and Status Monitoring**
   - Comprehensive flag and event checking
   - Error interrupt support
   - Software reset capability

## API Functions

### I2C Initialization
- `void I2C_DeInit(I2C_TypeDef* I2Cx)`
- `void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)`
- `void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)`
- `void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`

### Data Transmission
- `void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)`
- `void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)`

### Data Reception
- `uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)`

### Acknowledge Management
- `void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition)`

### Slave Addressing
- `void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address)`
- `void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`

### Status Monitoring
- `ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)`
- `uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)`
- `FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)`
- `void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)`

### Interrupt Management
- `void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)`
- `ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)`
- `void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)`

### Advanced Features
- `void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert)`
- `void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition)`
- `void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)`
- `void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)`
- `void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle)`
- `uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)`

## Usage Example

The provided example demonstrates:
1. Master transmitter and receiver modes
2. Slave transmitter and receiver modes
3. FreeRTOS task integration
4. Inter-task communication using queues

```c
// Initialize I2C peripheral
I2C_InitTypeDef I2C_InitStructure;
I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
I2C_InitStructure.I2C_OwnAddress1 = 0x20;
I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
I2C_InitStructure.I2C_ClockSpeed = 100000;
I2C_Init(I2C1, &I2C_InitStructure);

// Enable I2C peripheral
I2C_Cmd(I2C1, ENABLE);

// Master transmission
I2C_GenerateSTART(I2C1, ENABLE);
// ... wait for EV5
I2C_Send7bitAddress(I2C1, slave_address, I2C_Direction_Transmitter);
// ... wait for EV6
I2C_SendData(I2C1, data);
// ... wait for EV8_2
I2C_GenerateSTOP(I2C1, ENABLE);
```

## FreeRTOS Integration

The I2C driver is designed to work with FreeRTOS:
1. All I2C functions are reentrant and can be called from tasks
2. Example provided with FreeRTOS tasks for master and slave operations
3. Queue-based communication between master and slave tasks
4. Proper delay handling using vTaskDelay()

## Configuration Considerations

1. Ensure GPIO pins are configured for alternate function open-drain mode
2. Enable the I2C clock before initialization
3. Configure appropriate clock speed based on application requirements
4. For fast mode operation, ensure proper pull-up resistors on SCL and SDA lines
5. In multi-master systems, implement proper arbitration handling

## Performance Notes

1. Standard mode: Up to 100kHz
2. Fast mode: Up to 400kHz
3. Duty cycle configuration affects fast mode timing
4. Clock stretching can be enabled/disabled based on slave device requirements
5. DMA support available for high-throughput applications

## Error Handling

The driver provides comprehensive error handling through:
1. Flag-based status checking
2. Event-based status monitoring
3. Interrupt-driven error detection
4. Software reset capability for error recovery