/*
 * FreeRTOS LED Toggle Example for GD32F103C8T6
 *
 * This example demonstrates how to use FreeRTOS to toggle LEDs
 * connected to the GD32F103C8T6 microcontroller.
 */

/* Include necessary header files */
#include "gd32f10x.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"

/* LED definitions - based on the gpio_example.c */
#define LEDn 4

#define LED1_PIN GPIO_PIN_0
#define LED1_GPIO_PORT GPIOC
#define LED1_GPIO_CLK RCC_APB2Periph_GPIOC

#define LED2_PIN GPIO_PIN_1
#define LED2_GPIO_PORT GPIOC
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOC

#define LED3_PIN GPIO_PIN_2
#define LED3_GPIO_PORT GPIOC
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOC

#define LED4_PIN GPIO_PIN_3
#define LED4_GPIO_PORT GPIOC
#define LED4_GPIO_CLK RCC_APB2Periph_GPIOC

/* LED control functions - based on gpio_example.c */
static void led_init(uint32_t led_pin, uint32_t led_gpio_port, uint32_t led_gpio_clk)
{
    /* Enable the GPIO clock */
    RCC_APB2PeriphClockCmd(led_gpio_clk, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = led_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(led_gpio_port, &GPIO_InitStructure);
}

static void led_toggle(uint32_t led_gpio_port, uint32_t led_pin)
{
    /* Toggle the LED by reading the output data register and writing the complement */
    uint16_t current_state = GPIO_ReadOutputDataBit(led_gpio_port, led_pin);
    if (current_state != RESET) {
        GPIO_ResetBits(led_gpio_port, led_pin);
    } else {
        GPIO_SetBits(led_gpio_port, led_pin);
    }
}

/* LED task function */
void led_task(void *pvParameters)
{
    /* Initialize all LEDs */
    led_init(LED1_PIN, LED1_GPIO_PORT, LED1_GPIO_CLK);
    led_init(LED2_PIN, LED2_GPIO_PORT, LED2_GPIO_CLK);
    led_init(LED3_PIN, LED3_GPIO_PORT, LED3_GPIO_CLK);
    led_init(LED4_PIN, LED4_GPIO_PORT, LED4_GPIO_CLK);

    while (1)
    {
        /* Toggle each LED with a delay */
        led_toggle(LED1_GPIO_PORT, LED1_PIN);
        vTaskDelay(500 / portTICK_RATE_MS); /* Delay 500ms */

        led_toggle(LED2_GPIO_PORT, LED2_PIN);
        vTaskDelay(500 / portTICK_RATE_MS); /* Delay 500ms */

        led_toggle(LED3_GPIO_PORT, LED3_PIN);
        vTaskDelay(500 / portTICK_RATE_MS); /* Delay 500ms */

        led_toggle(LED4_GPIO_PORT, LED4_PIN);
        vTaskDelay(500 / portTICK_RATE_MS); /* Delay 500ms */
    }
}

/* Main function */
int main(void)
{
    /* Create the LED task */
    xTaskCreate(led_task, "LED_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (1)
        ;
}

/* FreeRTOS hook functions */
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
    /* This function will only be called if a task overflows its stack */
    (void)xTask;
    (void)pcTaskName;

    /* Hang in a loop for debugging */
    while (1)
        ;
}