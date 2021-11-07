/**
  ******************************************************************************
  * @file           : main.c
  * @author         ：SINOMCU-AE
  * @brief          : Main program body
  *    
  *          This file provides example code for GPIO and printf by uart:
  * LED1,LED2 blink by sysTick delay_ms;
  * uart send information  of running count(redirect printf).
  * For details, see “readme.txt”  
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
#include "system_define.h"

/* LED blink half cycle in ms  */
#define LED_BLINK_HALF_PRE  200 

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  
  * @retval 
  */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  while(!(MS32_USART_IsActiveFlag_TXE(USART1)))
  {
      ;
  }
  MS32_USART_TransmitData8(USART1,ch);
  return ch;
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void) 
{
    uint32_t count=0;
  
    SysTick_Init();
    GPIO_Initialization();
    USART1_UART_Init();
  
    LED1_ON(); 
    LED2_OFF(); 
    printf("\r\n*****UART Example*****\r\n");
  
    while(1) 
    {
        SysTick_Ms(LED_BLINK_HALF_PRE);
        LED1_TOGGLE();
        LED2_TOGGLE();
        count++;
        printf("\r\n-----running count:%d",count);
    }
}

/******************************** END OF FILE *********************************/
