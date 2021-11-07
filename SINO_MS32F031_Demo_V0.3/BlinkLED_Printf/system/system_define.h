/**
  ******************************************************************************
  * @file    system_define.h
  * @author  SINOMCU-AE
  * @brief   Header file of mian.c file.
  *          Include needed and user application head file
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
#ifndef __SYSTEM_DEF_H
#define __SYSTEM_DEF_H

/* Private includes ----------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "ms32f0xx.h"

#include "GPIO_CFG.h"
#include "USART1_CFG.h"

#include "SysTick_Delay.h"
#include "ms32f0xx_it.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
int main (void);

#endif /* __SYSTEM_DEF_H */

/******************************** END OF FILE *********************************/
