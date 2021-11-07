/**
  ******************************************************************************
  * @file 		SysTick_Delay.c
	* @author		SINOMCU-AE
  * @brief 		SysTick delay ms
  *    
  *          This file provides functions of delay_ms:
  *              SysTick_Ms(volatile uint32_t Cnt); 
	* Needed call SysTickDelay_Decrement() function in ms32f0xx_it.c file by 
	* SysTick_Handler() function.
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
	
/* Includes ------------------------------------------------------------------*/
#include "SysTick_Delay.h"

/* Variables -----------------------------------------------------------------*/
static __IO uint32_t TimeDelayCnt;


/**
  * @brief SysTick Initialization Function 1ms interrupt
  * @param None
  * @retval None
  */
void SysTick_Init(void)
{
/* SystemFrequency / 1000    1ms 
 * SystemFrequency / 10000   100us 
 */
  if(SysTick_Config( SystemCoreClock / 1000))
  { 
    while (1); 
  }
  
  NVIC_SetPriority(SysTick_IRQn, 0x3);
}

/**
  * @brief Decrement TimeDelayCnt
  * @param None
  * @retval None
  * @note call by SysTick_Handler()
  */
void SysTickDelay_Decrement(void)
{
  if (TimeDelayCnt != 0x00)
  { 
    TimeDelayCnt--;
  }
}

/**
  * @brief delay ms with blocking mode
  * @param How many ms delay
  *         This parameter can be uint32
  * @retval None
  */
void SysTick_Ms(volatile uint32_t Cnt)
{
    TimeDelayCnt = Cnt;
    while(TimeDelayCnt != 0);
}

/******************************** END OF FILE *********************************/
