#include "main.h"
#include "beep.h"
#include "usart.h"

void led_test(void) 
{ 
	HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_RESET);
	
  HAL_GPIO_TogglePin(GPIOA, LED1_Pin);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED1_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
}

void BEEP_Setup(void)
{
    BEEP_ON;
    HAL_Delay(100);
    BEEP_OFF;
    HAL_Delay(500);
}

void usart_test(void)
{
    uint8_t tx_data = 0x5A; 
    uint8_t rx_data = 0x00;

    /* ========== 测试 USART1 -> 对应 LED1 ========== */
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_ORE)) {
        __HAL_UART_CLEAR_OREFLAG(&huart1);
    }
    while (HAL_UART_Receive(&huart1, &rx_data, 1, 0) == HAL_OK) {}

    HAL_UART_Transmit(&huart1, &tx_data, 1, 10);
    if (HAL_UART_Receive(&huart1, &rx_data, 1, 2) == HAL_OK && rx_data == tx_data) {
        HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);   // 短接成功，点亮 LED1
    } else {
        HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET); // 断开，熄灭 LED1
    }

    /* ========== 测试 USART2 -> 对应 LED2 ========== */
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE)) {
        __HAL_UART_CLEAR_OREFLAG(&huart2);
    }
    while (HAL_UART_Receive(&huart2, &rx_data, 1, 0) == HAL_OK) {}

    HAL_UART_Transmit(&huart2, &tx_data, 1, 10);
    if (HAL_UART_Receive(&huart2, &rx_data, 1, 2) == HAL_OK && rx_data == tx_data) {
        HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_RESET);
    }

    /* ========== 测试 USART3 -> 对应 LED3 ========== */
    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE)) {
        __HAL_UART_CLEAR_OREFLAG(&huart3);
    }
    while (HAL_UART_Receive(&huart3, &rx_data, 1, 0) == HAL_OK) {}

    HAL_UART_Transmit(&huart3, &tx_data, 1, 10);
    if (HAL_UART_Receive(&huart3, &rx_data, 1, 2) == HAL_OK && rx_data == tx_data) {
        HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
    }
}