/**
  ******************************************************************************
  * @file    SysTick_Delay.h
  * @author  SINOMCU-AE
  * @brief   Header file of SysTick_Delay file.
  * 	
	******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 sinomcu
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by sinomcu under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTICK_DELAY_H
#define __SYSTICK_DELAY_H

/* Private includes ----------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void SysTick_Init(void);
void SysTickDelay_Decrement(void);
void SysTick_Ms(volatile uint32_t Cnt);

void SysDelay_Init(void);
void SysDelay_ms(volatile uint32_t Cnt);
void SysDelay_us(volatile uint32_t Cnt);

#endif /* __SYSTICK_DELAY_H */

/******************************** END OF FILE *********************************/
