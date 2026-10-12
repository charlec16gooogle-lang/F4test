#include "led.h"

/**
 * @brief LED流水灯测试：LED1→2→3→4 依次点亮
 */
void led_test(void)
{
	HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(GPIOA, LED1_Pin); HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED1_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED2_Pin); HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED3_Pin); HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
	HAL_GPIO_TogglePin(GPIOA, LED4_Pin); HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
}
