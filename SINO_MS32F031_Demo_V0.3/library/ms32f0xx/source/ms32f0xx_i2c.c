/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_i2c.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2C_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the I2C registers to their default reset values.
  * @param  I2Cx I2C Instance.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: I2C registers are de-initialized
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_I2C_DeInit(I2C_TypeDef *I2Cx) {
  /* Enable clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_I2C1);
  /* Force reset of I2C clock */
  MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_I2C1);
  /* Release reset of I2C clock */
  MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_I2C1);

  return SUCCESS;
}

/**
  * @brief  Initialize the I2C registers according to the specified parameters in I2cInitStr.
  * @param  I2Cx I2C Instance.
  * @param  I2cInitStr pointer to a @ref MS32_I2C_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: I2C registers are initialized
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_I2C_Init(I2C_TypeDef *I2Cx, MS32_I2C_InitTypeDef *I2cInitStr) {
  /* Enable clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_I2C1);

  /* Disable the selected I2Cx Peripheral */
  MS32_I2C_Disable(I2Cx);

  /*---------------------------- I2Cx CR1 Configuration ------------------------
   * Configure the analog and digital noise filters with parameters :
   * - AnalogFilter: I2C_CR1_ANFOFF bit
   * - DigitalFilter: I2C_CR1_DNF[3:0] bits
   */
  MS32_I2C_ConfigFilters(I2Cx, I2cInitStr->AnalogFilter, I2cInitStr->DigitalFilter);

  /*---------------------------- I2Cx TIMINGR Configuration --------------------
   * Configure the SDA setup, hold time and the SCL high, low period with parameter :
   * - Timing: I2C_TIMINGR_PRESC[3:0], I2C_TIMINGR_SCLDEL[3:0], I2C_TIMINGR_SDADEL[3:0],
   *           I2C_TIMINGR_SCLH[7:0] and I2C_TIMINGR_SCLL[7:0] bits
   */
  MS32_I2C_SetTiming(I2Cx, I2cInitStr->Timing);

  /* Enable the selected I2Cx Peripheral */
  MS32_I2C_Enable(I2Cx);

  /*---------------------------- I2Cx OAR1 Configuration -----------------------
   * Disable, Configure and Enable I2Cx device own address 1 with parameters :
   * - OwnAddress1:  I2C_OAR1_OA1[9:0] bits
   * - OwnAddrSize:  I2C_OAR1_OA1MODE bit
   */
  MS32_I2C_DisableOwnAddress1(I2Cx);
  MS32_I2C_SetOwnAddress1(I2Cx, I2cInitStr->OwnAddress1, I2cInitStr->OwnAddrSize);

  /* OwnAdress1 == 0 is reserved for General Call address */
  if (I2cInitStr->OwnAddress1 != 0U) {
    MS32_I2C_EnableOwnAddress1(I2Cx);
  }

  /*---------------------------- I2Cx MODE Configuration -----------------------
  * Configure I2Cx peripheral mode with parameter :
   * - PeripheralMode: I2C_CR1_SMBDEN and I2C_CR1_SMBHEN bits
   */
  MS32_I2C_SetMode(I2Cx, I2cInitStr->PeripheralMode);

  /*---------------------------- I2Cx CR2 Configuration ------------------------
   * Configure the ACKnowledge or Non ACKnowledge condition
   * after the address receive match code or next received byte with parameter :
   * - TypeAcknowledge: I2C_CR2_NACK bit
   */
  MS32_I2C_AcknowledgeNextData(I2Cx, I2cInitStr->TypeAcknowledge);

  return SUCCESS;
}

/**
  * @brief  Set each @ref MS32_I2C_InitTypeDef field to default value.
  * @param  I2cInitStr Pointer to a @ref MS32_I2C_InitTypeDef structure.
  * @retval None
  */
void MS32_I2C_StructInit(MS32_I2C_InitTypeDef *I2cInitStr) {
  /* Set I2cInitStr fields to default values */
  I2cInitStr->PeripheralMode  = MS32_I2C_MODE_I2C;
  I2cInitStr->Timing          = 0U;
  I2cInitStr->AnalogFilter    = MS32_I2C_ANALOGFILTER_ENABLE;
  I2cInitStr->DigitalFilter   = 0U;
  I2cInitStr->OwnAddress1     = 0U;
  I2cInitStr->TypeAcknowledge = MS32_I2C_NACK;
  I2cInitStr->OwnAddrSize     = MS32_I2C_OWNADDRESS1_7BIT;
}

/**
  * @brief  Initializes the I2C interrupt according to the specified parameters.
  * @param  I2Cx I2C Instance
  * @param  InterruptFunc  contains the configuration information for the I2C interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_I2C_CR1_TXIE  
  *         @arg @ref MS32_I2C_CR1_RXIE  
  *         @arg @ref MS32_I2C_CR1_ADDRIE
  *         @arg @ref MS32_I2C_CR1_NACKIE
  *         @arg @ref MS32_I2C_CR1_STOPIE
  *         @arg @ref MS32_I2C_CR1_TCIE   
  *         @arg @ref MS32_I2C_CR1_ERRIE  
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_I2C_ITConfig(I2C_TypeDef *I2Cx, uint32_t InterruptFunc, uint32_t Priority) {
  /* Enable clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_I2C1);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  WRITE_REG(I2Cx->ICR, MS32_I2C_ICR_ALLCF);
  SET_BIT(I2Cx->CR1, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (READ_BIT(I2Cx->CR1, MS32_I2C_CR1_ALLIE)) {
    NVIC_EnableIRQ(I2C1_IRQn);
    NVIC_SetPriority(I2C1_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(I2C1_IRQn);
  }
}

/**
  * @brief  Get the I2C flags according to the internal I2C ISR registers.
  * @param  I2Cx I2C Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_I2C_ISR_TXE    
  *            @arg @ref MS32_I2C_ISR_TXIS   
  *            @arg @ref MS32_I2C_ISR_RXNE   
  *            @arg @ref MS32_I2C_ISR_ADDR   
  *            @arg @ref MS32_I2C_ISR_NACKF  
  *            @arg @ref MS32_I2C_ISR_STOPF  
  *            @arg @ref MS32_I2C_ISR_TC     
  *            @arg @ref MS32_I2C_ISR_TCR    
  *            @arg @ref MS32_I2C_ISR_BERR   
  *            @arg @ref MS32_I2C_ISR_ARLO   
  *            @arg @ref MS32_I2C_ISR_OVR    
  *            @arg @ref MS32_I2C_ISR_PECERR 
  *            @arg @ref MS32_I2C_ISR_TIMEOUT
  *            @arg @ref MS32_I2C_ISR_ALERT  
  *            @arg @ref MS32_I2C_ISR_BUSY   
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_I2C_GetStatusFlag(I2C_TypeDef *I2Cx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(I2Cx->ISR, Flags)) {
    flags = SET;
    WRITE_REG(I2Cx->ISR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}


/******************************** END OF FILE *********************************/
