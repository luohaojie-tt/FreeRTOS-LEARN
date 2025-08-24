/**
  ******************************************************************************
  * @file    spi_example.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-July-2021
  * @brief   SPI driver usage example
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
#include "gd32f10x_spi.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_MASTER_MODE                 1
#define SPI_SLAVE_MODE                  0

/* SPI communication mode */
#define SPI_MODE                        SPI_MASTER_MODE

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef  SPI_InitStructure;
uint8_t SPI_Master_Buffer_Tx[32] = {0x00};
uint8_t SPI_Master_Buffer_Rx[32] = {0x00};
uint8_t SPI_Slave_Buffer_Tx[32] = {0x00};
uint8_t SPI_Slave_Buffer_Rx[32] = {0x00};
uint32_t TxIdx = 0, RxIdx = 0;
uint8_t data = 0;

/* Private function prototypes -----------------------------------------------*/
void SPI_GPIO_Config(void);
void SPI_Config(void);
void SPI_Master_Task(void *pvParameters);
void SPI_Slave_Task(void *pvParameters);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the SPI GPIO ports.
  * @param  None
  * @retval None
  */
void SPI_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

#if SPI_MODE == SPI_MASTER_MODE
    /* Enable SPI1 GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
    
    /* Configure SPI1 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure PA4 as SPI1 NSS output */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_PIN_4);
#else
    /* Enable SPI1 GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    
    /* Configure SPI2 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB12 as SPI2 NSS input */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}

/**
  * @brief  Configure the SPI interface.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
#if SPI_MODE == SPI_MASTER_MODE
    /* SPI1 configuration */
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
    
    /* Enable SPI1 */
    SPI_Cmd(SPI1, ENABLE);
#else
    /* SPI2 configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);
    
    /* Enable SPI2 */
    SPI_Cmd(SPI2, ENABLE);
#endif
}

/**
  * @brief  SPI Master Task.
  * @param  pvParameters: pointer that will be passed to the task
  * @retval None
  */
void SPI_Master_Task(void *pvParameters)
{
    /* Initialize data */
    for(TxIdx = 0; TxIdx < 32; TxIdx++)
    {
        SPI_Master_Buffer_Tx[TxIdx] = TxIdx;
    }
    
    TxIdx = 0;
    RxIdx = 0;
    
    while(1)
    {
#if SPI_MODE == SPI_MASTER_MODE
        /* Wait for SPI1 Tx buffer empty */
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        
        /* Send data */
        SPI_I2S_SendData(SPI1, SPI_Master_Buffer_Tx[TxIdx++]);
        
        /* Wait for SPI1 Rx buffer not empty */
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        
        /* Read data */
        SPI_Slave_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
        
        /* Wait for SPI1 Busy flag */
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        
        if(TxIdx == 32)
        {
            TxIdx = 0;
        }
        
        if(RxIdx == 32)
        {
            RxIdx = 0;
        }
        
        vTaskDelay(100 / portTICK_RATE_MS);
#endif
    }
}

/**
  * @brief  SPI Slave Task.
  * @param  pvParameters: pointer that will be passed to the task
  * @retval None
  */
void SPI_Slave_Task(void *pvParameters)
{
    /* Initialize data */
    for(TxIdx = 0; TxIdx < 32; TxIdx++)
    {
        SPI_Slave_Buffer_Tx[TxIdx] = 0xAA;
    }
    
    TxIdx = 0;
    RxIdx = 0;
    
    while(1)
    {
#if SPI_MODE == SPI_SLAVE_MODE
        /* Wait for SPI2 Tx buffer empty */
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
        
        /* Send data */
        SPI_I2S_SendData(SPI2, SPI_Slave_Buffer_Tx[TxIdx++]);
        
        /* Wait for SPI2 Rx buffer not empty */
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        
        /* Read data */
        SPI_Master_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
        
        /* Wait for SPI2 Busy flag */
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);
        
        if(TxIdx == 32)
        {
            TxIdx = 0;
        }
        
        if(RxIdx == 32)
        {
            RxIdx = 0;
        }
        
        vTaskDelay(100 / portTICK_RATE_MS);
#endif
    }
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure SPI GPIO ports */
    SPI_GPIO_Config();
    
    /* Configure SPI interface */
    SPI_Config();
    
    /* Create tasks */
#if SPI_MODE == SPI_MASTER_MODE
    xTaskCreate(SPI_Master_Task, "SPI_Master_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
#else
    xTaskCreate(SPI_Slave_Task, "SPI_Slave_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
#endif
    
    /* Start the scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    while(1);
}