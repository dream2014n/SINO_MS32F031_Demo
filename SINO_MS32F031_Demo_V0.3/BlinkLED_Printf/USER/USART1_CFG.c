/**
  ******************************************************************************
  * @file 		USART1_CFG.c
	* @author		SINOMCU-AE
  * @brief 		USART1 config
  *    
  *          This file provides functions to usart1 initialization:
  *             PA9   ------> USART1_TX
  *             PA10  ------> USART1_RX
  *             BaudRate:115200,8 bit , NONE,STOP 1bit
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
#include "USART1_CFG.h"

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void USART1_UART_Init(void)
{
  MS32_USART_InitTypeDef USART_InitStruct = {0};

  MS32_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_USART1);
  MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10  ------> USART1_RX
  */
  GPIO_InitStruct.Pin = MS32_GPIO_PIN_9;
  GPIO_InitStruct.Mode = MS32_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = MS32_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = MS32_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = MS32_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = MS32_GPIO_AF_1;
  MS32_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = MS32_GPIO_PIN_10;
  GPIO_InitStruct.Mode = MS32_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = MS32_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = MS32_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = MS32_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = MS32_GPIO_AF_1;
  MS32_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* UART parameter configuration*/
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = MS32_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = MS32_USART_STOPBITS_1;
  USART_InitStruct.Parity = MS32_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = MS32_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = MS32_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = MS32_USART_OVERSAMPLING_16;
  MS32_USART_Init(USART1, &USART_InitStruct);
  MS32_USART_DisableIT_CTS(USART1);
  MS32_USART_ConfigAsyncMode(USART1);
  MS32_USART_Enable(USART1);

}

/******************************** END OF FILE *********************************/
