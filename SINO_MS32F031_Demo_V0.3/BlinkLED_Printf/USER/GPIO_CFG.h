/**
  ******************************************************************************
  * @file    GPIO_CFG.h
  * @author  SINOMCU-AE
  * @brief   Header file of GPIO_CFG.c file.
  *    
  *          This file describes the GPIO macro definitions used:
  *             PB8  ------> LED2
  *             PB9  ------> LED1
  *         
 	******************************************************************************
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
#ifndef __GPIO_CFG_H
#define __GPIO_CFG_H

/* Private includes ----------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"

/* Exported macro ------------------------------------------------------------*/
#define LED_Port  GPIOB
#define LED1_Pin   MS32_GPIO_PIN_9
#define LED1_ON()                   MS32_GPIO_SetOutputPin(LED_Port,LED1_Pin) 
#define LED1_OFF()                  MS32_GPIO_ResetOutputPin(LED_Port,LED1_Pin)  
#define LED1_TOGGLE()               MS32_GPIO_TogglePin(LED_Port,LED1_Pin)      

#define LED2_Pin   MS32_GPIO_PIN_8
#define LED2_ON()                   MS32_GPIO_SetOutputPin(LED_Port,LED2_Pin) 
#define LED2_OFF()                  MS32_GPIO_ResetOutputPin(LED_Port,LED2_Pin)    
#define LED2_TOGGLE()               MS32_GPIO_TogglePin(LED_Port,LED2_Pin)  

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void GPIO_Initialization(void);

/* Private defines -----------------------------------------------------------*/

#endif /* __GPIO_CFG_H */ 

/******************************** END OF FILE *********************************/
