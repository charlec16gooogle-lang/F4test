#include "beep.h"

/**
 * @brief 上电蜂鸣器自检：响一声后静音
 */
void BEEP_Setup(void)
{
	BEEP_ON;
	HAL_Delay(100);
	BEEP_OFF;
	HAL_Delay(500);
}
