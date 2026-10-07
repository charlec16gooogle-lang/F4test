#ifndef _BEEP_H_
#define _BEEP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"

#define BEEP_PORT GPIOA
#define BEEP_PIN GPIO_PIN_8


#define BEEP_ON HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_SET)
#define BEEP_OFF HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_RESET)

//void BEEP_Alarm(u8 time);
void BEEP_Setup(void);

#ifdef __cplusplus
}
#endif

#endif
