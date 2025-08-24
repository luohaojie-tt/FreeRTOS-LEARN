/**
  ******************************************************************************
  * @file    i2c_example.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-July-2021
  * @brief   I2C driver usage example
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
#include "gd32f10x_gpio.h"
#include "gd32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_SPEED                       100000
#define I2C_SLAVE_ADDRESS7              0x20

#define I2C_MASTER_WRITE_BUFFER_SIZE    10
#define I2C_MASTER_READ_BUFFER_SIZE     10
#define I2C_SLAVE_WRITE_BUFFER_SIZE     10
#define I2C_SLAVE_READ_BUFFER_SIZE      10

#define I2C_MASTER_WRITE_TASK_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define I2C_MASTER_READ_TASK_PRIORITY   ( tskIDLE_PRIORITY + 1 )
#define I2C_SLAVE_TASK_PRIORITY         ( tskIDLE_PRIORITY + 1 )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_InitTypeDef  I2C_InitStructure;
uint8_t I2C_MasterWriteBuffer[I2C_MASTER_WRITE_BUFFER_SIZE] = {0x55, 0xAA, 0x33, 0xCC, 0x11, 0xEE, 0x22, 0xDD, 0x44, 0xBB};
uint8_t I2C_MasterReadBuffer[I2C_MASTER_READ_BUFFER_SIZE] = {0x00};
uint8_t I2C_SlaveWriteBuffer[I2C_SLAVE_WRITE_BUFFER_SIZE] = {0x00};
uint8_t I2C_SlaveReadBuffer[I2C_SLAVE_READ_BUFFER_SIZE] = {0x55, 0xAA, 0x33, 0xCC, 0x11, 0xEE, 0x22, 0xDD, 0x44, 0xBB};

uint32_t I2C_MasterWriteIndex = 0;
uint32_t I2C_MasterReadIndex = 0;
uint32_t I2C_SlaveWriteIndex = 0;
uint32_t I2C_SlaveReadIndex = 0;

xQueueHandle xI2CQueue;

/* Private function prototypes -----------------------------------------------*/
void I2C_GPIO_Config(void);
void I2C_Config(void);
void I2C_MasterWriteTask(void *pvParameters);
void I2C_MasterReadTask(void *pvParameters);
void I2C_SlaveTask(void *pvParameters);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the I2C GPIO ports.
  * @param  None
  * @retval None
  */
void I2C_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIOB clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* Configure I2C1 pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin =  GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  Configure the I2C interface.
  * @param  None
  * @retval None
  */
void I2C_Config(void)
{
    /* Enable I2C1 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
    
    /* I2C initialization */
    I2C_Init(I2C1, &I2C_InitStructure);
    
    /* Enable I2C1 */
    I2C_Cmd(I2C1, ENABLE);
}

/**
  * @brief  I2C Master Write Task.
  * @param  pvParameters: pointer that will be passed to the task
  * @retval None
  */
void I2C_MasterWriteTask(void *pvParameters)
{
    uint8_t i = 0;
    
    /* Send START condition */
    I2C_GenerateSTART(I2C1, ENABLE);
    
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    /* Send slave address for write */
    I2C_Send7bitAddress(I2C1, I2C_SLAVE_ADDRESS7, I2C_Direction_Transmitter);
    
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    /* Send data */
    for(i = 0; i < I2C_MASTER_WRITE_BUFFER_SIZE; i++)
    {
        /* Send data */
        I2C_SendData(I2C1, I2C_MasterWriteBuffer[i]);
        
        /* Test on EV8 and clear it */
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C1, ENABLE);
    
    /* Wait for STOP condition to be generated */
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_I2CBSY));
    
    /* Send data to queue to indicate write operation is complete */
    xQueueSend(xI2CQueue, &i, 0);
    
    while(1)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

/**
  * @brief  I2C Master Read Task.
  * @param  pvParameters: pointer that will be passed to the task
  * @retval None
  */
void I2C_MasterReadTask(void *pvParameters)
{
    uint8_t i = 0;
    uint8_t data = 0;
    
    /* Wait for write operation to complete */
    xQueueReceive(xI2CQueue, &i, portMAX_DELAY);
    
    /* Send START condition */
    I2C_GenerateSTART(I2C1, ENABLE);
    
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    /* Send slave address for read */
    I2C_Send7bitAddress(I2C1, I2C_SLAVE_ADDRESS7, I2C_Direction_Receiver);
    
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    
    /* Receive data */
    for(i = 0; i < I2C_MASTER_READ_BUFFER_SIZE; i++)
    {
        if(i == (I2C_MASTER_READ_BUFFER_SIZE - 1))
        {
            /* Disable Acknowledgement */
            I2C_AcknowledgeConfig(I2C1, DISABLE);
            
            /* Send STOP condition */
            I2C_GenerateSTOP(I2C1, ENABLE);
        }
        
        /* Test on EV7 and clear it */
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
        
        /* Read data */
        data = I2C_ReceiveData(I2C1);
        I2C_MasterReadBuffer[i] = data;
    }
    
    /* Enable Acknowledgement */
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    
    /* Wait for STOP condition to be generated */
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_I2CBSY));
    
    /* Print received data */
    printf("Master received data: ");
    for(i = 0; i < I2C_MASTER_READ_BUFFER_SIZE; i++)
    {
        printf("0x%02X ", I2C_MasterReadBuffer[i]);
    }
    printf("\n");
    
    while(1)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

/**
  * @brief  I2C Slave Task.
  * @param  pvParameters: pointer that will be passed to the task
  * @retval None
  */
void I2C_SlaveTask(void *pvParameters)
{
    uint8_t i = 0;
    uint8_t data = 0;
    
    while(1)
    {
        /* Wait for address match event */
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));
        
        /* Receive data */
        for(i = 0; i < I2C_SLAVE_READ_BUFFER_SIZE; i++)
        {
            /* Test on EV7 and clear it */
            while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_BYTE_RECEIVED));
            
            /* Read data */
            data = I2C_ReceiveData(I2C1);
            I2C_SlaveReadBuffer[i] = data;
        }
        
        /* Wait for address match event */
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED));
        
        /* Send data */
        for(i = 0; i < I2C_SLAVE_WRITE_BUFFER_SIZE; i++)
        {
            /* Test on EV7 and clear it */
            while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
            
            /* Send data */
            I2C_SendData(I2C1, I2C_SlaveWriteBuffer[i]);
        }
        
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure I2C GPIO ports */
    I2C_GPIO_Config();
    
    /* Configure I2C interface */
    I2C_Config();
    
    /* Create queue for communication between tasks */
    xI2CQueue = xQueueCreate(1, sizeof(uint8_t));
    
    /* Create tasks */
    xTaskCreate(I2C_MasterWriteTask, "I2C_MasterWriteTask", configMINIMAL_STACK_SIZE, NULL, I2C_MASTER_WRITE_TASK_PRIORITY, NULL);
    xTaskCreate(I2C_MasterReadTask, "I2C_MasterReadTask", configMINIMAL_STACK_SIZE, NULL, I2C_MASTER_READ_TASK_PRIORITY, NULL);
    xTaskCreate(I2C_SlaveTask, "I2C_SlaveTask", configMINIMAL_STACK_SIZE, NULL, I2C_SLAVE_TASK_PRIORITY, NULL);
    
    /* Start the scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    while(1);
}