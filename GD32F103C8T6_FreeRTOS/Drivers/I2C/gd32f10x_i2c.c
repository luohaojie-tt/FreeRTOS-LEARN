/**
  ******************************************************************************
  * @file    gd32f10x_i2c.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    14-July-2021
  * @brief   This file provides all the I2C firmware functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2021 GIGADEVICE
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_i2c.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C 
  * @brief I2C driver modules
  * @{
  */ 

/** @defgroup I2C_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Defines
  * @{
  */

/* I2C CTLR1_I2CEN mask */
#define CTLR1_I2CEN_SET             ((uint16_t)0x0001)
#define CTLR1_I2CEN_RESET           ((uint16_t)0xFFFE)

/* I2C CTLR1_GENSTA mask */
#define CTLR1_GENSTA_SET            ((uint16_t)0x0100)
#define CTLR1_GENSTA_RESET          ((uint16_t)0xFEFF)

/* I2C CTLR1_GENSTP mask */
#define CTLR1_GENSTP_SET            ((uint16_t)0x0200)
#define CTLR1_GENSTP_RESET          ((uint16_t)0xFDFF)

/* I2C CTLR1_ACKEN mask */
#define CTLR1_ACKEN_SET             ((uint16_t)0x0400)
#define CTLR1_ACKEN_RESET           ((uint16_t)0xFBFF)

/* I2C CTLR1_POAP mask */
#define CTLR1_POAP_SET              ((uint16_t)0x0800)
#define CTLR1_POAP_RESET            ((uint16_t)0xF7FF)

/* I2C CTLR1_PECTRANS mask */
#define CTLR1_PECTRANS_SET          ((uint16_t)0x1000)
#define CTLR1_PECTRANS_RESET        ((uint16_t)0xEFFF)

/* I2C CTLR1_SALT mask */
#define CTLR1_SALT_SET              ((uint16_t)0x2000)
#define CTLR1_SALT_RESET            ((uint16_t)0xDFFF)

/* I2C CTLR1_SMBRST mask */
#define CTLR1_SMBRST_SET            ((uint16_t)0x4000)
#define CTLR1_SMBRST_RESET          ((uint16_t)0xBFFF)

/* I2C CTLR1_SMBEN mask */
#define CTLR1_SMBEN_SET             ((uint16_t)0x8000)
#define CTLR1_SMBEN_RESET           ((uint16_t)0x7FFF)

/* I2C CTLR2_DMAON mask */
#define CTLR2_DMAON_SET             ((uint16_t)0x0800)
#define CTLR2_DMAON_RESET           ((uint16_t)0xF7FF)

/* I2C CTLR2_DMALST mask */
#define CTLR2_DMALST_SET            ((uint16_t)0x1000)
#define CTLR2_DMALST_RESET          ((uint16_t)0xEFFF)

/* I2C AR1_ADDMSK mask */
#define AR1_ADDMSK                  ((uint16_t)0x7FFF)

/* I2C AR2_DUADEN mask */
#define AR2_DUADEN_SET              ((uint16_t)0x0001)
#define AR2_DUADEN_RESET            ((uint16_t)0xFFFE)

/* I2C AR2_ADD2 mask */
#define AR2_ADD2                    ((uint16_t)0x00FE)

/* I2C CKCFGR_CLKC mask */
#define CKCFGR_CLKC                 ((uint16_t)0x0FFF)

/* I2C CKCFGR_DTCY mask */
#define CKCFGR_DTCY_SET             ((uint16_t)0x4000)
#define CKCFGR_DTCY_RESET           ((uint16_t)0xBFFF)

/* I2C CKCFGR_FMSM mask */
#define CKCFGR_FMSM_SET             ((uint16_t)0x8000)
#define CKCFGR_FMSM_RESET           ((uint16_t)0x7FFF)

/* I2C STR1_FLAG mask */
#define STR1_FLAG_MASK              ((uint32_t)0x00FFFFFF)

/* I2C STR2_FLAG mask */
#define STR2_FLAG_MASK              ((uint32_t)0x00FFFFFF)

/**
  * @}
  */

/** @defgroup I2C_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  if (I2Cx == I2C1)
  {
    /* Enable I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else
  {
    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified 
  *   parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *   contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint16_t tmpreg = 0, freqrange = 0;
  uint16_t result = 0x04;
  uint32_t pclk1 = 8000000;
  RCC_ClocksTypeDef  rcc_clocks;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_InitStruct->I2C_DutyCycle));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

/*---------------------------- I2Cx CTLR2 Configuration ------------------------*/
  /* Get the I2Cx CTLR2 value */
  tmpreg = I2Cx->CTLR2;
  /* Clear frequency FREQ[5:0] bits */
  tmpreg &= (uint16_t)~((uint16_t)I2C_CTLR2_FREQ);
  /* Get pclk1 frequency value */
  RCC_GetClocksFreq(&rcc_clocks);
  pclk1 = rcc_clocks.PCLK1_Frequency;
  /* Set frequency bits depending on pclk1 value */
  freqrange = (uint16_t)(pclk1 / 1000000);
  tmpreg |= freqrange;
  /* Write to I2Cx CTLR2 */
  I2Cx->CTLR2 = tmpreg;

/*---------------------------- I2Cx CKCFGR Configuration -----------------------*/
/* Configure the clock control registers value*/
  /* If I2C Clock frequency is lower than 100Khz */
  if (I2C_InitStruct->I2C_ClockSpeed <= 100000)
  {
    /* Standard mode speed calculation */
    result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));
    /* If the result of CCR calculation is equal to 0 */
    if (result == 0)
    {
      /* Set minimum allowed value */
      result = 0x0004;  
    }
    /* Set speed value for standard mode */
    tmpreg = result;   
    /* Write to I2Cx CKCFGR */
    I2Cx->CKCFGR = tmpreg;
    /* Set the maximum rise time for standard mode */
    I2Cx->RTR = freqrange + 1; 
  }
  /* If I2C Clock frequency is higher than 100Khz */
  else
  {
    /* Fast mode speed calculation */
    if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2)
    {
      /* Fast mode speed calculation: Tlow/Thigh = 2 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
    }
    else /* I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9 */
    {
      /* Fast mode speed calculation: Tlow/Thigh = 16/9 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
      /* Set DTCY bit */
      result |= I2C_DutyCycle_16_9;
    }

    /* If the result of CCR calculation is equal to 0 */
    if ((result & CKCFGR_CLKC) == 0)
    {
      /* Set minimum allowed value */
      result |= (uint16_t)0x0001;  
    }
    /* Set speed value and set F/S bit for fast mode */
    tmpreg = (uint16_t)(result | CKCFGR_FMSM_SET);
    /* Write to I2Cx CKCFGR */
    I2Cx->CKCFGR = tmpreg;
    /* Set the maximum rise time for fast mode */
    I2Cx->RTR = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);  
  }

/*---------------------------- I2Cx CTLR1 Configuration ------------------------*/
  /* Get the I2Cx CTLR1 value */
  tmpreg = I2Cx->CTLR1;
  /* Clear ACKEN, POAP, SMBTYPE, SMBUS, ARPEN, PECTRANS, SALT, GCEN and I2CEN bits */
  tmpreg &= CTLR1_CLEAR_MASK;
  /* Configure I2Cx: mode and acknowledgement */
  /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
  /* Set ACKEN bit according to I2C_Ack value */
  tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  /* Write to I2Cx CTLR1 */
  I2Cx->CTLR1 = tmpreg;

/*---------------------------- I2Cx AR1 Configuration ---------------------------*/
  /* Get the I2Cx AR1 value */
  tmpreg = I2Cx->AR1;
  /* Clear ADDMSK bit [7:1] */
  tmpreg &= AR1_ADDMSK;
  /* Set I2Cx Own Address1 */
  tmpreg |= (uint16_t)((uint16_t)I2C_InitStruct->I2C_OwnAddress1 & (uint16_t)0x00FE);
  /* Write to I2Cx AR1 */
  I2Cx->AR1 = tmpreg;

/*---------------------------- I2Cx AR2 Configuration ---------------------------*/
  /* Set I2Cx Own Address2 */
  I2Cx->AR2 = (uint16_t)((uint16_t)I2C_InitStruct->I2C_OwnAddress2 & (uint16_t)0x00FE);
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
/*---------------- Reset I2C init structure parameters values ----------------*/
  /* Initialize the I2C_ClockSpeed member */
  I2C_InitStruct->I2C_ClockSpeed = 5000;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_DutyCycle member */
  I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CTLR1 |= CTLR1_I2CEN_SET;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CTLR1 &= CTLR1_I2CEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified I2C DMA requests.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CTLR2 |= CTLR2_DMAON_SET;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CTLR2 &= CTLR2_DMAON_RESET;
  }
}

/**
  * @brief  Specifies if the next DMA transfer will be the last one.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C DMA last transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Next DMA transfer is the last transfer */
    I2Cx->CTLR2 |= CTLR2_DMALST_SET;
  }
  else
  {
    /* Next DMA transfer is not the last transfer */
    I2Cx->CTLR2 &= CTLR2_DMALST_RESET;
  }
}

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CTLR1 |= CTLR1_GENSTA_SET;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CTLR1 &= CTLR1_GENSTA_RESET;
  }
}

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CTLR1 |= CTLR1_GENSTP_SET;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CTLR1 &= CTLR1_GENSTP_RESET;
  }
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CTLR1 |= CTLR1_ACKEN_SET;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CTLR1 &= CTLR1_ACKEN_RESET;
  }
}

/**
  * @brief  Configures the specified I2C own address2.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address)
{
  uint16_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->AR2;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= AR2_ADD2;

  /* Set I2Cx Own address2 */
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

  /* Store the new register value */
  I2Cx->AR2 = tmpreg;
}

/**
  * @brief  Enables or disables the specified I2C dual addressing mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C dual addressing mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    I2Cx->AR2 |= AR2_DUADEN_SET;
  }
  else
  {
    /* Disable dual addressing mode */
    I2Cx->AR2 &= AR2_DUADEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified I2C general call feature.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C General call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable general call */
    I2Cx->CTLR1 |= CTLR1_GCEN_SET;
  }
  else
  {
    /* Disable general call */
    I2Cx->CTLR1 &= CTLR1_GCEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_BUF: Buffer interrupt mask
  *     @arg I2C_IT_EVT: Event interrupt mask
  *     @arg I2C_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CTLR2 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CTLR2 &= (uint16_t)~I2C_IT;
  }
}

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Write in the DR register the data to be sent */
  I2Cx->DTR = Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->DTR;
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a
  *   Transmitter or a Receiver. This parameter can be one of the following values
  *     @arg I2C_Direction_Transmitter: Transmitter mode
  *     @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= I2C_OAR1_ADD0_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= I2C_OAR1_ADD0_Reset;
  }
  /* Send the address */
  I2Cx->DTR = Address;
}

/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_Register: specifies the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_Register_CTLR1:  CTLR1 register.
  *     @arg I2C_Register_CTLR2:   CTLR2 register.
  *     @arg I2C_Register_AR1:   AR1 register.
  *     @arg I2C_Register_AR2:   AR2 register.
  *     @arg I2C_Register_DTR:   DTR register.
  *     @arg I2C_Register_STR1: STR1 register.
  *     @arg I2C_Register_STR2: STR2 register.
  *     @arg I2C_Register_CKCFGR: CKCFGR register.
  *     @arg I2C_Register_RTR:  RTR register.
  * @retval The value of the read register.
  */
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint16_t *) tmp);
}

/**
  * @brief  Enables or disables the specified I2C software reset.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C software reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->CTLR1 |= CTLR1_SMBRST_SET;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->CTLR1 &= CTLR1_SMBRST_RESET;
  }
}

/**
  * @brief  Selects the specified I2C NACK position in master receiver mode.
  *         This function is useful in I2C Master Receiver mode when the number
  *         of data to be received is equal to 2. In this case, this function 
  *         should be called (with parameter I2C_NACKPosition_Next) before data 
  *         reception starts,as described in the 2-byte reception procedure 
  *         recommended in Reference Manual in Section: Master receiver.                
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_NACKPosition: specifies the NACK position. 
  *   This parameter can be one of the following values:
  *     @arg I2C_NACKPosition_Next: indicates that the next byte will be the last
  *          received byte.  
  *     @arg I2C_NACKPosition_Current: indicates that current byte is the last 
  *          received byte.
  *            
  * @note    This function configures the same bit (POS) as I2C_PECPositionConfig() 
  *          but is intended to be used in I2C mode while I2C_PECPositionConfig() 
  *          is intended to used in SMBUS mode. 
  *            
  * @retval None
  */
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));
  
  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    /* Next byte in shift register is the last received byte */
    I2Cx->CTLR1 |= I2C_NACKPosition_Next;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    I2Cx->CTLR1 &= I2C_NACKPosition_Current;
  }
}

/**
  * @brief  Drives the SMBusAlert pin high or low for the specified I2C.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_SMBusAlert: specifies SMBAlert pin level. 
  *   This parameter can be one of the following values:
  *     @arg I2C_SMBusAlert_Low: SMBAlert pin driven low
  *     @arg I2C_SMBusAlert_High: SMBAlert pin driven high
  * @retval None
  */
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));
  if (I2C_SMBusAlert == I2C_SMBusAlert_Low)
  {
    /* Drive the SMBusAlert pin Low */
    I2Cx->CTLR1 |= I2C_SMBusAlert_Low;
  }
  else
  {
    /* Drive the SMBusAlert pin High  */
    I2Cx->CTLR1 &= I2C_SMBusAlert_High;
  }
}

/**
  * @brief  Enables or disables the specified I2C PEC transfer.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C PEC transmission.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC transmission */
    I2Cx->CTLR1 |= CTLR1_PECTRANS_SET;
  }
  else
  {
    /* Disable the selected I2C PEC transmission */
    I2Cx->CTLR1 &= CTLR1_PECTRANS_RESET;
  }
}

/**
  * @brief  Selects the specified I2C PEC position.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_PECPosition: specifies the PEC position. 
  *   This parameter can be one of the following values:
  *     @arg I2C_PECPosition_Next: indicates that the next byte is PEC
  *     @arg I2C_PECPosition_Current: indicates that current byte is PEC
  *       
  * @note    This function configures the same bit (POS) as I2C_NACKPositionConfig()
  *          but is intended to be used in SMBUS mode while I2C_NACKPositionConfig() 
  *          is intended to used in I2C mode.
  *               
  * @retval None
  */
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));
  if (I2C_PECPosition == I2C_PECPosition_Next)
  {
    /* Next byte in shift register is PEC */
    I2Cx->CTLR1 |= I2C_PECPosition_Next;
  }
  else
  {
    /* Current byte in shift register is PEC */
    I2Cx->CTLR1 &= I2C_PECPosition_Current;
  }
}

/**
  * @brief  Enables or disables the PEC value calculation of the transferred bytes.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC calculation */
    I2Cx->CTLR1 |= CTLR1_SALT_SET;
  }
  else
  {
    /* Disable the selected I2C PEC calculation */
    I2Cx->CTLR1 &= CTLR1_SALT_RESET;
  }
}

/**
  * @brief  Returns the PEC value for the specified I2C.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The PEC value.
  */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the selected I2C PEC value */
  return ((I2Cx->STR2) >> 8);
}

/**
  * @brief  Enables or disables the specified I2C ARP.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx ARP. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C ARP */
    I2Cx->CTLR1 |= CTLR1_ARPEN_SET;
  }
  else
  {
    /* Disable the selected I2C ARP */
    I2Cx->CTLR1 &= CTLR1_ARPEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified I2C Clock stretching.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Clock stretching.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState == DISABLE)
  {
    /* Enable the selected I2C Clock stretching */
    I2Cx->CTLR1 |= CTLR1_SALT_SET;
  }
  else
  {
    /* Disable the selected I2C Clock stretching */
    I2Cx->CTLR1 &= CTLR1_SALT_RESET;
  }
}

/**
  * @brief  Selects the specified I2C fast mode duty cycle.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_DutyCycle: specifies the fast mode duty cycle.
  *   This parameter can be one of the following values:
  *     @arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
  *     @arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @retval None
  */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));
  if (I2C_DutyCycle != I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh=2 */
    I2Cx->CKCFGR &= I2C_DutyCycle_2;
  }
  else
  {
    /* I2C fast mode Tlow/Thigh=16/9 */
    I2Cx->CKCFGR |= I2C_DutyCycle_16_9;
  }
}

/**
  * @brief  Checks whether the last I2C Event is equal to the one passed
  *   as parameter.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_EVENT: specifies the event to be checked. 
  *   This parameter can be one of the following values:
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1
  *     @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1
  *     @arg I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUMODF)     : EV2
  *     @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUMODF)  : EV3
  *     @arg I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2
  *     @arg I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4
  *     @arg I2C_EVENT_MASTER_MODE_SELECT                          : EV5
  *     @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6     
  *     @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6
  *     @arg I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2
  *     @arg I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9
  *     
  * @note: For detailed description of Events, please refer to section 
  *    I2C_Events in gd32f10x_i2c.h file.
  *    
  * @retval An ErrorStatus enumeration value:
  * - SUCCESS: Last event is equal to the I2C_EVENT
  * - ERROR: Last event is different from the I2C_EVENT
  */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_EVENT(I2C_EVENT));

  /* Read the I2Cx status register */
  flag1 = I2Cx->STR1;
  flag2 = I2Cx->STR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & STR1_FLAG_MASK;

  /* Check whether the last event contains the I2C_EVENT */
  if ((lastevent & I2C_EVENT) == I2C_EVENT)
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }
  /* Return status */
  return status;
}

/**
  * @brief  Returns the last I2Cx Event.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  *     
  * @note: For detailed description of Events, please refer to section 
  *    I2C_Events in gd32f10x_i2c.h file.
  *    
  * @retval The last event
  */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read the I2Cx status register */
  flag1 = I2Cx->STR1;
  flag2 = I2Cx->STR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & STR1_FLAG_MASK;

  /* Return status */
  return lastevent;
}

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_DUMODF: Dual flag (Slave mode)
  *     @arg I2C_FLAG_HSTSMB: SMBus host header (Slave mode)
  *     @arg I2C_FLAG_DEFSMB: SMBus default header (Slave mode)
  *     @arg I2C_FLAG_RXGC: General call header flag (Slave mode)
  *     @arg I2C_FLAG_TRS: Transmitter/Receiver flag
  *     @arg I2C_FLAG_I2CBSY: Bus busy flag
  *     @arg I2C_FLAG_MASTER: Master/Slave flag
  *     @arg I2C_FLAG_SMBALTS: SMBus Alert flag
  *     @arg I2C_FLAG_SMBALT: SMBus Host Alert flag
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AF: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BERR: Bus error flag
  *     @arg I2C_FLAG_TXE: Data register empty flag (Transmitter)
  *     @arg I2C_FLAG_RXNE: Data register not empty (Receiver) flag
  *     @arg I2C_FLAG_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
  *     @arg I2C_FLAG_BTF: Byte transfer finished flag
  *     @arg I2C_FLAG_ADDR: Address sent flag (Master mode) "ADSL"
  *   Address matched flag (Slave mode)"ENDA"
  *     @arg I2C_FLAG_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Get the I2Cx peripheral base address */
  i2cxbase = (uint32_t)I2Cx;
  
  /* Read flag register index */
  i2creg = I2C_FLAG >> 28;
  
  /* Get bit[23:0] of the flag */
  I2C_FLAG &= STR1_FLAG_MASK;
  
  if(i2creg != 0)
  {
    /* Get the I2Cx SR2 value */
    i2cxbase += 0x18;
  }
  else
  {
    /* Get the I2Cx SR1 value */
    i2cxbase += 0x14;
  }
  
  if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  
  /* Return the I2C_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_SMBALT: SMBus Host Alert flag
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AF: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BERR: Bus error flag
  *   
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation 
  *     to I2C_STR1 register (I2C_GetFlagStatus()) followed by a write operation 
  *     to I2C_CTLR1 register (I2C_Cmd() to enable the peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read 
  *     operation to I2C_STR1 register (I2C_GetFlagStatus()) followed by writing 
  *     the second byte of the address in DR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
  *     operation to I2C_STR1 register (I2C_GetFlagStatus()) followed by a 
  *     read/write to I2C_DTR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to 
  *     I2C_STR1 register (I2C_GetFlagStatus()) followed by a read operation to 
  *     I2C_STR2 register ((void)(I2Cx->STR2)).
  *   - SB (Start Bit) is cleared software sequence: a read operation to I2C_STR1
  *     register (I2C_GetFlagStatus()) followed by a write operation to I2C_DTR
  *     register  (I2C_SendData()).
  * @retval None
  */
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
  /* Get the I2C flag position */
  flagpos = I2C_FLAG & STR1_FLAG_MASK;
  /* Clear the selected I2C flag */
  I2Cx->STR1 = (uint16_t)~flagpos;
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg I2C_IT_SMBALERT: SMBus Alert flag
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_IT_PECERR: PEC error in reception flag
  *     @arg I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_IT_AF: Acknowledge failure flag
  *     @arg I2C_IT_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_IT_BERR: Bus error flag
  *     @arg I2C_IT_TXE: Data register empty flag (Transmitter)
  *     @arg I2C_IT_RXNE: Data register not empty (Receiver) flag
  *     @arg I2C_IT_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_IT_ADD10: 10-bit header sent flag (Master mode)
  *     @arg I2C_IT_BTF: Byte transfer finished flag
  *     @arg I2C_IT_ADDR: Address sent flag (Master mode) "ADSL"
  *                       Address matched flag (Slave mode)"ENDA"
  *     @arg I2C_IT_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint32_t)(((I2C_IT & ITEN_MASK) >> 16) & (I2Cx->CTLR2)) ;
  
  /* Get bit[23:0] of the flag */
  I2C_IT &= STR1_FLAG_MASK;

  /* Check the status of the specified I2C flag */
  if (((I2Cx->STR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }
  /* Return the I2C_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the I2Cx interrupt pending bits.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt pending bit to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_SMBALERT: SMBus Alert interrupt
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow error interrupt
  *     @arg I2C_IT_PECERR: PEC error in reception  interrupt
  *     @arg I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode)
  *     @arg I2C_IT_AF: Acknowledge failure interrupt
  *     @arg I2C_IT_ARLO: Arbitration lost interrupt (Master mode)
  *     @arg I2C_IT_BERR: Bus error interrupt
  *   
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation 
  *     to I2C_STR1 register (I2C_GetITStatus()) followed by a write operation to 
  *     I2C_CTLR1 register (I2C_Cmd() to enable the peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read 
  *     operation to I2C_STR1 register (I2C_GetITStatus()) followed by writing 
  *     the second byte of the address in I2C_DTR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
  *     operation to I2C_STR1 register (I2C_GetITStatus()) followed by a 
  *     read/write to I2C_DTR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to 
  *     I2C_STR1 register (I2C_GetITStatus()) followed by a read operation to 
  *     I2C_STR2 register ((void)(I2Cx->STR2)).
  *   - SB (Start Bit) is cleared by software sequence: a read operation to 
  *     I2C_STR1 register (I2C_GetITStatus()) followed by a write operation to 
  *     I2C_DTR register (I2C_SendData()).
  * @retval None
  */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));

  /* Get the I2C flag position */
  flagpos = I2C_IT & STR1_FLAG_MASK;

  /* Clear the selected I2C flag */
  I2Cx->STR1 = (uint16_t)~flagpos;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2021 GIGADEVICE *****END OF FILE****/