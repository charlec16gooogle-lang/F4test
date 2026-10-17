#include "main.h"
#include "usart.h"
#include "can.h"
#include "stdio.h"

/* CAN 接收头与数据缓冲：CAN1 / CAN2 各自独立，避免中断并发时相互覆盖 */
CAN_RxHeaderTypeDef CAN1_RxHeader;
CAN_RxHeaderTypeDef CAN2_RxHeader;
uint8_t CAN1_RxData[8];
uint8_t CAN2_RxData[8];

/* CAN Echo 回传专用变量（与主循环测试发送的变量相互独立） */
static CAN_TxHeaderTypeDef CAN_EchoTxHeader;
static uint8_t             CAN_EchoTxData[8];
static uint32_t            CAN_EchoTxMailBox;

/**
 * @brief CAN 收到帧后原路 Echo 回传
 *        用于板级测试：发什么回什么，对端 LED 闪烁即表示整条链路正常
 * @param hcan      触发中断的 CAN 句柄（决定从哪路回传）
 * @param rxHeader  收到的帧头（ID / DLC 等信息）
 * @param rxData    收到的数据
 */
static void CAN_RxProcess(CAN_HandleTypeDef *hcan,
                          CAN_RxHeaderTypeDef *rxHeader,
                          uint8_t *rxData)
{
	/* 复制接收数据 */
	for (uint8_t i = 0; i < 8; i++)
		CAN_EchoTxData[i] = rxData[i];

	/* 沿用原始帧的 ID 和格式，原路回传 */
	CAN_EchoTxHeader.StdId              = rxHeader->StdId;
	CAN_EchoTxHeader.ExtId              = rxHeader->ExtId;
	CAN_EchoTxHeader.IDE                = rxHeader->IDE;
	CAN_EchoTxHeader.RTR                = CAN_RTR_DATA;
	CAN_EchoTxHeader.DLC                = rxHeader->DLC;
	CAN_EchoTxHeader.TransmitGlobalTime = DISABLE;

	if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) > 0)
		HAL_CAN_AddTxMessage(hcan, &CAN_EchoTxHeader,
		                     CAN_EchoTxData, &CAN_EchoTxMailBox);
}

/**
 * @brief FIFO0 接收回调（CAN1 / CAN2 均路由到 FIFO0）
 *        收到帧：① 翻转对应 LED 指示  ② Echo 回传
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_RxHeader, CAN1_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
			CAN_RxProcess(hcan, &CAN1_RxHeader, CAN1_RxData);
		}
	} else if (hcan->Instance == CAN2) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN2_RxHeader, CAN2_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
			CAN_RxProcess(hcan, &CAN2_RxHeader, CAN2_RxData);
		}
	}
}

/**
 * @brief FIFO1 接收回调（CAN1 / CAN2 均路由到 FIFO1）
 *        收到帧：① 翻转对应 LED 指示  ② Echo 回传
 */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN1_RxHeader, CAN1_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
			CAN_RxProcess(hcan, &CAN1_RxHeader, CAN1_RxData);
		}
	} else if (hcan->Instance == CAN2) {
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN2_RxHeader, CAN2_RxData) == HAL_OK) {
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
			CAN_RxProcess(hcan, &CAN2_RxHeader, CAN2_RxData);
		}
	}
}
