/**
  ******************************************************************************
  * @file 		GPIO_CFG.c
	* @author		SINOMCU-AE
  * @brief 		GPIO config
  *    
  *          This file provides functions to GPIO config:
  *              LED1 LED2 pin pushpull,output,pull up resistance
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
	
/* Includes ------------------------------------------------------------------*/
#include "GPIO_CFG.h"

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void GPIO_Initialization(void)
{
    MS32_GPIO_InitTypeDef  GPIO_InitStruct;
    
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOA);

    MS32_GPIO_StructInit(&GPIO_InitStruct);    
//    GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin;
	GPIO_InitStruct.Pin = MS32_GPIO_PIN_9;
    GPIO_InitStruct.Mode = MS32_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.OutputType = MS32_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Speed = MS32_GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = MS32_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = MS32_GPIO_AF_0;
    MS32_GPIO_Init(GPIOB,&GPIO_InitStruct);    
}

/******************************** END OF FILE *********************************/
