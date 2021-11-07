/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_usart.h"
#include "ms32f0xx_rcc.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup USART_EF_Init
  * @{
  */

/**
  * @brief  De-initialize USART registers (Registers restored to their default values).
  * @param  USARTx USART Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: USART registers are de-initialized
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_USART_DeInit(USART_TypeDef *USARTx) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_USART1);
  /* Force reset of USART clock */
  MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_USART1);
  /* Release reset of USART clock */
  MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_USART1);

  return SUCCESS;
}

/**
  * @brief  Initialize USART registers according to the specified
  *         parameters in UsartInitStr.
  * @note   As some bits in USART configuration registers can only be written when the USART is disabled (USART_CR1_UE bit =0),
  *         USART Peripheral should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @note   Baud rate value stored in UsartInitStr BaudRate field, should be valid (different from 0).
  * @param  USARTx USART Instance
  * @param  UsartInitStr pointer to a MS32_USART_InitTypeDef structure
  *         that contains the configuration information for the specified USART peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: USART registers are initialized according to UsartInitStr content
  *          - ERROR: Problem occurred during USART Registers initialization
  */
ErrorStatus MS32_USART_Init(USART_TypeDef *USARTx, MS32_USART_InitTypeDef *UsartInitStr) {
  ErrorStatus status = ERROR;
  uint32_t periphclk = MS32_RCC_PERIPH_FREQUENCY_NO;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_USART1);

  /* USART needs to be in disabled state, in order to be able to configure some bits in
     CRx registers */
  if (MS32_USART_IsEnabled(USARTx) == 0U) {
    /*---------------------------- USART CR1 Configuration ---------------------
     * Configure USARTx CR1 (USART Word Length, Parity, Mode and Oversampling bits) with parameters:
     * - DataWidth:          USART_CR1_M bits according to UsartInitStr->DataWidth value
     * - Parity:             USART_CR1_PCE, USART_CR1_PS bits according to UsartInitStr->Parity value
     * - TransferDirection:  USART_CR1_TE, USART_CR1_RE bits according to UsartInitStr->TransferDirection value
     * - Oversampling:       USART_CR1_OVER8 bit according to UsartInitStr->OverSampling value.
     */
    MODIFY_REG(USARTx->CR1,
               (USART_CR1_M | USART_CR1_PCE | USART_CR1_PS |
                USART_CR1_TE | USART_CR1_RE | USART_CR1_OVER8),
               (UsartInitStr->DataWidth | UsartInitStr->Parity |
                UsartInitStr->TransferDirection | UsartInitStr->OverSampling));

    /*---------------------------- USART CR2 Configuration ---------------------
     * Configure USARTx CR2 (Stop bits) with parameters:
     * - Stop Bits:          USART_CR2_STOP bits according to UsartInitStr->StopBits value.
     * - CLKEN, CPOL, CPHA and LBCL bits are to be configured using MS32_USART_ClockInit().
     */
    MS32_USART_SetStopBitsLength(USARTx, UsartInitStr->StopBits);

    /*---------------------------- USART CR3 Configuration ---------------------
     * Configure USARTx CR3 (Hardware Flow Control) with parameters:
     * - HardwareFlowControl: USART_CR3_RTSE, USART_CR3_CTSE bits according to UsartInitStr->HardwareFlowControl value.
     */
    MS32_USART_SetHWFlowCtrl(USARTx, UsartInitStr->HardwareFlowControl);

    /*---------------------------- USART BRR Configuration ---------------------
     * Retrieve Clock frequency used for USART Peripheral
     */
    if (USARTx == USART1)
    {
      periphclk = MS32_RCC_GetUSARTClockFreq(MS32_RCC_USART1_CLKSOURCE);
    } else {
      /* Nothing to do, as error code is already assigned to ERROR value */
    }

    /* Configure the USART Baud Rate :
       - valid baud rate value (different from 0) is required
       - Peripheral clock as returned by RCC service, should be valid (different from 0).
    */
    if ((periphclk != MS32_RCC_PERIPH_FREQUENCY_NO) && (UsartInitStr->BaudRate != 0U)) {
      status = SUCCESS;
      MS32_USART_SetBaudRate(USARTx,
                           periphclk,
                           UsartInitStr->OverSampling,
                           UsartInitStr->BaudRate);
    }
  }
  /* Endif (=> USART not in Disabled state => return ERROR) */

  return status;
}

/**
  * @brief Set each @ref MS32_USART_InitTypeDef field to default value.
  * @param UsartInitStr pointer to a @ref MS32_USART_InitTypeDef structure
  *                         whose fields will be set to default values.
  * @retval None
  */

void MS32_USART_StructInit(MS32_USART_InitTypeDef *UsartInitStr) {
  /* Set UsartInitStr fields to default values */
  UsartInitStr->BaudRate            = 9600U;
  UsartInitStr->DataWidth           = MS32_USART_DATAWIDTH_8B;
  UsartInitStr->StopBits            = MS32_USART_STOPBITS_1;
  UsartInitStr->Parity              = MS32_USART_PARITY_NONE ;
  UsartInitStr->TransferDirection   = MS32_USART_DIRECTION_TX_RX;
  UsartInitStr->HardwareFlowControl = MS32_USART_HWCONTROL_NONE;
  UsartInitStr->OverSampling        = MS32_USART_OVERSAMPLING_16;
}

/**
  * @brief  Initialize USART Clock related settings according to the
  *         specified parameters in the UsartClkInitStr.
  * @note   As some bits in USART configuration registers can only be written when the USART is disabled (USART_CR1_UE bit =0),
  *         USART Peripheral should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  USARTx USART Instance
  * @param  UsartClkInitStr pointer to a @ref MS32_USART_ClockInitTypeDef structure
  *         that contains the Clock configuration information for the specified USART peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: USART registers related to Clock settings are initialized according to UsartClkInitStr content
  *          - ERROR: Problem occurred during USART Registers initialization
  */
ErrorStatus MS32_USART_ClockInit(USART_TypeDef *USARTx, MS32_USART_ClockInitTypeDef *UsartClkInitStr) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_USART1);

  /* USART needs to be in disabled state, in order to be able to configure some bits in
     CRx registers */
  if (MS32_USART_IsEnabled(USARTx) == 0U) {
    /*---------------------------- USART CR2 Configuration -----------------------*/
    /* If Clock signal has to be output */
    if (UsartClkInitStr->ClockOutput == MS32_USART_CLOCK_DISABLE) {
      /* Deactivate Clock signal delivery :
       * - Disable Clock Output:        USART_CR2_CLKEN cleared
       */
      MS32_USART_DisableSCLKOutput(USARTx);
    } else {
      /*---------------------------- USART CR2 Configuration -----------------------
       * Configure USARTx CR2 (Clock signal related bits) with parameters:
       * - Enable Clock Output:         USART_CR2_CLKEN set
       * - Clock Polarity:              USART_CR2_CPOL bit according to UsartClkInitStr->ClockPolarity value
       * - Clock Phase:                 USART_CR2_CPHA bit according to UsartClkInitStr->ClockPhase value
       * - Last Bit Clock Pulse Output: USART_CR2_LBCL bit according to UsartClkInitStr->LastBitClockPulse value.
       */
      MODIFY_REG(USARTx->CR2,
                 USART_CR2_CLKEN | USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_LBCL,
                 USART_CR2_CLKEN | UsartClkInitStr->ClockPolarity |
                 UsartClkInitStr->ClockPhase | UsartClkInitStr->LastBitClockPulse);
    }
  } else {
    /* Else (USART not in Disabled state => return ERROR */
    status = ERROR;
  }

  return status;
}

/**
  * @brief Set each field of a @ref MS32_USART_ClockInitTypeDef type structure to default value.
  * @param UsartClkInitStr pointer to a @ref MS32_USART_ClockInitTypeDef structure
  *                              whose fields will be set to default values.
  * @retval None
  */
void MS32_USART_ClockStructInit(MS32_USART_ClockInitTypeDef *UsartClkInitStr) {
  /* Set MS32_UsartClkInitStr fields with default values */
  UsartClkInitStr->ClockOutput       = MS32_USART_CLOCK_DISABLE;
  UsartClkInitStr->ClockPolarity     = MS32_USART_POLARITY_LOW;            /* Not relevant when ClockOutput = MS32_USART_CLOCK_DISABLE */
  UsartClkInitStr->ClockPhase        = MS32_USART_PHASE_1EDGE;             /* Not relevant when ClockOutput = MS32_USART_CLOCK_DISABLE */
  UsartClkInitStr->LastBitClockPulse = MS32_USART_LASTCLKPULSE_NO_OUTPUT;  /* Not relevant when ClockOutput = MS32_USART_CLOCK_DISABLE */
}

/**
  * @brief  Initializes the USART interrupt according to the specified parameters.
  * @param  USARTx USART Instance
  * @param  InterruptFunc  contains the configuration information for the USART interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_USART_CR1_IDLEIE
  *         @arg @ref MS32_USART_CR1_RXNEIE
  *         @arg @ref MS32_USART_CR1_TCIE  
  *         @arg @ref MS32_USART_CR1_TXEIE 
  *         @arg @ref MS32_USART_CR1_PEIE  
  *         @arg @ref MS32_USART_CR1_CMIE  
  *         @arg @ref MS32_USART_CR1_RTOIE 
  *         @arg @ref MS32_USART_CR1_EOBIE 
  *         @arg @ref MS32_USART_CR2_LBDIE 
  *         @arg @ref MS32_USART_CR3_EIE   
  *         @arg @ref MS32_USART_CR3_CTSIE 
  *         @arg @ref MS32_USART_CR3_WUFIE 
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_USART_ITConfig(USART_TypeDef *USARTx, uint32_t InterruptFunc, uint32_t Priority) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_USART1);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  SET_BIT(USARTx->ICR, MS32_USART_ICR_ALLIF);
  SET_BIT(USARTx->CR1, InterruptFunc & MS32_USART_CR1_ALLIE);
  SET_BIT(USARTx->CR2, InterruptFunc & MS32_USART_CR2_ALLIE);
  SET_BIT(USARTx->CR3, InterruptFunc & MS32_USART_CR3_ALLIE);

  /*----------------------------- NVIC configuration -------------------------*/
  if ((READ_BIT(USARTx->CR1, MS32_USART_CR1_ALLIE)) || (READ_BIT(USARTx->CR2, MS32_USART_CR2_ALLIE)) || (READ_BIT(USARTx->CR3, MS32_USART_CR3_ALLIE))) {
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(USART1_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(USART1_IRQn);
  }
}

/**
  * @brief  Get the USART flags according to the internal USART ISR registers.
  * @param  USARTx USART Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_USART_ISR_PE   
  *            @arg @ref MS32_USART_ISR_FE   
  *            @arg @ref MS32_USART_ISR_NE   
  *            @arg @ref MS32_USART_ISR_ORE  
  *            @arg @ref MS32_USART_ISR_IDLE 
  *            @arg @ref MS32_USART_ISR_RXNE 
  *            @arg @ref MS32_USART_ISR_TC   
  *            @arg @ref MS32_USART_ISR_TXE  
  *            @arg @ref MS32_USART_ISR_LBDF 
  *            @arg @ref MS32_USART_ISR_CTSIF
  *            @arg @ref MS32_USART_ISR_CTS  
  *            @arg @ref MS32_USART_ISR_RTOF 
  *            @arg @ref MS32_USART_ISR_EOBF 
  *            @arg @ref MS32_USART_ISR_ABRE 
  *            @arg @ref MS32_USART_ISR_ABRF 
  *            @arg @ref MS32_USART_ISR_BUSY 
  *            @arg @ref MS32_USART_ISR_CMF  
  *            @arg @ref MS32_USART_ISR_SBKF 
  *            @arg @ref MS32_USART_ISR_RWU  
  *            @arg @ref MS32_USART_ISR_WUF  
  *            @arg @ref MS32_USART_ISR_TEACK
  *            @arg @ref MS32_USART_ISR_REACK
  * @note   Clear flags(only crc) After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_USART_GetStatusFlag(USART_TypeDef *USARTx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(USARTx->ISR, Flags)) {
    flags = SET;
    WRITE_REG(USARTx->ICR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}

/******************************** END OF FILE *********************************/

