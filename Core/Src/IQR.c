#include "main.h"
#include "usart.h"
#include "can.h"
#include "stdio.h"

CAN_RxHeaderTypeDef CAN1_RxHeader;
CAN_RxHeaderTypeDef CAN2_RxHeader;
uint8_t CAN_RxData[8];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_RxHeader, CAN_RxData) == HAL_OK) 
	{
		if (hcan->Instance == CAN1) 
		{
			HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
		}
		if (hcan->Instance == CAN2) 
		{
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
		}
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* hcan) {
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN1_RxHeader, CAN_RxData) == HAL_OK) 
	{
		if (hcan->Instance == CAN1) 
		{
			HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
		}
		if (hcan->Instance == CAN2) 
		{
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
		}
	}
}
