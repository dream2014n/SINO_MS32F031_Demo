/**
  ******************************************************************************
  * @file 		ms32f0xx_it.c
	* @author		SINOMCU-AE
  * @brief 		Interrupt Service Routines.
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
#include "system_define.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
// void NMI_Handler (void) 
// {
    
// }

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
// void HardFault_Handler (void) 
// {
//   /* Go to infinite loop when Hard Fault exception occurs */
//   while (1) 
//   {
//     ;
//   }
// }

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler (void) 
// {
    
// }

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler (void) 
// {
    
// }

/**
  * @brief This function handles System tick timer.
  */	
void SysTick_Handler(void)
{
    SysTickDelay_Decrement();
}

/******************************************************************************/
/*                 MS32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_ms32f0xx.s).                                               */
/******************************************************************************/


/**
  * @brief This function handles DMA1_Channel1.
  */
// void DMA1_Channel1_IRQHandler(void) 
// {
    
// }

/**
  * @brief This function handles ADC1 comp.
  */	
// void ADC1_COMP_IRQHandler(void)
// {
    
// }

/**
  * @brief This function handles Timer1 BRK_UP_TRG_COM.
  */
// void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
// {
    
// }

/**
  * @brief This function handles Timer1 CC.
  */
// void TIM1_CC_IRQHandler(void)
// {
    
// }

/**
  * @brief This function handles Timer2.
  */
// void TIM2_IRQHandler(void) //HALL
// {
    
// }

/**
  * @brief This function handles Timer3.
  */
// void TIM3_IRQHandler(void)
// {
    
// }

/**
  * @brief This function handles USART1.
  */
// void USART1_IRQHandler(void)
// {
    
// }

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler (void)
{

}*/

/******************************** END OF FILE *********************************/
