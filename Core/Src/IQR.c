#include "main.h"
#include "usart.h"
#include "can.h"
#include "stdio.h"

/* CAN 接收头与数据缓冲：CAN1 / CAN2 各自独立，避免中断并发时相互覆盖 */
CAN_RxHeaderTypeDef CAN1_RxHeader;
CAN_RxHeaderTypeDef CAN2_RxHeader;
uint8_t CAN1_RxData[8];
uint8_t CAN2_RxData[8];

/**
 * @brief FIFO0 接收回调（CAN1 / CAN2 均路由到 FIFO0）
 *        收到帧后翻转对应 LED 作为指示
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_RxHeader, CAN1_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
		}
	}
	if (hcan->Instance == CAN2) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN2_RxHeader, CAN2_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
		}
	}
}

/**
 * @brief FIFO1 接收回调（CAN1 / CAN2 均路由到 FIFO1）
 *        收到帧后翻转对应 LED 作为指示
 */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN1_RxHeader, CAN1_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
		}
	}
	if (hcan->Instance == CAN2) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN2_RxHeader, CAN2_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
		}
	}
}
